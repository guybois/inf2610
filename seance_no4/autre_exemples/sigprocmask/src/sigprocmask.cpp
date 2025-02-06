#include <signal.h>
#include <stdio.h>


void action(int sig) { 
    printf("\n Signal %d reçu, SIGINT=%d \n",sig,SIGINT);
}

int main() {
    sigset_t set;
    sigemptyset(&set);   // On met le masque à 0
    sigaddset(&set, SIGINT);  // Bloque SIGINT (Ctrl+C)

    struct sigaction sa;
    sa.sa_handler = action;
    sigaction(SIGINT, &sa, NULL);

    sigprocmask(SIG_BLOCK, &set, NULL);
    printf("SIGINT est bloqué, appuyez sur Ctrl+C\n");
    sleep(10);
    
    sigprocmask(SIG_UNBLOCK, &set, NULL);
    printf("SIGINT est débloqué\n");
    pause();
    printf (" fin de ma pause \n");
    return 0;
}



