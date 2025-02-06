/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
int main( ) {
    int fd[2];
    pipe(fd);
     if (fork()==0) { // premier fils
	        printf("fils de pid=%d se transforme en ls \n",getpid());
            dup2(fd[1],1);
            close(fd[0]); close(fd[1]);
            execl("/bin/ls","ls",NULL);
            _exit(1);
    }  
    
    if (fork()==0) { // second  fils
            printf("fils de pid=%d se transforme en cat \n",getpid());
            dup2(fd[0],0);
            close(fd[0]); close(fd[1]);
	        execl("/bin/cat","cat", NULL);
	        _exit(1);
    } 
    close(fd[0]); close(fd[1]);
    int pid;
    while ((pid=wait(NULL)) > 0)
         printf("fin du fils de pid=%d\n", pid);
    return 0;
}


