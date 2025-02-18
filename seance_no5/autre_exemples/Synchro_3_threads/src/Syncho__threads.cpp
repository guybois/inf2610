/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

sem_t S1;
sem_t S2;
sem_t S3;

// BOUCLES INFNIES POUR OBSERVATION

void* T1(void* arg) {
    while (1) {
        
        printf("exécution de U()\n");

        sem_post(&S1);
        sem_wait(&S3);

        printf("exécution de X()\n");

        sem_post(&S1);
        sem_wait(&S3);

    }
    return NULL;
}

void* T2(void* arg) {
    while (1) {
        
        sem_wait(&S1);

        printf("exécution de V()\n");

        sem_post(&S2);
        sem_wait(&S1);

        printf("exécution de Y()\n");

        sem_post(&S2);

    }
    return NULL;
}

void* T3(void* arg) {
    while (1) {
        
        sem_wait(&S2);

        printf("exécution de W()\n");

        sem_post(&S3);
        sem_wait(&S2);

        printf("exécution de Z()\n");

        sem_post(&S3);

    }
    return NULL;
}

int main() {
    const int NUMBER_OF_THREADS = 3;
    pthread_t tids[3];

    sem_init(&S1, 0, 0);     // On bloque au départ
    sem_init(&S2, 0, 0);     // On bloque au départ
    sem_init(&S3, 0, 0);     // On bloque au départ

   // création de 3 lecteurs et 2 rédacteurs
    pthread_create(&tids[0], NULL, T1, NULL);
    pthread_create(&tids[1], NULL, T2, NULL);
    pthread_create(&tids[2], NULL, T3, NULL);

   // attente de la fin des threads 
    for (int i = 0; i < NUMBER_OF_THREADS; ++i) {
        pthread_join(tids[i], NULL);
    }

    sem_destroy(&S1);
    sem_destroy(&S2);
    sem_destroy(&S3);

    return 0;
}

