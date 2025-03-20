#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <string.h> 
#include <errno.h> 

pthread_cond_t rdv_t[3] ; 
pthread_mutex_t acces = PTHREAD_MUTEX_INITIALIZER; 

int N = 3;
int nbw = 0; 

void *thread_code (void *param);

int main(int argc, char *argv[]) { 

	pthread_t thread_tcb[3];
	
	/* create threads */ 
	for (int i = 0; i <= 2; i++) {
		rdv_t[i] = PTHREAD_COND_INITIALIZER;
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
	
	printf ( "thread no %d se dirige vers cinema \n", thread_no); 
	
	//  Synchronisation	
	pthread_mutex_lock(&acces);  
	if (nbw == (N-1)) {
		while(nbw > 0) {
			nbw--; 
			printf ( "thread no %d tout le monde est la \n", thread_no); 
			for (int i = 0; i < N; i++) 
				pthread_cond_broadcast(&rdv_t[i]);
			break;
		}
	}		
	else {
			nbw++; 
			printf ( "thread no %d va attendre les autres \n", thread_no); 
			pthread_cond_wait(&rdv_t[thread_no], &acces);
	}			
	
	pthread_mutex_unlock(&acces);   
	
	printf ( "threadno %d on rentre ensemble au cinema\n", thread_no); 
		
	return NULL; 
}





