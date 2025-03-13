#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <string.h> 
#include <errno.h> 

pthread_cond_t wq = PTHREAD_COND_INITIALIZER; 
pthread_mutex_t acces = PTHREAD_MUTEX_INITIALIZER; 

int lock = 0; 
int nbw = 0;

void *loquet_passif(void *param);


int main(int argc, char *argv[]) { 

	pthread_t thread_tcb[4];
	
	/* create threads */ 
	for (int i = 0; i <= 3; i++)
		pthread_create (&thread_tcb[i], NULL, loquet_passif, (void*) i);
	
	/* wait for the threads to finish */ 
	for (int i = 0; i <= 3; i++)
		pthread_join(thread_tcb[i], NULL); 

	printf ( "The threads finished\n"); 
	return 0; 	
}
 
void *loquet_passif(void * param) {

	int i, j;
//	int k;
	int thread_no = reinterpret_cast<int> (param) ;
	
	printf ( "thread no %d demarre\n", thread_no); 

//	k = 5-thread_no;
//	for (i = 1; i <= 1000000*k; i++)  j += 1;

	// demander le verrou
	pthread_mutex_lock(&acces);   
	if (lock == 1) {
		printf ( "thread no %d attend var cond\n", thread_no); 
		nbw++;
		pthread_cond_wait (&wq, &acces);
	}
	else lock = 1;
	pthread_mutex_unlock(&acces); 

	printf ( "thread no %d acquiere la section critique\n", thread_no);
	
	// Execution quelconque
	for (i = 1; i <= 1000000*thread_no; i++)  j += 1;
	
	// liberer le verrou
	pthread_mutex_lock(&acces);   
	if (nbw > 0) {
		nbw--;;
		pthread_cond_signal(&wq); 
	}
	pthread_mutex_unlock(&acces);
	printf ( "thread no %d libere la section critique\n", thread_no); 
		
	return NULL; 
}





