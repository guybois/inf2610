
/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
int main( ) {
        int fd[2]; pipe(fd);
     if (fork()==0) { // premier fils
            printf("fils de pid=%d se transforme en ls \n",getpid());
            dup2(fd[1],1);   // fd[1] est l’extrémité d'écriture, on redirige la sortie standard dans fd[1]
                             // Désormais, tout ce qui sera écrit sur stdout ira dans le pipe
            close(fd[0]); close(fd[1]);     // on peut donc fermer les 2 descripteurs
            execl("/bin/ls","ls",NULL);
            _exit(1);
    }  
    
    if (fork()==0) { // second  fils
            printf("fils de pid=%d se transforme en sort \n",getpid());
           dup2(fd[0],0);  // fd[0] est l’extrémité de lecture, on redirige l'entrée standard  dans fd[0]
                           // Désormais, tout ce qui sera lu sur stdin ira dans le pipe
           close(fd[0]); close(fd[1]);   // on peut donc fermer les 2 descripteurs
           execl("/bin/sort","sort", NULL);
           _exit(1);
    } 
    int pid; close(fd[0]); close(fd[1]);
    while ((pid=wait(NULL)) > 0)
    printf("fin du fils de pid=%d\n", pid);
    return 0;
}



