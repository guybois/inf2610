/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

Suite de l'exemple2_1 qui montre l'utilisation de pthread_cancel et PTHREAD_CANCELED

*******************************************************************************/
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// fonction mthread
void *mthread(void *taille)
{    // allouer dynamiquement un tableau 

// Simuler une protection du thread à un pthread_cancel - si la ligne suivante n'est pas en commentaire on aura une fin anormale...
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);
    long*tab = (long*) malloc ( (long)taille*sizeof(long));
    sleep(2); // attendre 2 s

    if (tab!=NULL)
    {   // remplir le tableau
        for (long i=0; i<(long)taille; i++) 
            tab[i]=i;
        printf("\n fin de remplissage\n");
    }
    // retourner l'adresse du tableau (récupérable via pthread_join) 
    pthread_exit ((void*) tab);
}


int main() {
    pthread_t th;
    long* pstatus;
    if(pthread_create(&th,NULL,mthread,(void*)5))   return 1;

    // Pendant que le thread ci-haut attend 2 sec., le thread pricipal (main) va le cancellé...
    // Si le thread ci-haut ne s'est pas prémuni de la ligne 21 (i.e. il peut être cancellé) ce dernier aura alors une fin anormale avec l'instruction suivante:
    pthread_cancel(th);

    pthread_join(th, (void**) &pstatus);

    // On s'arrure dans ce qui suit que la fin est normale et que le pointeur sur tab n'est pas nul
    // sinon a pas à imprimer et libérer la mémoire alloué dynamiquement.
    // si pstatus == PTHREAD_CANCELED on a une fin anormale..
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

