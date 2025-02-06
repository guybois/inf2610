/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
void *func(void *x) { 
    sleep(1);     // Permet de mieux voir la concurrence...
    printf("Thread %d de tid=%lu \n", * ((int *)x), pthread_self());
    return NULL;
}
int main ()
 { pthread_t tid[3];
   for(int i=0; i <3; i++)
  {     pthread_create(&tid[i], NULL, func, (void*) &i);           
    }
   for(int i=0; i <3; i++)
  { pthread_join(tid[i],NULL);
  }
   return 0;
}


