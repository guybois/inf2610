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

sem_t mutex;
sem_t redact;
int db = 42;
int nbL = 0;
/// pour que l'ordre des demandes d'accès = l'odre d'accès 
sem_t tour;
///
// BOUCLES INFNIES POUR OBSERVATION

void* lecteur(void* arg) {
    while (1) {
        sem_wait(&tour); // attendre son tour avant de demander l'accès à la base de données
        sem_wait(&mutex);
        if (nbL == 0) {
            sem_wait(&redact); 
        }
        sem_post(&tour); 
        nbL++;
        sem_post(&mutex);
        //lecture de la base de données
        sleep(1);
        printf("lecteur db=%d\n", db);

        // fin de l'accès à la base de données
        sem_wait(&mutex);
        nbL--;
        if (nbL == 0) {
            sem_post(&redact); // il n'y a plus de lecteurs! Il faut libérer le jeton
        }
        sem_post(&mutex);
    }
    return NULL;
}

void* redacteur(void* arg) {
    while (1) {
        sem_wait(&tour);  // attendre son tour avant de demander l'accès à la base de données
        sem_wait(&redact);
        sem_post(&tour);
        // modifier les donnees de la bd bd
        db++;
        printf("redacteur bd=%d\n", db);
        sleep(1);
        sem_post(&redact);
    }
    return NULL;
}

int main() {
    const u_int8_t NUMBER_OF_THREADS = 5;
    pthread_t tids[5];

    sem_init(&mutex, 0, 1);
    sem_init(&redact, 0, 1);
    sem_init(&tour, 0, 1);
     
    pthread_create(&tids[0], NULL, lecteur, NULL);
    pthread_create(&tids[1], NULL, lecteur, NULL);
    pthread_create(&tids[2], NULL, lecteur, NULL);
    pthread_create(&tids[3], NULL, redacteur, NULL);
    pthread_create(&tids[4], NULL, redacteur, NULL);

    for (int i = 0; i < NUMBER_OF_THREADS; ++i) {
        pthread_join(tids[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&redact);
    sem_destroy(&tour);
    return 0;
}

