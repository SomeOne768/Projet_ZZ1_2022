#include <stdlib.h>
#include <stdio.h>
#include "regles.h"


// format de saisie par l'utilisateur exemple B45/S258 : naissance si 4 ou 5 voisins et survie si 2 ou 5 ou 8 voisins
void extraire_regles(char *saisie, int *Birth, int *Survive)
{
    for (int i=0; i<9; i++)
    {
        Birth[i]=0;
        Survive[i]=0;
    }

    //cas birth
    int i;
    int indice;
    while (saisie[i]!='/')
    {
        indice=saisie[i]-'0';
        Birth[indice]=1;
        i++;
    }
    i++; //on passe apres le slash
    //cas survive
    while (saisie[i]='\0')
    {
        indice=saisie[i]-'0';
        Survive[indice]=1;
        i++;
    }

}
