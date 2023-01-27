#ifndef __MODELISATION_TEMPS_H__
#define __MODELISATION_TEMPS_H__
#define NBACTION 6
#define NBDEPLATS 3
#define NBDEMPLACEMENTS 3
#define NB_TACO_TOTAL 10
#define NB_BURRITOS_TOTAL 10
#define NB_NACHOS_TOTAL 10
#define NB_ITE 100

#define NACHOS 0
#define BURRITOS 1
#define TACO 2
#define NACHOSNACHOS 3
#define NACHOSBURRITOS 4
#define NACHOSNACHOSNACHOS 5

#define GAMMA 0.8




typedef struct{
    int x;
    int y;
}coordonnee;

typedef struct{
    int fin;
    int *tab;
}set_t;



//Gestion des structures
//Partie d'un monde

set_t initSet(int n);
void LibererSet(set_t *s);
int rechercheVal(set_t s, int val);
void inserer_set(set_t *s, int val);
void inserer_set_avec_doublon(set_t *s, int val);
int suppressiondansset(set_t *s, int plat);




double** init_matrice_cosimienne(int n, int m);
int h(int periode_journee, int num_perso0, int num_perso1, int num_perso2);
void dehachage(int etat);
int prix(int plat, int periode);
int profit_action_etat(int action, set_t *s, int periode);
void insertionfile(int col, set_t *file);

void afficherMatrice(double **M, int n, int m);
void LibererMatrice(double **M, int n);
int estfini(int * compteurs);

#endif