#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <errno.h> 
#include <semaphore.h>
#define SUMSIZE 100 
#define BUFSIZE 8

// Attention 
// Ici on a:
// - nlots gere le  nombre de place disponible qui est équivalent a nplein
// - nitems gere le nombre place occupe qui est équivalent a nvide

static int buffer[BUFSIZE];
int sum = 0; 
static pthread_mutex_t buffer_lock = PTHREAD_MUTEX_INITIALIZER; 
static int bufin = 0;
static int bufout = 0;

void put_item(int); 
void get_item(int *); 
void *producer(void *param);
void *consumer(void *param);
sem_t nslots;     
sem_t nitems;  

int main (int argc, char *argv[])
{

	pthread_t prodtid; 
	pthread_t constid; 
	int i, total;     

	sem_init(&nslots, 0, BUFSIZE);    // N places disponibles au depart pour le producteur
	sem_init(&nitems, 0, 0);	  // Rien a consommer au depart pour le consommateur

	total = 0; 
	for (i = 1; i <= SUMSIZE; i++) 
		total += i*i; 
	printf("The actual sum should be %d\n", total); 

	/* create threads */ 
	if (pthread_create(&constid, NULL, consumer, NULL)) 
		perror ( "Could not create consumer"); 
	else if (pthread_create(&prodtid, NULL, producer, NULL)) 
		perror ( "Could not create producer");
		
	/* wait for the threads to finish */
	pthread_join(prodtid, NULL); 
	pthread_join(constid, NULL);
	printf ( "The threads produced the sum %d\n", sum); 
	return 0; 

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

/* Put item into buffer at position bufin and update bufin. */
void put_item(int item) 
{ 
	pthread_mutex_lock(&buffer_lock); 
	buffer[bufin] = item; 
	bufin = (bufin + 1) % BUFSIZE; 
	pthread_mutex_unlock(&buffer_lock); 
	return; 
}

void *producer(void * argl)
{
	int i; 
	for (i = 1; i <= SUMSIZE; i++) {
		sem_wait(&nslots);
		put_item(i*i); 
		printf ( "A sum has been produced %d\n", i*i); 
		sem_post(&nitems);
	}
	return NULL; 
}

void *consumer(void *arg2)
{
	int i, myitem; 
	for (i = 1; i <= SUMSIZE; i++) {
		sem_wait(&nitems);
		get_item(&myitem); 
		sum += myitem; 
		printf ( "Consume the sum %d\n", myitem); 
		sem_post(&nslots);
	}
	return NULL;
}

