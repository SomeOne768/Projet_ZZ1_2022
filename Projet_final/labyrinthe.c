#include <stdio.h>
#include "labyrinthe.h"
#include <stdlib.h>
#include <time.h>

char **init_matrice_labyrinthe(char *filename, int *nbligne, int *nbcol)
{

	char **M = NULL;

	int n = 0, m = 0;

	FILE *f = fopen(filename, "r");
	// On commence par compter nos lignes et nos colonne
	char rejet[128], c;
	int col = 0;
	while (!feof(f))
	{
		if (!col)
		{
			c = fgetc(f);
			if (c == '\n')
			{
				col = !col;
				n++;
			}
			else
			{
				m++;
			}
			printf("%c", c);
		}
		else
		{
			fgets(rejet, 128, f);
			n++;
			printf("%s", rejet);
		}
	}

	printf("Il y a %d ligne et %d colonne\n", n, m);

	fseek(f, 0, SEEK_SET);
	M = (char **)malloc(sizeof(char *) * n);
	for (int i = 0; i < n; i++)
	{
		M[i] = (char *)malloc(sizeof(char) * m);
		for (int j = 0; j < m; j++)
		{
			M[i][j] = fgetc(f);
		}
		fgetc(f); // retour ligne
	}

	*nbligne = n;
	*nbcol = m;

	return M;
}

void position(char **M, int n, int m, int *x, int *y)
{
	// On recherche le 1 qui donne la position du joueur dans le labyrinthe
	int i = 0, j = 0;
	// forcement présent
	while (i < n && M[i][j] != '1')
	{
		j++;
		if (j == m)
		{
			i++;
			j = 0;
		}
	}

	*x = i;
	*y = j;
}

void affiche_labyrinthe(char **M, int n, int m)
{

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			printf("%c", M[i][j]);

		printf("\n");
	}
}

void copiage(char **M1, char **M2, int n, int m)
{
	//On copie M1 dans M2
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			M2[i][j] = M1[i][j];
		}
	}
}

int mouvement_gauche(char **M, int n, int m, int *x, int *y)
{
	// printf("\n\nJE vais à gauche\n");
	// return 1 si gagné 0 sinon
	int possible = 0;
	if ((*y) != 0)
	{
		if (M[*x][(*y) - 1] != '#')
		{
			// On peut aller a cet endroit et on determine si c'est win
			if (M[*x][(*y) - 1] == '2')
				possible = 1;
			M[*x][*y] = '-';
			M[*x][(*y) - 1] = '1';
			(*y)--;
		}
	}
	return possible;
}

int mouvement_droite(char **M, int n, int m, int *x, int *y)
{
	// printf("\n\nJE vais à droite\n");
	// return 1 si mouvement possible 0 sinon
	int possible = 0;
	if ((*y) != (m - 1))
	{
		if (M[*x][(*y) + 1] != '#')
		{
			if (M[*x][(*y) + 1] == '2')
				possible = 1;
			// On peut aller sur une route
			M[*x][*y] = '-';
			M[*x][(*y) + 1] = '1';
			(*y)++;
		}
	}
	return possible;
}

int mouvement_haut(char **M, int n, int m, int *x, int *y)
{
	// printf("\n\nJE vais à haut\n");
	// return 1 si mouvement possible 0 sinon
	int possible = 0;
	if ((*x) != 0)
	{

		if (M[(*x) - 1][*y] != '#')
		{

			if (M[(*x) - 1][*y] == '2')
				possible = 1;
			// On peut aller sur une route
			M[*x][*y] = '-';
			M[(*x) - 1][(*y)] = '1';
			(*x)--;
		}
	}
	return possible;
}

int mouvement_bas(char **M, int n, int m, int *x, int *y)
{
	// printf("\n\nJE vais à bas\n");
	// return 1 si mouvement possible 0 sinon
	int possible = 0;
	if ((*x) != n - 1)
	{
		if (M[(*x) + 1][*y] != '#')
		{
			if (M[(*x) + 1][*y] == '2')
				possible = 1;
			// On peut aller sur une route
			M[*x][*y] = '-';
			M[(*x) + 1][(*y)] = '1';
			(*x)++;
		}
	}
	return possible;
}

int mouvement(char **M, int n, int m, int *x, int *y, int action)
{
	// Retourne 1 si fini
	int gagne;

	switch (action)
	{
	case HAUT:
		gagne = mouvement_haut(M, n, m, x, y);
		break;

	case BAS:
		gagne = mouvement_bas(M, n, m, x, y);
		break;

	case GAUCHE:
		gagne = mouvement_gauche(M, n, m, x, y);
		break;

	case DROITE:
		gagne = mouvement_droite(M, n, m, x, y);
		break;

	default:
		printf("Mouvement invalide.\n");
		break;
	}

	return gagne;
}

// Action de meilleur qualité
int meilleur_action_laby(double **Cosimienne, int etat)
{

	// L'ensemble contient toutes les valeurs/plats/codes possibles

	// On prend ensuite parmis ces plats/codes celui de qualité maximal
	int indice_meilleure_action = rand() % 4;
	double max = Cosimienne[etat][indice_meilleure_action];

	for (int i = 0; i < 4; i++)
	{
		if (max < Cosimienne[etat][i])
		{
			max = Cosimienne[etat][i];
			indice_meilleure_action = i;
		}
	}

	return indice_meilleure_action;
}

// Perception: position
// action :  haut bas gauche droite de 0 a 3

int run_qualite_action_laby(double **Cosimienne, char **M, int n, int m, double proba_x, double eps)
{
	// Fonction qui retourne l'état du jeu après un run (NULL si fini)
	int ite = 0;
	int suite_etat[NBITE + 1], // dans le pire des cas les clients POP 1 ar 1 + etat vide final
		suite_action[NBITE + 1],
		suite_recompense[NBITE + 1];

	// Connaitre l'état par rapport à une itération:
	int etat, action, gain; // On passe forcement une fois dans la boucle
	// On commence par générer une suite d'état/action/récompense
	int fini = 0;
	int x, y;
	position(M, n, m, &x, &y);
	int proba, recompense;
	while (ite < NBITE && !fini)
	{
		// Il est possible d'effectuer une action, on determine laquelle

		// Determination de l'état dans lequel on se trouve
		etat = h_laby(x, y, m);

		proba = rand() % 101;
		// On determine l'action à réaliser
		if (proba < proba_x)
		{
			// On choisit une action aléatoirement
			action = rand() % 4;
		}
		else
		{
			// On choisit la meilleur action à faire
			// On considere que c'est celle qui donne le benefice maximum OU ALORS EN FONCTION QUALITE ???
			action = meilleur_action_laby(Cosimienne, etat);
		}

		// On calcul la récompense en fonction de notre action
		fini = mouvement(M, n, m, &x, &y, action);
		gain = (fini == 1) ? 100 : -1;

		recompense += gain; // l'action correspondant à "vendre tel plat"
		suite_etat[ite] = etat;
		suite_action[ite] = action;
		suite_recompense[ite + 1] = gain;

		// printf("ite:%d\n", ite);
		// affiche_labyrinthe(M, n, m);
		ite++;
	}
	ite--;

	// Q( s(n-1), a(n-1) ) += epsilon * (rn - Q( s(n-1),a(n-1) ))
	Cosimienne[suite_etat[ite]][suite_action[ite]] += eps * (suite_recompense[ite + 1] - Cosimienne[suite_etat[ite]][suite_action[ite]]); // la derniere recompense vaut forcement 0 ici

	// pour i = n-2 à 0 par pas de -1
	double Max;
	for (int i = ite - 2; i >= 0; i--)
	{
		// Définir M le maximum des Q(s(i+1), a) pour toute action a possible
		etat = suite_etat[i + 1];

		action = meilleur_action_laby(Cosimienne, etat);
		Max = Cosimienne[etat][action];

		// Q(si, ai) += epsilon * (r(i+1) + gamma * M - Q(si,ai) )
		Cosimienne[suite_etat[i]][suite_action[i]] += eps * (suite_recompense[i + 1] + GAMMA * Max - Cosimienne[suite_etat[i]][suite_action[i]]);
	}

	return ite; // Parcourir est l'état du jeu dans lequel on est à la fin
}

int h_laby(int x, int y, int m)
{
	return (x * m) + y;
}

void LibererLaby(char **M, int n)
{
	for (int i = 0; i < n; i++)
		free(M[i]);
	free(M);
}