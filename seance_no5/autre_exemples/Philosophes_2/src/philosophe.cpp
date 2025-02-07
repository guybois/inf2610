/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5
#define G (i+1)%N
#define D i
#define libre 1
#define occupe 0

sem_t f[N];

void *philosophe (void *arg)
{
  long i = (long) arg;
  int tours = 4;
  while (tours) {
      sleep (1);		// penser
      if (G < D) {
    	  sem_wait (&f[G]);
	      sem_wait (&f[D]);
	   } else {
	    sem_wait (&f[D]);
	    sem_wait (&f[G]);
	   }
      tours--;
      printf ("le philosophe %ld mange\n", i);
      sleep (1);		// manger
      printf ("le philosophe %ld a fini de manger\n", i);
      // liberer les fourchettes
      sem_post (&f[G]);
      sem_post (&f[D]);
    }
}

int main ()
{
  long i;
  pthread_t tids[N];

  for (i = 0; i < N; ++i)
    sem_init (&f[i], 0, 1);

  for (i = 0; i < N; ++i)
    {
      pthread_create (&tids[i], NULL, philosophe, (void*)i);
    }

  for (i = 0; i < N; i++)
    {
      pthread_join (tids[i], NULL);
    }

  printf ("fin des threads\n");

  return 0;
}

