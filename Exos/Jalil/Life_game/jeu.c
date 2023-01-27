#include <stdio.h>
#include <stdlib.h>
#include "jeu.h"
#include <time.h>

char** CreerMatrice(int n, int m)
{
    //On utilise des char car un short int est sur 2 octets
    //Pas de gestion d'erreur d'allocation, on est riche on a beaucoup de mémoire
    char **tab = (char**)malloc(sizeof(char*) * n);
    for(int i=0; i<n; i++)
    {
        tab[i] = (char*)malloc(sizeof(char)*m);
    }

    return tab;
}


void Affichage_Sans_Trait_Comme_Paul_Nautre_No_Trait(SDL_Renderer* renderer, char **M, int n, int m, int h)
{
    //Affichage de la matrice sans les traits Comme Paul Nautrè 
    //Matrice de 0 et de 1
    //Si 1 dessiner un rectangle de dimension h
    SDL_Rect rectangle;

    //Carré noir
    SDL_SetRenderDrawColor(renderer,                                                
                         0, 0, 0,                                  // mode Red, Green, Blue (tous dans 0..255)
                         255);
    
    rectangle.w = h;
    rectangle.h = h;

    //On dessine tous les carrés de la nouvelle matrice
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            if(M[i][j])
            {
                //On doit dessiner un carré
                rectangle.x = j*h;
                rectangle.y = i*h;
                SDL_RenderFillRect(renderer, &rectangle); 
            }
        }
    }
}


void draw(SDL_Renderer* renderer, char **M, int n, int m, int h)
{
    //Version avec des traits affichés
    //Matrice de 0 et de 1
    //Si 1 dessiner un rectangle de dimension h
    SDL_Rect rectangle;

    //Carré noir
    SDL_SetRenderDrawColor(renderer,                                                
                         0, 0, 0,                                  // mode Red, Green, Blue (tous dans 0..255)
                         255);
    
    rectangle.w = h-1;
    rectangle.h = h-1;

    //On dessine tous les carrés de la nouvelle matrice
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            if(M[i][j])
            {
                //On doit dessiner un carré
                rectangle.x = j*h;
                rectangle.y = i*h;
                SDL_RenderFillRect(renderer, &rectangle); 
            }
        }
    }
}


void LiberationMatrice(char **M, int n)
{
    if(M)
    {
        for(int i=0; i<n; i++)
        {
            free(M[i]);
            M[i] = NULL;
        }

        free(M);
        M = NULL;
    }
}



int nombre_voisin(char **M, int n, int m, int i, int j)
{
    //On compte le nombre de voisins vivant dupoint i j
    int compteur = 0;

    int line, col;//positions réelles
    int ligne, colonne; //Positions relatives
    for(line = i-1; line< i+2; line++)
    {
        ligne = line;

        
        //Monde delimite donc on ne compte pas les cases du haut
        if(ligne>=0 && ligne<n)
        {
            for(col=j-1; col<j+2; col++)
            {
                colonne = col;
                if( !(ligne==i && colonne==j) && colonne>=0 && colonne<m &&  M[ligne][colonne])
                {
                    compteur++;
                }
            }
        }
    }

    return compteur;
}


void evolution_matrice(char **avant, char **apres, int n, int m, char *B, char *S)
{

    //On compte le nombre de voisin vivant de chaque cellule
    //Pour cela on les parcourt et en fonction des regles elles deviennent vivantes ou non

    int nb_voisin;
    for(int i=0; i<n; i++)
    {
        
        for(int j=0; j<m; j++)
        {
            nb_voisin = nombre_voisin(avant, n, m, i, j);
            if(!avant[i][j])
            {
                //Cellule morte, on regarge si elle doit naitre
                if(B[nb_voisin])
                {
                    //La cellule doit naitre
                    apres[i][j] = 1;
                }
                else
                {
                    apres[i][j] = 0;
                }
            }
            else
            {
                //Cellule vivante, on regarde si elle peut survivre
                if(!S[nb_voisin])
                {
                    //Elle doit CRevez (Comme Cosima Revez ma collegue)
                    apres[i][j] = 0;
                }
                else{
                    apres[i][j] = 1;
                }
            }            
        }
    }


}



int nombre_voisin_thorique(char **M, int n, int m, int i, int j)
{
    //On compte le nombre de voisins vivant dupoint i j
    int compteur = 0;

    int line, col;//positions réelles
    int ligne, colonne; //Positions relatives
    for(line = i-1; line< i+2; line++)
    {
        ligne = line;

                
        //Monde delimite donc on ne compte pas les cases du haut
        if(ligne<0)
        {
            ligne += n;
        }
        else if(ligne >= n)
        {
            ligne -= n;
        }

        for(col=j-1; col<j+2; col++)
        {
            colonne = col;
            if(colonne<0)
            {
                colonne += m;
            }
            else if (colonne>= m)
            {
                colonne -= m;
            }

            if( !(ligne==i && colonne==j) &&  M[ligne][colonne] )
            {
                compteur++;
            }
        }
    }

    return compteur;
}


void evolution_matrice_thorique(char **avant, char **apres, int n, int m, char *B, char *S)
{

    //On compte le nombre de voisin vivant de chaque cellule
    //Pour cela on les parcourt et en fonction des regles elles deviennent vivantes ou non

    int nb_voisin;
    for(int i=0; i<n; i++)
    {
        
        for(int j=0; j<m; j++)
        {
            nb_voisin = nombre_voisin_thorique(avant, n, m, i, j);
            if(!avant[i][j])
            {
                //Cellule morte, on regarge si elle doit naitre
                if(B[nb_voisin])
                {
                    //La cellule doit naitre
                    apres[i][j] = 1;
                }
                else
                {
                    apres[i][j] = 0;
                }
            }
            else
            {
                //Cellule vivante, on regarde si elle peut survivre
                if(!S[nb_voisin])
                {
                    //Elle doit CRevez (Comme Cosima Revez ma collegue)
                    apres[i][j] = 0;
                }
                else{
                    apres[i][j] = 1;
                }
            }            
        }
    }
}




int estStable(char **M1, char **M2, int n, int m)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            if(M1[i][j] != M2[i][j])
            {
                return 0;
            }
        }
    }
    return 1;
}

void MatriceCreuse(char **Matrice_avant, int n, int m)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            Matrice_avant[i][j] = 0;
        }
    }
}

void MatriceRandom(char **Matrice_avant, int n, int m)
{
    srand(time(NULL));
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            Matrice_avant[i][j] = rand()%2;
        }
    }
}

void colorerMatrice(char **M, int taille_carre, int x, int y)
{
    int i = y/taille_carre;
    int j = x/taille_carre;
    M[i][j] = 1;

}

char** user_matrix(SDL_Renderer *renderer, int n, int m, int taille_carre)
{
    char **M = CreerMatrice(n,m);
    MatriceCreuse(M, n, m);
    
    //effacement
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);    
    SDL_RenderPresent(renderer);
    
    SDL_Event event;
    int x,y;
    int fini = 0;
    while(!fini)
    {
        while(!fini && SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_RETURN)
                    {
                        fini = 1;
                    }
                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                    x = event.motion.x;
                    y = event.motion.y;
                    colorerMatrice(M, taille_carre, x, y);
                    draw(renderer, M, n, m, taille_carre); 
                    break;

                default: 
                    break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        draw(renderer, M, n, m, taille_carre);                // appel de la fonction qui crée l'image  
        SDL_RenderPresent(renderer);                      // affichage
        SDL_Delay(50);
    }
    return M;
}

void enregistrerMatrice(char **M, int n, int m, char *filemane)
{

    //Comme on sait que notre programme n'aurat pas énormément de succès
    //On écrase le fichier s'il existe

    FILE *f = fopen(filemane, "w+");
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
            fprintf(f, "%d ", (int)M[i][j]);
        }
    }
    printf("Le jeu a été enregistré.\n");
    fclose(f);    
}

char** chargerMatrice(char *filename)
{
    char **tab = NULL;

    FILE *f = fopen(filename, "r");

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
    tab = CreerMatrice(n, m);

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
        if(i<n) tab[i][j] = recup;
        j++;
    }
    

    return tab;
}