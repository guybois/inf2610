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
      else { _exit(0); }     // Le 2e fils passe de running à zombie
   }
   else { printf("message3\n"); }   // Le 1er fils affiche message3
   while(wait(NULL)>0);  // Le père et le fils passent ici: 
                         // Comme le fils n'a pas d'enfant alors wait retournera -1 (erreur) et donc le fils passe immédiatement le while
                         // Le père a un fils et fera une itération dans la boucle avant de recevoir 
   _exit(0);
} 

