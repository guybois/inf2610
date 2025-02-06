
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
int main() {  int fd[2]; pipe(fd);  
        if(fork()==0) {  close(fd[1]);
             printf("Fils: pid= %d ppid=%d \n", getpid(), getppid());
             int m; while(read(fd[0],&m,sizeof(int))>0)  // 2 conditions pour sortir: 1) le pipe est vide et 2) il n'y a plus d'écrivain suite à l'exécution de la ligne 31
                    printf("Fils: m=%d\n",m);
             close(fd[0]);

 } else {    close(fd[0]);
             srand(time(NULL));
             int n;  
             for( int i = 5; i>0; i--) {
                n = rand() % 100;
               printf("Père: pid=%d, n = %d\n", getpid(), n);
               write(fd[1],&n,sizeof(int));
//               sleep(5);
             }     
              close(fd[1]);
              wait(NULL);
     }
     return 0;
}

