#include <stdio.h>
#include "regle.h"
#include <stdlib.h>




/*******************************************************************************/

//Récuperation des règles
//Format de regle attendu : "B12/S27" -> naissance si 1 ou 2 voisins et survit si 2 ou 7 et non entre 2 et 7
int extraire_regle(char *saisie, char *B, char *S)
{
    //Ici on suppose que la saisie est correcte (format  + toujours B and S)
    //Mémoire pour B et S allouée avant
    
    //Initialisation de nos tableaux de retour
    int i;
    for(i=0; i<9; i++)
    {
        B[i] = 0;
        S[i] = 0;
    }

    //On commence par parcourir les cas de naissance
    i = 1;
    int indice;
    while(saisie[i] != '/')
    {
        //On met case du tableau correspondante à 1
        indice = saisie[i] - '0';
        B[indice] =  1;
        i++;
    }

    //Nous sommes sur le '/' on passe donc à la survie
    i += 2;
    while(saisie[i] != '\0')
    {
        indice = saisie[i] - '0';
        S[i] = 1;
        i++;
    }

    //A faire plus tard vérification et donc retour à 0 si nécessaire
    return 1;

}