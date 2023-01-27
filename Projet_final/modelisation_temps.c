#include <stdio.h>
#include "modelisation_temps.h"
#include <stdlib.h>
#include <time.h>
#include "apparition.h"



int estfini(int *compteurs)
{
    for (int i = 0; i < NBDEPLATS; i++)
    {
        if (compteurs[i])
            return 0;
    }
    return 1;
}

// Fonction de hachage pour récupérer le numéro de ligne de l'état i+1 en fonction des clients/repas demandes
int h(int periode_journee, int num_perso0, int num_perso1, int num_perso2)
{
    // Codage des différents elements:
    // Nachos : 0
    // Burritos: 1
    // Tacos: 2
    // Null : 3
    //periode journée : matin = 0, midi = 1, soir = 2 Indexé selon le bit le plus à gauche

    if (num_perso0 == -1)
        num_perso0 = 3;
    if (num_perso1 == -1)
        num_perso1 = 3;
    if (num_perso2 == -1)
        num_perso2 = 3;

    int i;

    //On place la période de la journée
    i = periode_journee * 64;
    // On place déjà le premier client:
    i += num_perso0 * 16;

    // On place le 2nd client
    i += num_perso1 * 4;

    /// On place enfin le 3eme client
    i += num_perso2;

    return i;
}


//affichage d'un etat etat
void dehachage(int etat)
{
    printf("%d %d %d %d", etat/64, (etat%64)/16, ((etat%64) % 16) / 4, etat % 4);
}


//Création de la mtrice d'état/action
//n doit valoir 192 et m 6 dans notre situation actuelle
double** init_matrice_cosimienne(int n, int m)
{
    
    double **Cosimienne = (double**)malloc(sizeof(double*) * n);
    
    
    int i;
    for (i = 0; i < n; i++)
    {
        Cosimienne[i] = (double*)calloc(m, sizeof(double));
    }


    return Cosimienne;
}



void LibererMatrice(double **M, int n)
{
    for(int i=0; i<n; i++)free(M[i]);
    free(M);
}

//Affichage formaté d'une matrice (etat/action)
void afficherMatrice(double **M, int n, int m)
{
    printf("ETAT  | N  | B | T | NN | NB | NNN\n ");
    
    
    for (int i = 0; i < n; i++)
    {
        printf("\netat:");
        dehachage(i);
        for (int j = 0; j < m; j++)
        {
            printf("| %f ", M[i][j]);
        }
    }
}


//Prix d'un plat en fonction de la période (matin/midi/soir ou lore de Clara)
int prix(int plat, int periode)
{
    int price;
    switch (plat)
    {
        case 0:
            price = 2;
            break;

        case 1:
            price = (periode == 1) ? 5 : 3;
            break;

        case 2:
            price = (periode==2) ? 7:5;
            break;

        default:
            price = 0;
            break;
    }

    return price;
}

int profit_action_etat(int action, set_t *s, int periode)
{

    set_t demande = initSet(4);

    // action: N B T NN NB NNN
    switch (action)
    {
        case NACHOS:
            inserer_set_avec_doublon(&demande, 0);
            break;

        case BURRITOS:
            inserer_set_avec_doublon(&demande, 1);
            break;

        case TACO:
            inserer_set_avec_doublon(&demande, 2);
            break;

        case NACHOSNACHOS:
            inserer_set_avec_doublon(&demande, 0);
            inserer_set_avec_doublon(&demande, 0);
            break;

        case NACHOSBURRITOS:
            inserer_set_avec_doublon(&demande, 0);
            inserer_set_avec_doublon(&demande, 1);
            break;

        case NACHOSNACHOSNACHOS:
            inserer_set_avec_doublon(&demande, 0);
            inserer_set_avec_doublon(&demande, 0);
            inserer_set_avec_doublon(&demande, 0);
            break;

        default:
            break;
    }

    // On essaie de vendre tout ce qu'on a produit
    int gain = 0;
    int vendu, plat;

    while (demande.fin >= 0)
    {
        // Ce que l'on veut vendre:
        plat = demande.tab[demande.fin];
        demande.fin--;

        // On regarde si quelqu'un veut acheter
        vendu = suppressiondansset(s, plat);
        if (vendu)
        {
            gain += prix(plat, periode);
        }
        else
        {
            gain -= prix(plat, periode);
        }
    }
    LibererSet(&demande);

    return gain; // Selon le BODE cela peut être negatif
}


set_t initSet(int n)
{
    set_t s;
    s.fin = -1;
    s.tab = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        s.tab[i] = -1;

    return s;
}

void LibererSet(set_t *s)
{
    free(s->tab);
    s->tab = NULL;
}

// Rechercher une valeur dans un set; renvoie l'indice (vérifier après si présence)
int rechercheVal(set_t s, int val)
{
    // ICI pas de dichotomie on a un tableau très petit !
    int debut = 0;
    int fin = s.fin;
    while ((debut <= fin) && (s.tab[debut] != val))
    {
        debut++;
    }

    return debut;
}

void inserer_set(set_t *s, int val)
{
    if (val != 3)
    {
        // Ajoute également l'element dans l'ensemble si besoin (si 1)
        int pos = rechercheVal(*s, val); // Indice ou la valeur se situe (si elle existe)
        if (pos > s->fin)
        {
            // La valeur n'existe pas, il faut donc l'insérer
            s->tab[pos] = val;
            s->fin++;
        }
    }
}

void inserer_set_avec_doublon(set_t *s, int val)
{

    s->fin++;
    s->tab[s->fin] = val;
}

// Supprime un element de notre ensemble. Renvoie 1 si supprimé 0 sinon
int suppressiondansset(set_t *s, int plat)
{
    // on cherche l'element à supprimer
    int indicetableau = 0;
    int supprimer = 0;

    // Recherche de la valeur
    while ((indicetableau <= s->fin) && (s->tab[indicetableau] != plat))
    {
        indicetableau++;
    }

    if (indicetableau <= s->fin)
    {
        // La valeur est présente

        // on decale à gauche
        for (int i = indicetableau; i < s->fin; i++)
        {
            s->tab[i] = s->tab[i + 1];
        }

        // on decale le pointeur de fin
        s->fin--;
        supprimer = 1;
    }
    return supprimer;
}
