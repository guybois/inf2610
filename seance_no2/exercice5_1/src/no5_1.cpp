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
   if (fork()) {   // Attention ici on teste d'abord le père (plus grand que 0) et non le fils comme dans les exercices précédents
      printf("message1\n");
      if (fork()) { // Même commentaire que précédemment
         printf("message2\n");
      }
      else { _exit(0); }
   }
   else { printf("message3\n"); }
   while(wait(NULL)>0);
   _exit(0);
} 

