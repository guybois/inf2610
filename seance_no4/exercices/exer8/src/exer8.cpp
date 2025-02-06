/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <unistd.h>        /* pour write et _exit */
#include <stdio.h>        /* pour printf */
#include <sys/wait.h>   /* pour wait */
#include <signal.h>     /* pour signal et kill */
#define MaxJoueurs 4

void jouer (int i)
{    while(1);    }        // simule une partie de jeu

int pid[MaxJoueurs];

void action(int sig)
{
    for (int i = 0; i < MaxJoueurs; i++)
     {kill(pid[i],SIGKILL);}    // Un peu plus violent que le _exit() car on on arrête subitement le fils, donc fuite possible de ressources...
    printf("Fils ont fini de jouer \n");  
}

int main ()
{
    for (int i = 0; i < MaxJoueurs; i++)
    {     if ((pid[i]=fork()) == 0)
         {     jouer (i);  }
    }
    signal(SIGALRM,action);
    alarm(5);
    while(wait(NULL)>0);
    return 0;
}



