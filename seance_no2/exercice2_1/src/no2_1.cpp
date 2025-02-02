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
{
   int nb;
   for(int i=0; i<5; i++)
      {
          if(fork() ==0 )
          {
              printf("pid = %d , ppid = %d \n", getpid(), getppid());
              _exit(0);
          }
      }
  printf("pid=%d \n", getpid());
  do
  {
      nb = wait(NULL);
      printf("nb=%d \n", nb);
  } while (nb > 0);
return(0);
}