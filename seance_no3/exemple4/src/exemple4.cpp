/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

Tout comme pour le processus père avec son fils, lors d'un exit un thread peut passer de l'info au thread (programme) principal i.e. le main
C'est le cas ici du pointeur sur tab qui est transférer au thread principal, imprimer et libérer

*******************************************************************************/
//pthreads.c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
long long counter = 0;
 #define MAX 1000000000
 
 void* count(void *arg) {
      long long*pc = (long long*) arg;
      for (long long i = 0; i < MAX; i++) 
      {    *pc += 1; }
      pthread_exit (NULL);
}
int main(int argc, void* argv[] ) {
    
    if(argc==1) { 
       // pas d'arguments pour le traçage
        execlp("strace", "strace", "-e", "trace=clone", "./a.out", "0", NULL);
        _exit(1);
    }
    pthread_t t1, t2;
    pthread_create(&t1,NULL,count, (void*)&counter);
    pthread_create(&t2,NULL,count, (void*)&counter);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    printf("pid= %d counter=%llu\n", getpid(), counter);
    return 0;
}
