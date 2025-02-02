/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
   printf("message0\n");
   if (fork()) {
      wait(NULL); // pour 2
      printf("message1\n");
      if (fork()) {
         printf("message2\n");
      }
      else { _exit(0); }
   }
   else { printf("message3\n"); }
   while(wait(NULL)>0);
   _exit(0);
} 

