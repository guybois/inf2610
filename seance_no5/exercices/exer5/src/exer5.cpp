

#include <stdio.h>
#include <pthread.h>
#include <unistd.h> 
#include <semaphore.h> 
#define N 3

sem_t S[N];

void * f (void *x)
{  long c=0;
   long i= (long)x;
   while(1) {  // un cycle de Ti
      sem_wait(&S[i]);
      if(i==2) sem_wait(&S[i]);
       printf("Cycle %lu de T%lu \n", c, i);
       c=c+1; 
       if(i!=2) sem_post(&S[2]);
       else { sem_post(&S[0]); sem_post(&S[1]);}
   }
   return NULL;
 }

int main()
{    pthread_t T[N];
     long i;
     for(i=0; i<N;i++)
        if (i==2) sem_init(&S[i],0,0);
        else sem_init(&S[i],0,1);
     for(i=0; i<N;i++)
        pthread_create (&T[i],NULL,f,(void *)i);
     sleep(1);
     for(i=0; i<N;i++)   
         pthread_cancel (T[i]);
     for(i=0; i<N;i++)  
        pthread_join (T[i],NULL);
     for(i=0; i<N;i++)  
        sem_destroy (&S[i]);
    return 0;
}