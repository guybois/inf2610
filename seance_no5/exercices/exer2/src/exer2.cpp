#include <stdio.h> // pour printf
#include <pthread.h>

long a=0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* thread_funct(void * p)
{
  printf("thread %lu exécute thread_funct(%ld)\n", pthread_self(), (long)p);
  pthread_mutex_lock(&mutex);
  for(long i=0;i<(long)p;i++) a++;
  pthread_mutex_unlock(&mutex);
  pthread_exit(NULL);
}

int main()
{
  pthread_t tid1, tid2;
  if ( pthread_create(&tid1, NULL, thread_funct, (void*)40000000) != 0)
    return -1;
  if ( pthread_create(&tid2, NULL, thread_funct, (void*)80000000) != 0)
    return -1;
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  pthread_mutex_destroy(&mutex);
  printf("thread principal se termine avec a =%ld\n", a);
  return 0;
}