#include <stdio.h>
#include "gestionSDL2.h"
#include <math.h>

/*
 *	initialisation de la SDL
 *	SDL_INIT_TIMER: timer subsystem
 *	SDL_INIT_AUDIO: audio subsystem
 * 	SDL_INIT_VIDEO: video subsystem; automatically initializes the events subsystem
 * 	SDL_INIT_JOYSTICK: joystick subsystem; automatically initializes the events subsystem
 * 	SDL_INIT_HAPTIC: haptic (force feedback) subsystem
 * 	SDL_INIT_GAMECONTROLLER: controller subsystem; automatically initializes the joystick subsystem
 * 	SDL_INIT_EVENTS: events subsystem
 * 	SDL_INIT_EVERYTHING: all of the above subsystems
 * 	SDL_INIT_NOPARACHUTE: compatibility; this flag is ignored
 *  SDL quit à la fin
*/


//Création d'une fenêtre:
/*SDL_Window * SDL_CreateWindow(const char *title,
                              int x, int y, int w,
                              int h, Uint32 flags);
                              //Par défaut flags à 0
*/

//Fonction pour cosima

SDL_Window** Cosima_Circle(int centre_x, int centre_y, int n, int rayon)
{
    //NECESSITE d'avoir ouvert en video
    
    int R = rayon;
    float pi = 3.14159;
    int posx, posy;
    int hauteur = 50, largeur = 50;
    float isima; //Angle du cosinus actuel [cos(isima) ma collègue de groupe ahaha]

    //On commence par créer nos n cercles + affichage
    SDL_Window **tab = NULL;
    tab = (SDL_Window**)malloc(sizeof(SDL_Window*) * n);
    for(int i=0; i<n; i++)
    {
        isima = 2 * pi * i/n;
        posx = centre_x + (int) R * cos(isima);
        posy = centre_y - (int) R * sin(isima);
        tab[i] = SDL_CreateWindow("Projet Cosima",
                              posx, posy, largeur,
                              hauteur, 0);
        if(!tab[i])
        {
            fprintf(stderr, "Problème création fenetre.\n");

            //On libère les autres
            for(int j=i-1; j>=0; j--)
            {
                SDL_DestroyWindow(tab[i]);
                
            }
            free(tab);
            tab=NULL;
        }
    }

    return tab;


    //on les faits ensuite entrer et ressortir (fn a part)
}



//On fait maintenant tourner les cercles;

void rotation(SDL_Window **tab,  int n, int centre_x, int centre_y, int R, int delay)
{

    //On leur fait faire un tour
    //On prends donc leur position de départ et chacun effectue le même pas de rotation
    float *isima=(float*)malloc(sizeof(float) * n);
    float pi = 3.14159;
    int i;

    //Position des angles au départ
    for(i=0; i<n; i++)
    {   
        isima[i] = 2*pi*i/n;
    }

    //On met à jour les positions toutes les 0.5sec
    int nombre_rotation = 100;//Chaque angle aurat 10 positions
    int posx, posy;
    for(int j=0; j<nombre_rotation; j++)
    {
        //On redonne à chaque fenetre une position
        for(i=0; i<n; i++)
        {
            posx = centre_x + R * cos(isima[i] + 2*pi*j/nombre_rotation);
            posy = centre_y - R * sin(isima[i] + 2*pi*j/nombre_rotation);
            SDL_SetWindowPosition(tab[i], posx, posy);

        }
        SDL_Delay(delay);
    }

    free(isima);

}


void Circle_Extension(SDL_Window **tab,  int n, int centre_x,
                        int centre_y, int R_debut, int R_fin, int delay)
{
    
    //On prends donc leur position de départ et chacun effectue le même pas de rotation
    float *isima=(float*)malloc(sizeof(float) * n);
    float pi = 3.14159;
    int i;

    //Position des angles au départ
    for(i=0; i<n; i++)
    {   
        isima[i] = 2*pi*i/n;
    }

    //Position de départ
    int posx, posy; 
    float *posX=malloc(sizeof(int)*n);
    float *posY=malloc(sizeof(int)*n);//Pour avoir plus de précision

    for(int i=0; i<n; i++)
    {
        //Récupération des positions
        SDL_GetWindowPosition(tab[i], &posx, &posy);
        posX[i] = posx;
        posY[i] = posy;
    }

    int incrementation = 2;


    if(R_debut > R_fin)
    {
        incrementation = -incrementation;
    }

    int nombre_incrementation = abs(R_fin - R_debut) / abs(incrementation);

    for(int j= 0; j<nombre_incrementation; j++)
    {
        
        for(int i=0; i<n; i++)
        {
            //Maj des positions
            posX[i] += incrementation * cos(isima[i]);
            posY[i] -= incrementation * sin(isima[i]);
            SDL_SetWindowPosition(tab[i], posX[i], posY[i]);
        }

        SDL_Delay(delay);
    }
    free(isima);
    free(posX);
    free(posY);

}
//libération mémoire tableau

void LiberationTabWindow(SDL_Window **tab, int n)
{
    if(tab)
    {
        int i;
        for(i=0; i<n; i++)
        {
            SDL_DestroyWindow(tab[i]);
            free(tab[i]);
        }
        free(tab);
        tab = NULL;
    }

}


