/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <stdio.h>
long* pa;
void increment() 
{   for(int i=0; i<1000000; i++)   *pa= *pa+1; 
}
int main ()  {
  
    pa = (long *) mmap(NULL, sizeof(long),PROT_READ | PROT_WRITE, 
    MAP_SHARED | MAP_ANON, 0, 0);

  *pa = 0;  
    if (fork() ==0)  {  
             increment(); 
             _exit(0); 
     }   
    wait(NULL);
    printf(" *pa = %ld\n", *pa); 
   
    munmap(pa, sizeof(long));
  return 0;
}




