
/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>  // pour printf
#include <stdlib.h>  // pour rand and srand
#include <time.h> // pour time  
#include <unistd.h>  // pour write, read, pipe and close
#include <sys/wait.h> // pour wait
#include <fcntl.h> // pour open
#include <sys/types.h>  // pour mkfifo
#include <sys/stat.h>  // pour mkfifo
int main() { mkfifo("tube",0600);
   if(fork()==0) {
             int fd=open("tube",O_RDONLY);
             printf("pid= %d ppid=%d \n", getpid(), getppid());
             int m; while(read(fd,&m,sizeof(int))>0) 
                    printf("Fils: m=%d\n",m);
             close(fd);
} else {     srand(time(NULL));
             int n;  
             int fd=open("tube",O_WRONLY);
             for( int i = 5; i>0; i--) {  n = rand() % 100;
                     printf("pid=%d, n = %d\n", getpid(), n);
                     write(fd,&n,sizeof(int));    
             }     
         close(fd);
         wait(NULL);
       }
     return 0;
}


