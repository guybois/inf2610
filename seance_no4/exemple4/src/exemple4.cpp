/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>  // pour mkfifo
#include <sys/stat.h> // pour mkfifo
int main( ) {  
     mkfifo("tube",0600);
     if (fork()==0) { // premier fils
            printf("fils de pid=%d se transforme en ls \n",getpid());
            int fd; fd=open("tube",O_WRONLY); 
            dup2(fd,1); close(fd);
            execl("/bin/ls","ls",NULL);
            _exit(1);
    }  
    if (fork()==0) { // second  fils
            printf("fils de pid=%d se transforme en sort \n",getpid());
            int fd; fd=open("tube",O_RDONLY); 
            dup2(fd,0); close(fd);
            execl("/bin/sort","sort", NULL);
           _exit(1);
    } 
    int pid;
    while ((pid=wait(NULL)) > 0)
    printf("fin du fils de pid=%d\n", pid);
    return 0;
}



