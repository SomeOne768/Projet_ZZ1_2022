#include <stdio.h>
#include <SDL2/SDL.h>
#include "gestionSDL2.h"

/*********************************************************************************************************************/
/* Programme qui gère l'affichage de plusieurs fenetres en les faisant tourner autour d'un axe, et en les ecartant   */
/*********************************************************************************************************************/

int main(int argc, char **arv)
{
	SDL_version nb;
	SDL_VERSION(&nb);

	printf("Version: %d %d %d\n", nb.major, nb.minor, nb.patch);

	//Ouverture en mode Vidéo et test 
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Problème initialisation de la SDL: %s", SDL_GetError());
        exit(1);
    }

    //Nombre de cercles désirés:
    int n = 9;
    int centre_x =700;
    int centre_y =300;
    int delay = 10;

	//On passe à l'affichage du cercle cosima
	SDL_Window** tab = Cosima_Circle(centre_x, centre_y, n, 100);
	
	//On les separe chacun dans une direction
	Circle_Extension(tab,  n, centre_x,
                        centre_y,  100, 200, delay);

	//On les fait tourner autour d'un axe
	rotation(tab, n, 700, 300, 200, delay);

	//on le fait se rassembler
	Circle_Extension(tab,  n, centre_x,
                        centre_y,  200, 100, delay);
	
	//On oublie pas de libérer la mémorie
	LiberationTabWindow(tab, n);
	SDL_Quit();

	return 0;
}