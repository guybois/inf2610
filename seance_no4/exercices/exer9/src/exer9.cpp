/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
//#include <signal.h>
//void action(int sig){ wait(NULL); }
int main() {
//    signal(SIGCHLD,action);
    if (fork()==0) // P1
    {   int fd[2]; pipe(fd); // pour 2
        if(fork()!=0) // P1
        {  sleep(2);
           char c; 
           dup2(fd[0],0); close(fd[0]); close(fd[1]); // pour 2       
           while(read(0,&c,1)>0)
               write(1,&c,1);
            wait(NULL);
            _exit(0);
        } // P2
        dup2(fd[1],1); close(fd[0]); close(fd[1]); // pour 2
        execl("/bin/ls", "ls", NULL);
        _exit(1);
    }
     wait(NULL);
     return 0;
}



