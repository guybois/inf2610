/*******************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define N 3

/*0*/ // déclarer les sémaphores etc.
sem_t S[N];
void  Trajet_au_cinema(long i) { 
    printf(" Ami %lu arrive au cinéma \n", i); 
}

void  Acces_au_cinema(long i) { 
    printf(" Ami %lu rentre au cinéma \n", i); 
}
 
void* ami (void * x) { 
    long i=(long)x;
    Trajet_au_cinema(i);
    /* 1*/ // attendre tous ses amis après avoir signalè son arrivée
    int j;
    for(j=0; j<N; j++) {
        if(j!=i) { sem_post(&S[j]);}
    }
    for(j=0; j<N-1; j++) { 
         sem_wait(&S[i]);
    }
    Acces_au_cinema(i);
}
int main() {
pthread_t tid[N];
long i;
  /* 2 */ //  initialiser les sémaphores 
for(i=0; i<N; i++)
  { sem_init(&S[i],0,0);} 
   
for(i=0; i<N; i++)
   pthread_create(&tid[i], NULL, ami, (void *)i);

for(i=0; i<N; i++)
    pthread_join(tid[i], NULL);
return 0;
}





