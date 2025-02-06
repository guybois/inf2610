/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
void *func(void *x) { 
    printf("Thread de tid=%lu rattaché au pid=%d\n", pthread_self(), getpid());
    return NULL;
}
int main (int argc, char* argv[])
 {  
    int  n=atoi(argv[1]);
// Attention pour n=5 faire un ./bin/executable 5 dans le terminal à l'exécution
  
    pthread_t *tid = (pthread_t *) malloc(n * sizeof(pthread_t));
    if (tid == NULL) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }


   for(int i=0; i <n; i++)
    {     pthread_create(&tid[i], NULL, func, NULL);           
    }
printf("Thread principal de tid=%lu rattaché au pid=%d\n", pthread_self(), getpid());
  for(int i=0; i <n; i++)
  { pthread_join(tid[i],NULL);
  }
  
   return 0;
}

