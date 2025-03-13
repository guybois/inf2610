#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <string.h> 
#include <errno.h> 

pthread_cond_t wq[3] ; 
pthread_mutex_t acces = PTHREAD_MUTEX_INITIALIZER; 

int tour = 0; 

void *thread_code (void *param);

int main(int argc, char *argv[]) { 

	pthread_t thread_tcb[3];
	
	/* create threads */ 
	for (int i = 0; i <= 2; i++) {
		wq[i] = PTHREAD_COND_INITIALIZER;
		pthread_create (&thread_tcb[i], NULL, thread_code, (void *) i);
	}
	/* wait for the threads to finish */ 
	for (int i = 0; i <= 2; i++)
		pthread_join(thread_tcb[i], NULL); 

	printf ( "The threads finished\n"); 
	return 0; 	
}
 
void *thread_code(void * param) {


	int thread_no = reinterpret_cast<int> (param) ;
	
	printf ( "thread no %d demarre\n", thread_no); 

//	k = 5-thread_no;
//	for (i = 1; i <= 1000000*k; i++)  j += 1;

	// wtour
	pthread_mutex_lock(&acces);   
	if (tour != thread_no) {
		printf ("thread no %d attend var cond\n", thread_no); 
		pthread_cond_wait (&wq[thread_no], &acces);
	}
	pthread_mutex_unlock(&acces);   

	printf ( "Cycle de T%d\n", thread_no); 
	
	// stour
	pthread_mutex_lock(&acces);  
	tour =(tour+1) % 3;
	pthread_cond_signal(&wq[tour]);
	pthread_mutex_unlock(&acces);  
	
	printf ( "threadno %d termine\n", thread_no); 
		
	return NULL; 
}





