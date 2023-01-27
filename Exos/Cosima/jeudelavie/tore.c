#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>
#include "tore.h"




int nb_voisins_tore(char ** matrice, int n, int m, int x, int y)
{
    //compte le nombre de voisins autour de la case x, y
    int nombrevoisins = 0;

    for (int a=x-1; a<x+2; a++)
    {
        if (a>=0 && a<n)
        {
            for (int b=y-1; b<y+2; b++)
            {
                if(b>=0 && b<m && !(a==x && b==y))
                {
                    if(matrice[a%n][b%m]==1)
                        nombrevoisins++;
                }
            }
        }
        
    }
    return nombrevoisins;
}


int future_case_tore(char ** matrice, int x, int y, int n, int m, char* B, char *S)
{
    int vivante = 0;
    int voisins = nb_voisins_tore(matrice, n, m, x, y);

    if (matrice[x][y] == 1) //cellule vivante
    {
        if(S[voisins] == 1)
            vivante = 1;
    }
    else
    {
        if(B[voisins] == 1)
            vivante = 1;
    }
    return vivante;
}


void future_matrice_tore(char ** matrice, int n, int m, char* B, char *S, char ** future_matrice)
{
    for (int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            future_matrice[i][j] = future_case_tore(matrice, i, j, n, m, B, S);
        }
    }
}
