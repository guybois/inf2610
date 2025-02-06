/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
void action (int sig) { printf("Signal %d reçu par le processus %d, SIGCHLD=%d\n", sig, 
getpid(),SIGCHLD);
   _exit(0);
}
int main() {
 if (fork()==0) { // fils
           printf("Fils : Je vais dormir pendant 2s\n");
           sleep(2);
           printf("Fils : je vais terminer mon exécution.\n");
          _exit(0);
} 
// Pere
    signal(SIGCHLD,action);
    printf("Père : je vais rentrer dans une boucle infinie\n");
    while(1);  // attente active de la fin de mon fils
}





