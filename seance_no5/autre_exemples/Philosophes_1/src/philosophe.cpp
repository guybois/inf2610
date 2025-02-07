/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5
#define G (i+1)%N  // fourchette de gauche du philosophe i
#define D i  // fourchette de droite du philosophe i
#define libre 1
#define occupe 0
// cinq fourchettes libres 
int fourchettes[N] = { libre, libre, libre, libre, libre };

sem_t mutex;

void* philosophe(void* arg) {
    long i = (long) arg;
    int tours = 4;
    while (tours) {
        sleep(1); // penser
        sem_wait(&mutex);
        if (fourchettes[G] == libre && fourchettes[D] == libre) {
            fourchettes[G] = occupe;
            fourchettes[D] = occupe;
            sem_post(&mutex);
            tours--;
            printf("le philosophe %ld mange\n", i);
            sleep(1); // manger
            printf("le philosophe %ld a fini de manger\n", i);
            sem_wait(&mutex);
            // liberer les fourchettes
            fourchettes[G] = libre;
            fourchettes[D] = libre;
            sem_post(&mutex);
        } else {
            sem_post(&mutex);
        }
    }
}

int  main() {
    long i;
    pthread_t tids[N];

    sem_init(&mutex, 0, 1);
   // création des 5 philosiphes
    for (i = 0; i < N; ++i) {
        pthread_create(&tids[i], NULL, philosophe, (void*)i);
    }

    for (i = 0; i < N; i++) {
        pthread_join(tids[i], NULL);
    }

    printf("fin des threads\n");

    return 0;
}


