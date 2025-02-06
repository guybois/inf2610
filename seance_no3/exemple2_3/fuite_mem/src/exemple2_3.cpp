/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Fonction qui évite la fuite de mémoire - si pthread_cleanup_pop(0) n'est pas exécuté mfree(tab) est exécuté
void mfree (void *arg) {
printf("free arret anormal - on libere l'espace et on évite les fuites...\n"); free(arg); }

// fonction mthread
void *mthread(void *taille)
{    // allouer dynamiquement un tableau 
    long*tab = (long*) malloc ( (long)taille*sizeof(long));

    if (tab!=NULL)
    {   // remplir le tableau
    pthread_cleanup_push(mfree, (void*) tab);  // met sur la pile d'exécution du thread l'appel à mfree(tab)
        for (long i=0; i<(long)taille; i++) 
            tab[i]=i;

// Simuler l'annulation du thread - si vous metttez la ligne suivante en commentaire on aura une fin normale et sinon anormale...
    pthread_exit(NULL);    // si on exécute ce code on met fin à l'exécution du thread ce qui du coup va provoquer mfree(tab) pour remettre l'espace de mémoire dynamique (heap)

        printf("\n fin de remplissage\n");
    pthread_cleanup_pop(0);   // si on se rend ici on retire mfree(tab) de la pile car le pointeur sur tab va être tranférer au thread principal  et un free sera fait
    }
    // retourner l'adresse du tableau (récupérable via pthread_join) 
    pthread_exit ((void*) tab);
}


int main() {
    pthread_t th;
    long* pstatus;
    if(pthread_create(&th,NULL,mthread,(void*)5))   return 1;
//    pthread_cancel(th);
    pthread_join(th, (void**) &pstatus);
    if(pstatus != PTHREAD_CANCELED && pstatus!=NULL ) { 
        printf("Terminaison normale avec pstatus=%p.\n", pstatus);
        // afficher le contenu du tableau
        for(int i=0; i<5;i++)
            printf("tab[%d]=%ld ", i, pstatus[i]);
        printf("\n fin de l'affichage \n");
        // libérer l'espace alloué au tableau
        printf("thread principal fin normal - on libere l'espace\n"); 
        free(pstatus);  // libération de l'espace mémoire dynamique (heap)
    }
    return 0;
}