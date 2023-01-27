#ifndef __MODELISATION_H__
#define __MODELISATION_H__
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

#define GAMMA 0.999999999



typedef struct{
    int x;
    int y;
}coordonnee;

typedef struct instance{
    int client[3];//on sauvegarde les positions/présences des clients
    int repas[3];//on sauvegarde le type de client/repas associé
    int stock_restant;
    struct instance *suiv;

}instance_t;

typedef struct{
    int fin;
    int *tab;
}set_t;

//Fonctios utilitaires
set_t initSet(int n);
void LibererSet(set_t *s);
int rechercheVal(set_t s, int val);
void inserer_set(set_t *s, int val);
void inserer_set2(set_t *s, int val);
int suppressiondansset(set_t *s, int plat);




int estfini(int * compteurs);

//Fonction de hachage pour récupérer le numéro de ligne de l'état i+1
int h(int num_perso0, int num_perso1, int num_perso2);
void dehachage(int etat);
void afficherMatrice(float **M, int n, int m);
void init_matrice(float M2[64][3]);
instance_t* generer_instance();
void LibererInstance(instance_t *debut);
int run_qualite_action(float M[64][3], instance_t *debut);
void enregistrerMatriceFichier(float M[64][3], char *filename);
void chargerMatrice(float M[64][3], char *filename);
void afficherInstance(instance_t instance);
int meilleur_action(float M[64][3], int etat, set_t s);
int profit_action_etat(int action, set_t *s);
int meilleur_action_2(float **Cosimienne, int etat);
int run_qualite_action_2(float **Cosimienne, instance_t *parcourir, float PROBA_X);
float** init_matrice_cosimienne();

instance_t * generer_instance2();

void insertionfile(int col, set_t *file);
int ecoulementDesStocks(int sommestocks);

#endif