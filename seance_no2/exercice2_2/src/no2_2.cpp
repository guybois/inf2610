/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{  int i;
   for(i=0; i<5; i++)
      {
          if(fork() ==0 )
          {
              printf("pid = %d , ppid = %d \n", getpid(), getppid());
              _exit(0); // Le fils passe de running à zombie
          }
      }
      printf("pid=%d \n", getpid());
       int pid;
       // WIFEXITED(status) vérifie si le fils s'est terminé normalement (valeur non nulle si le processus s'est terminé normalement)
      while((pid=wait(&i))>0) 
      {     if( WIFEXITED(i)) { printf(" fin normale du fils de pid= %d \n", pid); }
             else printf(" fin anormale du fils de pid= %d \n", pid);
       }
      return 0;
}
