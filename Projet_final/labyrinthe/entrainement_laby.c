#include <stdio.h>
#include "labyrinthe.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

char *filename = "monde6.txt";
char *save = "Laby_monde6.txt";

void LibererMatrice(double **M, int n)
{
    for(int i=0; i<n; i++)free(M[i]);
    free(M);
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

  // On commence par charger un monde
  
  int n, m;

  char **M = init_matrice_labyrinthe(filename, &n, &m);

  char **copie = malloc(sizeof(char*)*n);
  for(int i=0; i<n; i++)
  {
  	copie[i] = malloc(sizeof(char*)*m);
  	for(int j=0; j<m; j++)
  	{
  		copie[i][j] = M[i][j];
  	}
  }

  // On definit notre position dans le labyrinthe
  int x, y;
  position(M, n, m, &x, &y);
  printf("On est position (%d,%d)\n", x, y);

  // // On evaluer comment faire un mouvement dans ce labyrinthe


  double **Cosimienne = init_matrice_cosimienne(n * m, 4);

  int nb=0, max =200000, p=0;
  double dec = (0.95-0.1)/max, xi = 0.95, e=0.90;
  while(nb<max)
  {
  	
  	copiage(M, copie, n, m);
  	p =run_qualite_action_laby(Cosimienne, copie, n, m, e, xi);
    printf("Nb:%d, il reste:%d iterations  %d\n", nb, max-nb, p);
    xi-=dec;
    e-=dec;
    nb++;

  }
  copiage(M, copie, n, m);
  int f =0;
  int ir =0,action,etat;
  while(!f && ir <1000)
  {
    ir++;
    etat = h_laby(x,y,m);
    action= meilleur_action_laby(Cosimienne, etat);
    f = mouvement(copie, n, m, &x, &y, action);
    affiche_labyrinthe(copie, n, m);
    SDL_Delay(100);
  }
  
  printf("reussi en %d actions\n", ir);
   
  enregistrerMatriceFichier(Cosimienne, n * m, 4, save);
  LibererMatrice(Cosimienne, n*m);
  LibererLaby(M, n);
  LibererLaby(copie, n);
  // end_sdl(1, "rrr", window, renderer);
  return 0;
}