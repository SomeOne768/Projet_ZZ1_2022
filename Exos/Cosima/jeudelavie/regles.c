#include <stdio.h>
#include "regles.h"

//l'utilisateur entre une chaine de caractères de la forme : "B45/S38"
void regles(char * saisie, char *B, char *S)
{
    for (int k=0; k<9; k++)
    {
        B[k] = 0;
        S[k] = 0;
    }
    int i = 1;
    int indice;
    while (saisie[i] != '/')
    {
        indice = saisie[i] - '0';
        B[indice] = 1;
        i++;
    }
    i++;
    while (saisie[i] != '\0')
    {
        indice = saisie[i] - '0';
        S[indice] = 1;
        i++;
    }
}
