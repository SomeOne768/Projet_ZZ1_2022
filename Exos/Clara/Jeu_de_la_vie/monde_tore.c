#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "monde_tore.h"

int nb_voisint(char ** Matrice, int n, int m, int a, int b )
{
    int nombre=0;
    int ligne,colonne;
    for (ligne=(a-1); ligne<(a+2); ligne ++)
    {
    
            for (colonne=(b-1); colonne<(b+2); colonne++)
            {
                
                
                     if(ligne<0)
                     {
                        ligne = n+ligne;  //pour resoudre bug car sinon (-1%n=-1%172=-1....)
                     }
                     if(colonne<0)
                     {
                        colonne= n+colonne;

                     }
                    //printf(" %d %d %d; %d\n", ligne, n, (ligne%n), (colonne)%m);
                    
                    if ( !(ligne==a && colonne==b) && Matrice[(ligne)%n][(colonne)%m]==1)
                    {
                        nombre++;
                    }
                
            }
        
    }

 return nombre;

}

void nvlle_matricet(char** avant, char** apres, int n, int m, int *Birth, int * Survive)
{
    for (int i=0; i<n;i++)
    {
        for (int j=0; j<m; j++)
        {
            int nombre_voisins=nb_voisint(avant,n, m, i, j);
            if (avant[i][j]==0)
            {
                if (Birth[nombre_voisins]==1)
                {
                    apres[i][j]=1;
                }
                else{
                    apres[i][j]=0;
                }

            }
            else
            {
                if (Survive[nombre_voisins]==1)
                {
                    apres[i][j]=1;
                }
                else
                {
                    apres[i][j]=0;
                }
            }
        }
    }

}

