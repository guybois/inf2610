#include <stdio.h> // pour printf
#include <pthread.h>

long a=0;

void* thread_funct(void * p)
{
  printf("thread %lu exécute thread_funct(%ld)\n", pthread_self(), (long)p);
  for(long i=0;i<(long)p;i++) a++;
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
  printf("thread principal se termine avec a =%ld\n", a);
  return 0;
}