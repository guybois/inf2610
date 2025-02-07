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

// BOUCLES INFNIES POUR OBSERVATION

void* lecteur(void* arg) {
    while (1) {
        sem_wait(&mutex);
        if (nbL == 0) {
            sem_wait(&redact); // le premier lecteur doit obtenir le jeton de redact
        }
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
        sem_wait(&redact); // il faut obtenir le jeton de redact avant d'accéder à la base de données
        // modifier les donnees de la base de données
        db++;
        printf("redacteur bd=%d\n", db);
        sleep(1);
        sem_post(&redact);
    }
    return NULL;
}

int main() {
    const int NUMBER_OF_THREADS = 5;
    pthread_t tids[5];

    sem_init(&mutex, 0, 1);
    sem_init(&redact, 0, 1);
   // création de 3 lecteurs et 2 rédacteurs
    pthread_create(&tids[0], NULL, lecteur, NULL);
    pthread_create(&tids[1], NULL, lecteur, NULL);
    pthread_create(&tids[2], NULL, lecteur, NULL);
    pthread_create(&tids[3], NULL, redacteur, NULL);
    pthread_create(&tids[4], NULL, redacteur, NULL);
   // attente de la fin des threads 
    for (int i = 0; i < NUMBER_OF_THREADS; ++i) {
        pthread_join(tids[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&redact);

    return 0;
}

