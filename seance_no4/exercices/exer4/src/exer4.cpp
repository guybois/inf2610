/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <unistd.h> // pour fork, execl, _exit
#include <stdio.h>  // pour printf
#include <sys/wait.h>  // pour wait
#include <fcntl.h>   // pour open
#include <sys/types.h>  // pour mkfifo
 #include <sys/stat.h> // pour mkfifo
int main( ) {
      mkfifo("INF2610", 0666);
     if (fork()==0) { // premier fils
           int fd= open("INF2610", O_WRONLY);
           dup2(fd,1);
           printf("fils de pid=%d se transforme en ls \n",getpid());
           execl("/bin/ls","ls", NULL);
           _exit(1);
    }  
    
    if (fork()==0) { // second  fils
           int fd= open("INF2610", O_RDONLY);
            dup2(fd,0);
           printf("fils de pid=%d se transforme en cat \n",getpid());
           execl("/bin/cat","cat", NULL);
           _exit(1);
    } 
    
    int pid;
    while ((pid=wait(NULL)) > 0)
        printf("fin du fils de pid=%d\n", pid);
    unlink("INF2610");
    
    return 0;
}

