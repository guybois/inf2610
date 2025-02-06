#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

/* Voici un programme qui capture SIGCHLD et empêche la création de zombies
Éviter les processus zombies

On a vu que lorsqu'un processus fils termine, il reste dans l’état zombie jusqu’à ce que le parent appelle wait() pour récupérer son statut.
Avec un gestionnaire de signal pour SIGCHLD, le parent peut appeler waitpid() et nettoyer le fils immédiatement.
plutôt que d’appeler wait() dans une boucle bloquante. On peut donc gérer les fils de manière asynchrone. */

void handler(int sig) {
    int status;
    pid_t pid;

    // On récupère tous les fils terminés
    // Le gestionnaire appelle waitpid() en mode non bloquant (WNOHANG) pour récupérer les processus fils terminés.
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("Processus fils %d terminé\n", pid);
    }
}

int main() {

    // Quand un fils meurt, SIGCHLD est envoyé, et handler() nettoie le zombie.
   /*  Options utiles pour sigaction()
    SA_RESTART : Redémarre les appels système interrompus.
    SA_NOCLDSTOP : Ignore les fils suspendus (SIGSTOP, SIGTSTP).
    SA_NOCLDWAIT : Empêche la création de zombies (les fils sont nettoyés automatiquement). */

    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP | SA_NOCLDWAIT;  
    sigaction(SIGCHLD, &sa, NULL);

    if (fork() == 0) {
        printf("Fils %d démarré\n", getpid());
        sleep(2);  // Simule un travail du fils
        exit(0);
    }

    printf("Parent en attente...\n");
    sleep(5);  // Simulation d'un programme en cours
    // wait(NULL); Plutôt que d’appeler wait() dans une boucle bloquante, on peut gérer les fils de manière asynchrone.
    printf("Parent termine\n");

    return 0;
}



