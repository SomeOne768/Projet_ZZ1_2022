#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <string.h>

void extraire_regles(char *saisie, int *Birth, int *Survive)
{
    for (int i=0; i<9; i++)
    {
        Birth[i]=0;
        Survive[i]=0;
    }

    //cas birth
    int i=1;
    int indice;
    while (saisie[i]!='/')
    {
        indice=saisie[i]-'0';
        Birth[indice]=1;
        i++;
    }
    i+=2; //on passe apres le slash et le S
    //cas survive
    while (saisie[i]!='\0')
    {
        indice=saisie[i]-'0';
        Survive[indice]=1;
        i++;
    }

}

int main()
{
    char * saisie="B12/S456";
    int B[9], S[9];
    extraire_regles(saisie,B,S);
    printf("Birth:    ");
    for (int i=0; i<9;i++)
    {
        printf("%d", B[i]);
    }
    printf("\n");

    printf("Survive:    ");
    for (int i=0; i<9;i++)
    {
        printf("%d", S[i]);
    }
    printf("\n");
    return 0;

}