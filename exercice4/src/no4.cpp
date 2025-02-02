/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{    printf(" pid=%d, ppid=%d\n", getpid(),getppid());
     if (fork() == 0) // F1
     {  printf(" pid=%d, ppid=%d\n", getpid(),getppid());
     
        if(fork()==0) // F4
        {  printf(" pid=%d, ppid=%d\n", getpid(),getppid());
            char com[100];
           sprintf(com, " Ici processus %d de père %d ", getpid(), getppid());
           execl("/bin/echo", "echo", com, NULL);
        } 
        wait(NULL);
        _exit(0);
     }
     
     if (fork() == 0 ) // F2
     {   printf(" pid=%d, ppid=%d\n", getpid(),getppid());
     
         if(fork()==0) // F5
         { printf(" pid=%d, ppid=%d\n", getpid(),getppid()); 
           char com[100];
           sprintf(com, " Ici processus %d de père %d ", getpid(), getppid());
           execl("/bin/echo", "echo", com, NULL);
        } 
         
         if(fork()==0) // F6
         {  printf(" pid=%d, ppid=%d\n", getpid(),getppid());
            char com[100];
             sprintf(com, " Ici processus %d de père %d ", getpid(), getppid());
             execl("/bin/echo", "echo", com, NULL);
          } 
          wait(NULL); wait(NULL);
          _exit(0);
     }
     
     if (fork()==0) // F3
     {    printf(" pid=%d, ppid=%d\n", getpid(),getppid());
     
          if(fork()==0) // F7
         {  printf(" pid=%d, ppid=%d\n", getpid(),getppid());
            char com[100];
             sprintf(com, " Ici processus %d de père %d ", getpid(), getppid());
             execl("/bin/echo", "echo", com, NULL);
          } 
          wait(NULL); _exit(0);
     }
     
   while(wait(NULL)>0);
   return 0;
}

