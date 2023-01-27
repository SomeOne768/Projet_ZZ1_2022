#ifndef __APPRENTISSAGE_H__
#define __APPRENTISSAGE_H__
#include "modelisation_temps.h"

typedef struct instance{
    int client[3];//on sauvegarde les positions/présences des clients
    int repas[3];//on sauvegarde le type de client/repas associé
    int stock_restant;
    struct instance *suiv;

}instance_t;







//Gestion de l'apprentissage
void afficherInstance(instance_t instance);
instance_t* generer_instance();
void LibererInstance(instance_t *debut);
int meilleur_action(double **Cosimienne, int etat);

//gestion des resultats
void enregistrerMatriceFichier(double **M, int n, int m, char *filename);
void chargerMatrice(double **M, int n, int m, char *filename);
int run_qualite_action(double **Cosimienne, instance_t *parcourir, double PROBA_X, double eps,  int stocktotal);

void insertionfile(int col, set_t *file);
int ecoulementDesStocks(int sommestocks,  int stocktotal);


#endif
