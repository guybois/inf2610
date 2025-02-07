/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>      // Pour printf()
#include <stdlib.h>     // Pour exit() et NULL
#include <pthread.h>    // Pour pthread_t, pthread_create(), pthread_join(), pthread_exit()
//#include <stdatomic.h>  // Pour atomic_long, atomic_fetch_add(), atomic_init()
#include <atomic>  
#include <iostream>

std::atomic_long a;
volatile long b;
const int un = 1, moinsun = -1;
void *
inc_dec (void *x)
{
  int pas = *(int *) x;
  for (int i = 0; i < 100000; i++)
    {
      atomic_fetch_add (&a, pas);
      b = b + pas;
    }
    std::cout << "Valeur après inc_dec  dans main de a  : " << a << "  et b : " << b << "  pour un pas de : " << pas  <<std::endl;

  pthread_exit (NULL);
}

int
main ()
{
 // atomic_init (&a, 0);  inutile en C++
  a = 0;
  std::cout << "Valeur initiale dans main de a  : " << a << "  et b : " << b <<std::endl;
  pthread_t tid1, tid2;

  //creation de deux threads
  if (pthread_create (&tid1, NULL, inc_dec, (void *) &un) != 0)
    return -1;
  //printf("ici main: creation du thread inc_dec(%d) avec succes\n",un);
  if (pthread_create (&tid2, NULL, inc_dec, (void *) &moinsun) != 0)
    return -1;
  // printf("ici main: creation du thread inc_dec(%d) avec succes\n",moinsun);

  // attendre la fin des deux threads
  pthread_join (tid1, NULL);
  pthread_join (tid2, NULL);

  std::cout << "Valeur finale dans main de a  : " << a << "  et b : " << b <<std::endl;
  return 0;
}


