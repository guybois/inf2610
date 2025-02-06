/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

Tout comme pour le processus père avec son fils, lors d'un exit un thread peut passer de l'info au thread (programme) principal i.e. le main
C'est le cas ici du pointeur sur tab qui est transférer au thread principal, imprimer et libérer

*******************************************************************************/
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// fonction mthread
void *mthread(void *taille)
{    // allouer dynamiquement un tableau 
long*tab = (long*) malloc ( (long)taille*sizeof(long));
    if (tab!=NULL)
    {   // remplir le tableau
        for (long i=0; i<(long)taille; i++) 
            tab[i]=i;
        printf("\n fin de remplissage \n");
    }
    // retourner l'adresse du tableau (récupérable via pthread_join) 
    pthread_exit ((void*) tab);
}


int main() {
    pthread_t th;
    long* pstatus;
    if(pthread_create(&th,NULL,mthread,(void*)5))   return 1;
    pthread_join(th, (void**) &pstatus);
    // On s'arrure dans ce qui suit que la fin est normale et que le pointeur sur tab n'est pas nul
    // sinon on a pas à imprimer et libérer la mémoire alloué dynamiquement.
    if(pstatus != PTHREAD_CANCELED && pstatus!=NULL ) { 
        printf("Terminaison normale avec pstatus=%p.\n", pstatus);
        // afficher le contenu du tableau
        for(int i=0; i<5;i++)
            printf("tab[%d]=%ld ", i, pstatus[i]);
        printf("\n fin de l'affichage \n");
        // libérer l'espace alloué au tableau
        free(pstatus);
    }
    return 0;
}

