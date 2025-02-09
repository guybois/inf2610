/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int glob=100;
int main()
{
       if(fork()==0)
        {   glob=glob-1;
            printf("ici fils pid=%d, glob=%d, @glob=%p\n", 
                     getpid(), glob, &glob);
            _exit(glob);  
        }
        int x; wait(&x); 
        glob=glob+1;
        // WEXITSTATUS(status) extrait le parametre de retour du fils, ici la valeur glob du fils
        printf("ici pere pid=%d, glob=%d, @glob=%p, glob du fils = %d\n",
                 getpid(), glob, &glob, WEXITSTATUS(x));
    return 0;
}
