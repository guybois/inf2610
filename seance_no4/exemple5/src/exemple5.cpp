/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
void action(int sig) { 
         printf("\n Signal %d reçu, SIGINT=%d \n",sig,SIGINT);
}

int main()
{     signal(SIGINT, action);      
       printf("Je me mets en pause. Réveillez-moi en tapant CTRL+C.\n");
      pause();
      printf(" fin de ma pause \n");
     return 0;
}



