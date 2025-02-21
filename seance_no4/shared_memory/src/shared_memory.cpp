#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/wait.h>

long* pa;
sem_t* sem;

void increment() {
    for (int i = 0; i < 1000000; i++) {
        sem_wait(sem);   // 🔒 Verrouille le sémaphore
        *pa = *pa + 1;
        sem_post(sem);   // 🔓 Déverrouille le sémaphore
    }
}

int main() {
    // Création d'une mémoire partagée
    pa = (long*) mmap(NULL, sizeof(long), PROT_READ | PROT_WRITE,
                      MAP_SHARED | MAP_ANON, -1, 0);
    sem = (sem_t*) mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE,
                        MAP_SHARED | MAP_ANON, -1, 0);

    if (pa == MAP_FAILED || sem == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    *pa = 0;
    sem_init(sem, 1, 1);  // Initialisation du sémaphore (1 = inter-processus)

    if (fork() == 0) {  // Premier fils
        increment();
        _exit(0);
    }

    if (fork() == 0) {  // Deuxième fils
        increment();
        _exit(0);
    }

    // Attente de la fin des deux fils
    wait(NULL);
    wait(NULL);

    printf(" *pa = %ld\n", *pa);  // Attendu : 2000000

    // Libération des ressources
    sem_destroy(sem);
    munmap(pa, sizeof(long));
    munmap(sem, sizeof(sem_t));

    return 0;
}



