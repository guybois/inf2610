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
        printf("ici pere pid=%d, glob=%d, @glob=%p, glob du fils = %d\n",
                 getpid(), glob, &glob, WEXITSTATUS(x));
    return 0;
}

// 1- ici fils pid=5751, glob=99                                                                
//    ici pere pid=5750, glob=101 
// 2- ici fils pid=14908, glob=99, @glob=0x601060                                               
//    ici pere pid=14907, glob=101, @glob=0x601060  
// oui il s'agit de la même adresse virtuelle. L'espace d'adressage du fils 
// est une copie de celle de son père. La variable glob a la même adresse 
// virtuelle dans chacun des deux espaces virtuelles.
// 3 - oui  
