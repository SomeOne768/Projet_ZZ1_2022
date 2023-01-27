#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "monde_limite.h"


char **CreerMatrice(int n, int m)
{
    char **tab = (char **)malloc(sizeof(char *) * n);
    for (int i = 0; i < n; i++)
    {
        tab[i] = (char *)malloc(sizeof(char) * m);
    }

    return tab;
}

void Liberation_matrice(char **M, int n)
{
    if (M)
    {
        for (int i = 0; i < n; i++)
        {
            free(M[i]);
            M[i] = NULL;
        }
        free(M);
        M = NULL;
    }
}

void draw(SDL_Renderer *renderer, char **M, int n, int m, int h)
{
    SDL_Rect rectangle;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // 0 = transparent ; 255 = opaque

    rectangle.w = h; // sa largeur (w = width)
    rectangle.h = h; // sa hauteur (h = height)

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (M[i][j])
            {
                rectangle.x = j * h;
                rectangle.y = i * h;
                SDL_RenderFillRect(renderer, &rectangle);
            }
        }
    }
}

int nb_voisin(char **Matrice, int n, int m, int a, int b)
{
    int nombre = 0;
    int ligne, colonne;
    for (ligne = a - 1; ligne < a + 2; ligne++)
    {
        if (ligne >= 0 && ligne < n)
        {
            for (colonne = b - 1; colonne < b + 2; colonne++)
            {
                if (colonne >= 0 && colonne < m)
                {
                    if (!(ligne == a && colonne == b) && Matrice[ligne][colonne] == 1)
                    {
                        nombre++;
                    }
                }
            }
        }
    }

    return nombre;
}

int etatstable(char ** Mat1, char** Mat2,int n,int m)
{
	int stable=1;
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<m; j++)
		{
			if (!(Mat1[i][j]==Mat2[i][j]))
			{
				stable=0;
			}
		}
	}
	return stable;
}

void nvlle_matrice(char **avant, char **apres, int n, int m, int *Birth, int *Survive)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int nombre_voisins = nb_voisin(avant, n, m, i, j);
            if (avant[i][j] == 0)
            {
                if (Birth[nombre_voisins] == 1)
                {
                    apres[i][j] = 1;
                }
                else
                {
                    apres[i][j] = 0;
                }
            }
            else
            {
                if (Survive[nombre_voisins] == 1)
                {
                    apres[i][j] = 1;
                }
                else
                {
                    apres[i][j] = 0;
                }
            }
        }
    }
}


void enregistrerMatrice(char **Matrice, int n, int m, char *fichier)
{

    //Comme on sait que notre programme n'aurat pas énormément de succès
    //On écrase le fichier s'il existe

    FILE *f = fopen(fichier, "w+");
    if(!f)
    {
        fprintf(stderr, "problème création fichier\n");
        exit(1);
    }
    //On commence par enregistrer le nombre de ligne/colonne
    fprintf(f, "%d %d", n, m);
    
    for(int i=0; i<n; i++)
    {
        fprintf(f, "\n");
        for(int j=0; j<m; j++)
        {
            //On récupère 
            fprintf(f, "%d ",(int)Matrice[i][j]);
        }
    }
    fclose(f);    
}

void colorerMatrice(char **M, int taille_carre, int x, int y)
{
    int i = y/taille_carre;
    int j = x/taille_carre;
    M[i][j] = 1;

}


char** chargerMatrice(char *fichier)
{
    char **tab = NULL;

    FILE *f = fopen(fichier, "r");

    if(!f)
    {
        fprintf(stderr, "Probleme ouverture fichier \n");
        exit(1);
    }

    //Récupération des dimensions de la matrice
    int n,m;
    fscanf(f, "%d", &n);
    fscanf(f, "%d", &m);

    //Allocation mémoire de la matrice
    int i,j;
    tab = (char**)malloc(sizeof(char*)*n);
    for(i=0; i<n; i++)
    {
        tab[i] = (char*)malloc(sizeof(char)*m);
    }

    //Initialisation de la matrice
    i = 0;
    j = 0;
    int recup;
    while(!feof(f))
    {
        if(j==m)
        {
            i++;
            j = 0;
        }
        fscanf(f, "%d", &recup);
        if(i<n)tab[i][j] = recup;
        j++;
    }
    

    return tab;
}

