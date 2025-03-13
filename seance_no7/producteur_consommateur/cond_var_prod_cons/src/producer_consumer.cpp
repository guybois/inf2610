#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <string.h> 
#include <errno.h> 

#define SUMSIZE 100 
#define BUFSIZE 8 

// - slots est la variable conditionnelle et nslots gere le  nombre de place disponible 
// - items est la variable conditionnelle et nitems gere le nombre place occupe
// - slot_lock permet l'exclusion mutuelle entre producteurs 
// - item_lock permet l'exclusion mutuelle entre consommateurs

int sum = 0; 
static int buffer[BUFSIZE];
static int bufin = 0;
static int bufout = 0;

pthread_cond_t slots = PTHREAD_COND_INITIALIZER; 
pthread_cond_t items = PTHREAD_COND_INITIALIZER; 
pthread_mutex_t slot_lock = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t item_lock = PTHREAD_MUTEX_INITIALIZER; 
static pthread_mutex_t buffer_lock = PTHREAD_MUTEX_INITIALIZER; 

int nslots = BUFSIZE; 
int producer_done = 0; 
int nitems = 0; 

void get_item(int *itemp); 
void put_item(int item);
void *producer(void *param);
void *consumer(void *param);

int main(int argc, char *argv[]) { 

	pthread_t prodtid; 
	pthread_t constid; 
	int i, total; 
	
	total = 0; 
	for (i = 1; i <= SUMSIZE; i++) 
	total += i; 
	printf ( "The checksum is %d\n", total); 
	/* create threads */ 
	pthread_create(&prodtid, NULL, producer, NULL); 
	pthread_create(&constid, NULL, consumer, NULL); 
	/* wait for the threads to finish */ pthread_join(prodtid, NULL); 
	pthread_join(constid, NULL); 
	printf ( "The threads produced the sum %d\n", sum); 
	return 0; 	
}
 
void *producer(void * param) {

	int i;

	for (i = 1; i <= SUMSIZE; i++) { 

		printf ( "producer  start  iteration no %d\n", i); 

		pthread_mutex_lock(&slot_lock);   /* acquire right to a slot */
		while (nslots <= 0) {
			printf ( "producer  is waiting\n");
			pthread_cond_wait (&slots, &slot_lock);
		}
		nslots--;
		pthread_mutex_unlock(&slot_lock); 
		
		put_item(i); 
		
		pthread_mutex_lock(&item_lock);	  /* release right to a slot */
		nitems++;
		pthread_cond_signal(&items); 
		
		pthread_mutex_unlock(&item_lock);

		printf ( "producer  finish  iteration no %d\n", i); 

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
		while (nitems <= 0  && !producer_done) {
			printf ( "consumer  is waiting\n");
			pthread_cond_wait (&items, &item_lock);
		}
		if ( (nitems <= 0) && producer_done) { 
			pthread_mutex_unlock(&item_lock); 
			break; 
		}
		nitems--;
		pthread_mutex_unlock(&item_lock); 
		get_item(&myitem); 
		sum += myitem; 

		printf ( "consumer  finish  iteration  no %d\n", myitem);

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



