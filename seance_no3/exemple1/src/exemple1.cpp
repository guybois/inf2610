
/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

Ce programme illustre la bonne manière de passer des paramètres à un thread en passant un pointeur sur une structure
On en profite pour créer un id à chaque thread, ce qui permet de toujours savoir de quel thread il s'agit lorsqu'on débogue le code

Deuxiement ce code est non déterministe en ce sens que chaque exécution peut imprimer une valeur de a différente
En effet comme on expliqué au cours on a une condition de concurrence sur la variable global a (ce qui peut conduire à une corruption) due
à différentsd entrelacements possibles. On verra dans le chap. 5 comment éviter cette situation.

*******************************************************************************/
// pthreadRaceCond.c
#include <stdio.h>  // pour printf
#include <pthread.h>  

typedef struct{
	int id;
	long incr;
    } info;

long a=0;

void* thread_funct(void * p)
{      
    info params = *(info*)p;
    int id = params.id;
    long incr = params.incr;
    printf("thread %d exécutant thread_funct(%ld)\n", id, incr);
    for(long i=0;i<(long)incr;i++) a++;
    pthread_exit(NULL);
}
int main()
{     
    info params[2];
    pthread_t tid[2];

    for (int i = 0; i < 2; i++) {
        	switch(i)
		{
			case 0:
				params[i].id = 0;
                params[i].incr = 40000000;
				break;
			case 1:
				params[i].id = 1;
                params[i].incr = 80000000;
				break;
			default:
				break;
		};
    };

    for(int i=0; i <2; i++) {     
        pthread_create(&tid[i], NULL, thread_funct, (void*) &params[i]);           
    }

    for(int i=0; i <2; i++) { 
        pthread_join(tid[i],NULL);
    }

    printf("thread principal se termine avec a =%ld\n", a);
    return 0;
}

