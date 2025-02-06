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
int main() {
    int fd[2];  pipe(fd);
    if (fork() == 0) {
               dup2(fd[1],1);
               close(fd[1]); close(fd[0]);
               execlp("ls", "ls", NULL);        
      }
        close(fd[1]); char c;
        while(read(fd[0],&c,1)>0) write(1,&c,1);  
        close(fd[0]);
        wait(NULL);
       _exit(0);
}