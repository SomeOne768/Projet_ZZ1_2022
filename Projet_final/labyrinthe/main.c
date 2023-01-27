#include <stdio.h>
#include "labyrinthe.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include "affichage_laby.h"

char *filename = "monde3.txt";
char *apprentissage = "Laby_monde3.txt";

// Chargement d'un apprentissage
void chargerMatrice(double **M, int n, int m, char *filename)
{
  FILE *f = fopen(filename, "r");
  if (f)
  {
    int i = 0, j = 0;
    double rejet;
    fseek(f, 0, SEEK_SET);
    while (!feof(f))
    {
      fscanf(f, "%lf", &rejet);
      if (i < n)
      {
        M[i][j] = rejet;
        j++;
        if (j == m)
        {
          j = 0;
          i++;
        }
      }
    }
    fclose(f);
  }
  else
  {
    printf("J'ai pas reussi à charger hahahaaha\n");
    exit(-1);
  }
}

void LibererMatrice(double **M, int n)
{
  for (int i = 0; i < n; i++)
    free(M[i]);
  free(M);
}

void end_sdl(char ok,            // fin normale : ok = 0 ; anormale ok = 1
             char const *msg,    // message à afficher
             SDL_Window *window, // fenêtre à fermer
             SDL_Renderer *renderer)
{ // renderer à fermer
  char msg_formated[255];
  int l;

  if (!ok)
  { // Affichage de ce qui ne va pas
    strncpy(msg_formated, msg, 250);
    l = strlen(msg_formated);
    strcpy(msg_formated + l, " : %s\n");

    SDL_Log(msg_formated, SDL_GetError());
  }

  if (renderer != NULL)
  {                                // Destruction si nécessaire du renderer
    SDL_DestroyRenderer(renderer); // Attention : on suppose que les NULL sont maintenus !!
    renderer = NULL;
  }
  if (window != NULL)
  {                            // Destruction si nécessaire de la fenêtre
    SDL_DestroyWindow(window); // Attention : on suppose que les NULL sont maintenus !!
    window = NULL;
  }

  SDL_Quit();

  if (!ok)
  { // On quitte si cela ne va pas
    exit(EXIT_FAILURE);
  }
}

double **init_matrice_cosimienne(int n, int m)
{

  double **Cosimienne = (double **)malloc(sizeof(double *) * n);

  int i;
  for (i = 0; i < n; i++)
  {
    Cosimienne[i] = (double *)calloc(m, sizeof(double));
  }

  return Cosimienne;
}
7
void enregistrerMatriceFichier(double **M, int n, int m, char *filename)
{
  FILE *f = fopen(filename, "w+");
  if (f)
  {
    for (int i = 0; i < n; i++)
    {

      for (int j = 0; j < m; j++)
      {
        fprintf(f, "%lf ", M[i][j]);
      }
      fprintf(f, "\n");
    }

    fclose(f);
  }
}

int main()
{

  srand(time(NULL));

  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;

  SDL_DisplayMode screen;

  /*********************************************************************************************************************/
  /*                         Initialisation de la SDL  + gestion de l'échec possible                                   */
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    end_sdl(0, "ERROR SDL INIT", window, renderer);

  SDL_GetCurrentDisplayMode(0, &screen);
  printf("Résolution écran\n\tw : %d\n\th : %d\n",
         screen.w, screen.h);

  /* Création de la fenêtre */
  window = SDL_CreateWindow("Premier dessin",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, screen.w * 0.66,
                            screen.h * 0.66,
                            SDL_WINDOW_OPENGL);
  if (window == NULL)
    end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

  /* Création du renderer */
  renderer = SDL_CreateRenderer(window, -1,
                                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL)
    end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

  // On commence par charger un monde

  SDL_Texture *goal = load_texture_from_image("../img/goal.xcf", window, renderer);
  SDL_Texture *wall = load_texture_from_image("../img/wall.xcf", window, renderer);
  SDL_Texture *perso = load_texture_from_image("../img/srek.png", window, renderer);
  SDL_Texture *road = load_texture_from_image("../img/road.xcf", window, renderer);

  // On definit notre position dans le labyrinthe

  SDL_bool program_on = SDL_TRUE; // Booléen pour dire que le programme doit continuer
  SDL_Event event;                // c'est le type IMPORTANT !!

  int n, m;

  char **M = init_matrice_labyrinthe(filename, &n, &m);

  double **Cosimienne = init_matrice_cosimienne(n * m, 4);
  chargerMatrice(Cosimienne, n * m, 4, apprentissage);

  // Connaitre l'état par rapport à une itération:
  int etat, action, gain; // On passe forcement une fois dans la boucle
  // On commence par générer une suite d'état/action/récompense
  int fini = 0;
  int x, y;
  position(M, n, m, &x, &y);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  affiche_labyrinthe(M, n, m);
  afficherLaby(window, renderer, road, wall, goal, perso, M, n, m);
  SDL_RenderPresent(renderer);
  SDL_Delay(500);

  int ite = 0;
  while (!fini && program_on)
  { // Voilà la boucle des évènements
    // Il est possible d'effectuer une action, on determine laquelle

    //   // Determination de l'état dans lequel on se trouve
    //   etat = h(x, y, m);

    //   action = meilleur_action(Cosimienne, etat);

    //   // On calcul la récompense en fonction de notre action
    //   fini = mouvement(M, n, m, &x, &y, action);
    //   int interessant = 0;

    //   while (!interessant && SDL_PollEvent(&event))
    //   { // si la file d'évènements n'est pas vide : défiler l'élément en tête
    //     // de file dans 'event'
    //     switch (event.type)
    //     {                         // En fonction de la valeur du type de cet évènement
    //     case SDL_QUIT:            // Un évènement simple, on a cliqué sur la x de la fenêtre
    //       program_on = SDL_FALSE; // Il est temps d'arrêter le programme
    //       break;

    //     case SDL_KEYDOWN: // Le type de event est : une touche appuyée
    //                       // comme la valeur du type est SDL_Keydown, dans la partie 'union' de
    //                       // l'event, plusieurs champs deviennent pertinents
    //       interessant = 1;
    //       switch (event.key.keysym.sym)
    //       { // la touche appuyée est ...
    //       // case SDLK_DOWN:
    //       //   program_on = !mouvement_bas(M, n, m, &x, &y);
    //       //   break; // 'p'
    //       // case SDLK_UP:
    //       //   program_on = !mouvement_haut(M, n, m, &x, &y);
    //       //   break; // ou 'SPC'
    //       // case SDLK_RIGHT:
    //       //   program_on = !mouvement_droite(M, n, m, &x, &y);
    //       //   // 'ESCAPE'
    //       //   break;
    //       // case SDLK_LEFT:
    //       //   program_on = !mouvement_gauche(M, n, m, &x, &y); // ou 'q'
    //       //   break;

    //       case SDLK_ESCAPE:

    //         program_on = 0;
    //         break;
    //       default: // Une touche appuyée qu'on ne traite pas
    //         interessant = 0;
    //         break;
    //       }

    //     default: // L'évènement défilé ne nous intéresse pas
    //       break;
    //     }
    //   }

    //   printf("ite:%d\n", ite);
    //   affiche_labyrinthe(M, n, m);
    //   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // SDL_RenderClear(renderer);
    // affiche_labyrinthe(M, n, m);
    // afficherLaby(window, renderer, road, wall, goal, perso, M, n, m);
    // SDL_RenderPresent(renderer);
    //   SDL_Delay(600);
    //       ite++;

    program_on = faire_les_courses(window, renderer, road, wall, goal, perso, M, n, m, Cosimienne, &fini);
  }

  LibererMatrice(Cosimienne, n * m);
  LibererLaby(M, n);

  end_sdl(1, "rrr", window, renderer);
  return 0;
}