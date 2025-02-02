/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int glob=100;
int main()
{
  if(fork()==0)
    { glob=glob-1;
      printf("ici fils pid=%d, glob=%d\n", getpid(), glob);
      _exit(0);
    }
  wait(NULL);
  glob=glob+1;
  printf("ici pere pid=%d, glob=%d\n", getpid(), glob);
  return 0;
}