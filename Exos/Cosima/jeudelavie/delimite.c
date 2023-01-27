#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>
#include "delimite.h"

char ** CreerMatrice(int n, int m)
{
    char ** tab = (char **)malloc(sizeof(char*) * n);
    for (int i=0; i<n; i++)
    {
        tab[i] = (char*)malloc(sizeof(char) * m);
    }
    return tab;
}


void LibererMatrice(int n, char ** tab)
{
    for (int i=0; i<n; i++)
    {
        free(tab[i]);
        tab[i] = NULL;
    }
    free(tab);
    tab = NULL;
}


void drawMatrice(SDL_Renderer* renderer, int n, int m, char ** tab, int taille_carre) 
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_Rect carre;                                                             
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);                                      

    carre.w = taille_carre;                                               
    carre.h = taille_carre;                                                

    for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++)
        {
            if(tab[i][j])
            {
                carre.x = taille_carre*j;                                                  
                carre.y = taille_carre*i; 
                SDL_RenderFillRect(renderer, &carre);
            }
        }
    }                         
}


int nb_voisins_delimite(char ** matrice, int n, int m, int x, int y)
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
                    if(matrice[a][b]==1)
                        nombrevoisins++;
                }
            }
        }
        
    }
    return nombrevoisins;
}


int future_case_delimite(char ** matrice, int x, int y, int n, int m, char* B, char *S)
{
    int vivante = 0;
    int voisins = nb_voisins_delimite(matrice, n, m, x, y);

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


void future_matrice_delimite(char ** matrice, int n, int m, char* B, char *S, char ** future_matrice)
{
    for (int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            future_matrice[i][j] = future_case_delimite(matrice, i, j, n, m, B, S);
        }
    }
}

void echangematrice(int n, int m, char ** matrice, char ** futurematrice)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            matrice[i][j] = futurematrice[i][j];
        }
    }
}

int compareMatrice(char** matrice1, char ** matrice2, int n, int m)
{
    int pareil = 1;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            if(matrice1[i][j] != matrice2[i][j])
                pareil = 0;
            
        }
    }
    return pareil;
}