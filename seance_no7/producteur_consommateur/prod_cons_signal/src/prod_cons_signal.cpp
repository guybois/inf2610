#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <signal.h> 
#include <pthread.h> 
#include <sched.h> 
#define SUMSIZE 1861 
#define BUFSIZE 8 
#define SPIN 1000000 
int sum = 0; 
static int buffer[BUFSIZE];
static int bufin = 0;
static int bufout = 0;

// Attention 
// Par rapport au code Java du pdf ici on a:
// - slots est la variable conditionnelle et nlots gere le  nombre de place disponible qui remplacent nplein
// - slot_lock permet l'exclusion mutuelle entre producteurs 
// - items est la variable conditionnelle et nitems gere le nombre place occupe   qui remplacent nvide
// - item_lock permet l'exclusion mutuelle entre consommateurs

pthread_cond_t slots = PTHREAD_COND_INITIALIZER; 
pthread_cond_t items = PTHREAD_COND_INITIALIZER; 
pthread_mutex_t slot_lock PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t item_lock = PTHREAD_MUTEX_INITIALIZER; 
static pthread_mutex_t buffer_lock = PTHREAD_MUTEX_INITIALIZER; 
int nslots = BUFSIZE; 
int producer_done = 0; 
int nitems = 0; 
int totalproduced = 0; 
int producer_shutdown = 0; 
void get_item(int *itemp);
void put_item(int item); 

void spinit(void) { 

	int i;

	for (i = 0; i < SPIN; i++);
}

void *sigusr1_thread(void *arg){
	sigset_t intmask; 
	int number;
	struct sched_param param; 
	int policy; 
	sigemptyset(&intmask); 
	sigaddset(&intmask, SIGUSR1); 
	pthread_getschedparam(pthread_self(), &policy, &param); 
	fprintf(stderr, "sigusr1_thread entered with policy %d and priority %d\n", policy, param.sched_priority);
	sigwait(&intmask, &number); 
	fprintf(stderr, "sigusr1_thread returned from sigwait\n"); 
	pthread_mutex_lock(&slot_lock); 
	producer_shutdown = 1;
	pthread_cond_broadcast(&slots); 
	pthread_mutex_unlock(&slot_lock); 
	return NULL; 
}
	
	
void *producer(void *argl){
	int i;

	for ( i = 1; ; i++) {	
	spinit(); 
	pthread_mutex_lock(&slot_lock);		/* acquire right to a slot */
	while ((nslots <= 0) && (!producer_shutdown)) 
		pthread_cond_wait (&slots, &slot_lock); 
	if (producer_shutdown) { 
		pthread_mutex_unlock(&slot_lock); 
		break; 
		}
	nslots--;
	pthread_mutex_unlock(&slot_lock); 
	spinit(); 
	put_item(i * i);
	pthread_mutex_lock(&item_lock);		/* release right to an item */
	nitems++;
	pthread_cond_signal(&items); 
	pthread_mutex_unlock(&item_lock); spinit(); 
	totalproduced = i; 
	}
	pthread_mutex_lock(&item_lock); 
	producer_done = 1; 
	pthread_cond_broadcast(&items); 
	pthread_mutex_unlock(&item_lock); 
	return NULL; 
}
	
	void *consumer(void * param) {

	int myitem;

	for ( ; ; ) { 

		pthread_mutex_lock(&item_lock);   /* acquire right to a slot */
		while (nitems <= 0  && !producer_done)
			pthread_cond_wait (&items, &item_lock);
		if ( (nitems <= 0) && producer_done) { 
			pthread_mutex_unlock(&item_lock); 
			break; 
		}
		nitems--;
		pthread_mutex_unlock(&item_lock); 
		get_item(&myitem); 
		sum += myitem; 
		pthread_mutex_lock(&slot_lock);  /* release right to a slot */
		nslots++;
		pthread_cond_signal(&slots); 
		pthread_mutex_unlock(&slot_lock);
	}
	return NULL;
}
		
/* Put item into buffer at position bufin and update bufin. */
void put_item(int item) 
{ 
	pthread_mutex_lock(&buffer_lock); 
	buffer[bufin] = item; 
	bufin = (bufin + 1) % BUFSIZE; 
	pthread_mutex_unlock(&buffer_lock); 
	return; 
}

/* Get the next item from buffer and put it in *itemp. */ 
void get_item(int *itemp) 
{
	pthread_mutex_lock(&buffer_lock); 
	*itemp = buffer[bufout];
	bufout = (bufout + 1) % BUFSIZE; 
	pthread_mutex_unlock(&buffer_lock); 
return;
}

int main(int argc, char *argv[]) { 

	pthread_t prodtid; 
	pthread_t constid; 
	pthread_t sighandid; 
	double total; 
	double tp; 
	sigset_t set; 
	pthread_attr_t high_prio_attr; 
	struct sched_param param; 
	fprintf ( stderr, "Process ID is %ld\n", ( long) getpid () ) ;
	
	sigemptyset(&set);		/* block the signal */
	
	sigaddset(&set, SIGUSR1); 
	sigprocmask(SIG_BLOCK, &set, NULL); 
	fprintf(stderr, "Signal blocked\n"); 
	/* create threads */ 
	pthread_attr_init(&high_prio_attr); 
	pthread_attr_getschedparam(&high_prio_attr, &param); 
	param.sched_priority++; 
	pthread_attr_setschedparam(&high_prio_attr, &param); 
	pthread_create(&sighandid, &high_prio_attr, sigusr1_thread, NULL); 
	pthread_create(&prodtid, NULL, producer, NULL); 
	pthread_create(&constid, NULL, consumer, NULL); 
	
	/* wait for the threads to finish */
	pthread_join(prodtid, NULL); 
	pthread_join(constid, NULL); 
	printf ( "The threads produced the sum %d\n", sum) ;
	
	/* show correct value */
	tp = (double) totalproduced; 
	total = tp*(tp + 1)*(2*tp + 1)/6.0; 
	if (tp > SUMSIZE) 
		fprintf(stderr, "*** Overflow occurs for more than %d items\n", SUMSIZE);
	printf ( "The checksum for %4d items is %1.0f\n", totalproduced, total); 

	printf ( "The threads produced the sum %d\n", sum); 
	return 0; 	
}
 








