/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main()
{  pid_t pid = fork(); 
   if(pid==0)
  {  printf("Fils : je vais rentrer en pause \n"); 
     pause(); 
     printf("Fils : je suis sorti de ma pause \n");
     return 0; 
 }
   sleep(2);
   kill(pid, SIGUSR1);   // On est sensible à SIGUSR1
   int s;  wait(&s);
   if(WIFEXITED(s)) // true ssi la terminaison est normale
        printf("Fin normale : %d\n", WEXITSTATUS(s));
    if(WIFSIGNALED(s)) // true ssi la terminaison est anormale
        printf("Fin anormale : %d, %d\n", WTERMSIG(s), SIGUSR1);  // numéro du signal ayant 
                                                                  // causé la terminaison anormale
  
return 0;
}
