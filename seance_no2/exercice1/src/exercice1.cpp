/******************************************************************************

Exercice 1

*******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main ()
{
  int x;
  if ((x = fork()) == 0)	// fils
    {
      printf ("pid=%d, ppid=%d\n", getpid(), getppid());
      _exit (0);  // Le fils passe de running à zombie
    }
  printf ("pid=%d, pid du fils = %d \n", getpid(), x);
  wait(NULL);  // Le fils passe de zombie à terminé
  return 0;
} 
