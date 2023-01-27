#include <stdio.h>
#include "modelisation.h"
#include <time.h>
#include <stdlib.h>
#include "apparition.h"

/* Différentes étapes
Initialiser les qualités, les paramètres d'apprentissage,
Générer une instance du monde,
Réaliser un 'run', c'est à dire une suite d'actions menant si possible à un état terminal,
A partir des résultats du 'run', modifier les qualités par rétro-propagation,
Modifier si nécessaires les paramètres d'apprentissage,
Retour en 1 jusqu'à (condition à choisir de façon adéquate).
*/

// MARIO KART WII POUR ANTONIO
// FUTUR POUR BABETHE

// 1: Initialiser les qualités, les paramètres d'apprentissage,

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
int h(int num_perso0, int num_perso1, int num_perso2)
{
    // Codage des différents elements:
    // Nachos : 0
    // Burritos: 1
    // Tacos: 2
    // Null : 3

    if (num_perso0 == -1)
        num_perso0 = 3;
    if (num_perso1 == -1)
        num_perso1 = 3;
    if (num_perso2 == -1)
        num_perso2 = 3;

    int i;

    // On place déjà le premier client:
    i = num_perso0 * 16;

    // On place le 2nd client
    i += num_perso1 * 4;

    /// On place enfin le 3eme client
    i += num_perso2;

    return i;
}

void dehachage(int etat)
{
    printf("%d %d %d\n", etat % 16, (etat % 16) / 4, etat % 4);
}

// Création de la matrice
void init_matrice(float M[64][3])
{
    // Codage des différents elements:
    // Ligne:
    // Nachos : 0
    // Burritos: 1
    // Tacos: 2
    // Null : 3*

    // Colonne : choix action : servir T ou B ou N

    int i, j;
    // Au depart tout est pondéré de la même manière
    for (i = 0; i < 64; i++)
    {
        for (j = 0; j < 3; j++)
        {
            M[i][j] = 1;
        }
    }

    // On enleve les cas non possible (servir tacos alors que personne n'en veut)
    for (j = 0; j < 3; j++)
    {
        // j = aliment que personne ne veut

        int plat1, plat2, plat3;
        for (plat1 = 0; plat1 <= NBDEPLATS; plat1++)
        {
            if (plat1 != j)
            {
                // le client 1 ne souhaite pas le plat j

                for (plat2 = 0; plat2 <= NBDEPLATS; plat2++)
                {
                    if (plat2 != j)
                    {
                        // le client 2 ne souhaite pas le plat j
                        for (plat3 = 0; plat3 <= NBDEPLATS; plat3++)
                        {
                            if (plat3 != j)
                            {
                                // le client 3 ne souhaite pas le plat j
                                //=>ici personne ne souhaite le plat j
                                i = 16 * plat1 + 4 * plat2 + plat3;
                                M[i][j] = 0;
                            }
                        }
                    }
                }
            }
        }
    }
}

void init_matrice_cosimatrice(float M[64][3])
{
    int i, j, valeur;

    for (i = 0; i < 64; i++)
    {
        for (j = 0; j < 3; j++)
        {
            valeur = 0;
            switch (j)
            {
            case NACHOS:
                valeur = 2;
                break;

            case BURRITOS:
                valeur = 3;
                break;

            case TACO :
                valeur = 5;
                break;

            default:
                break;
            }
            M[i][j] = valeur;
        }
    }

    for (j = 0; j < 3; j++)
    {
        // j = aliment que personne ne veut

        int plat1, plat2, plat3;
        for (plat1 = 0; plat1 <= NBDEPLATS; plat1++)
        {
            if (plat1 != j)
            {
                // le client 1 ne souhaite pas le plat j

                for (plat2 = 0; plat2 <= NBDEPLATS; plat2++)
                {
                    if (plat2 != j)
                    {
                        // le client 2 ne souhaite pas le plat j
                        for (plat3 = 0; plat3 <= NBDEPLATS; plat3++)
                        {
                            if (plat3 != j)
                            {
                                // le client 3 ne souhaite pas le plat j
                                //=>ici personne ne souhaite le plat j
                                i = 16 * plat1 + 4 * plat2 + plat3;
                                M[i][j] = 0;
                            }
                        }
                    }
                }
            }
        }
    }
}

float** init_matrice_cosimienne()
{
    float **Cosimienne = malloc(sizeof(float*) * 64);
    
    
    int i;
    for (i = 0; i < 64; i++)
    {
        Cosimienne[i] = malloc(sizeof(float) * 6);
    }


    set_t s = initSet(6);
    int c0, c1, c2;
    for (c0 = 0; c0 <= NBDEPLATS; c0++)
    {
        for (c1 = 0; c1 <= NBDEPLATS; c1++)
        {
            for (c2 = 0; c2 <= NBDEPLATS; c2++)
            {

                for (i = 0; i < 6; i++)
                {
                    s.fin = -1;
                    inserer_set2(&s, c0);
                    inserer_set2(&s, c1);
                    inserer_set2(&s, c2);
                    Cosimienne[h(c0,c1,c2)][i] =  profit_action_etat(i, &s);
                }               
            }
        }
    }

    return Cosimienne;
}

void afficherMatrice(float **M, int n, int m)
{
    printf("ETAT  | N  | B | T | NN | NB | NNN\n ");
    for (int i = 0; i < n; i++)
    {
        printf("\n");
        printf("etat:%d:%d:%d ", i / 16, (i % 16) / 4, i % 4);
        for (int j = 0; j < m; j++)
        {
            printf("| %f ", M[i][j]);
        }
    }
}

void afficherInstance(instance_t instance)
{
    for (int i = 0; i < 3; i++)
    {
        printf("c:%d,p:%d ", instance.client[i], instance.repas[i]);
    }
    printf(" stocks restant %d\n", instance.stock_restant);
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

void inserer_set2(set_t *s, int val)
{

    s->fin++;
    s->tab[s->fin] = val;

}

// Générer une instance du monde
// On genere une suite de client
// Modéliser par un tableau de perso avec des valeurs € [|0; 3|]
instance_t *generer_instance()
{
    // le jeu s'arrête lorsqu'on a généré le nombre de client pour chaque plats
    instance_t *liste = NULL,
               **prec = NULL;
    // On suppose que l'on aura au moins un instance sinon notre jeu ne sert à rien
    //  liste = (instance_t*)malloc(sizeof(instance_t));
    prec = &liste;

    int compteurs[3] = {NB_NACHOS_TOTAL, NB_BURRITOS_TOTAL, NB_TACO_TOTAL};

    // chaque client existant peut être de 3 types différents

    while (!(estfini(compteurs)))
    {
        // il reste des clients à faire pop
        // on alloue de la mémoire
        (*prec) = (instance_t *)malloc(sizeof(instance_t));

        for (int j = 0; j < NBDEMPLACEMENTS; j++)
        {
            (*prec)->client[j] = 0;
            (*prec)->repas[j] = -1;
        }

        // on attribue des valeurs
        nouveauxclients((*prec)->client);
        quellecommandesurquelemplacement((*prec)->client, (*prec)->repas, compteurs);

        // A Adapter plus tard
        for (int i = 0; i < NBDEMPLACEMENTS; i++)
        {
            // correspond à NULL => code 3
            if ((*prec)->repas[i] == -1)
                (*prec)->repas[i] = 3;
        }

        // on passe a la suite et on continue tant qu'il y a du stock
        prec = &((*prec)->suiv);
    }

    (*prec) = NULL;
    // Dès qu'on est sortie, on a une instance d'une partie entière générée aléatoirement

    return liste;
}


instance_t *generer_instance2()
{
    // le jeu s'arrête lorsqu'on a généré le nombre de client pour chaque plats
    instance_t *liste = NULL,
               **prec = NULL;
    // On suppose que l'on aura au moins un instance sinon notre jeu ne sert à rien
    //  liste = (instance_t*)malloc(sizeof(instance_t));
    prec = &liste;

    int compteurs[3] = {NB_NACHOS_TOTAL, NB_BURRITOS_TOTAL, NB_TACO_TOTAL};

    // chaque client existant peut être de 3 types différents

    while (!(estfini(compteurs)))
    {
        // il reste des clients à faire pop
        // on alloue de la mémoire
        (*prec) = (instance_t *)malloc(sizeof(instance_t));

        for (int j = 0; j < NBDEMPLACEMENTS; j++)
        {
            (*prec)->client[j] = 0;
            (*prec)->repas[j] = -1;
        }

        // on attribue des valeurs
        nouveauxclients((*prec)->client);
        quellecommandesurquelemplacement((*prec)->client, (*prec)->repas, compteurs);
        (*prec)->stock_restant=compteurs[0]+compteurs[1]+compteurs[2];
        

        // A Adapter plus tard
        for (int i = 0; i < NBDEMPLACEMENTS; i++)
        {
            // correspond à NULL => code 3
            if ((*prec)->repas[i] == -1)
                (*prec)->repas[i] = 3;
        }

        // on passe a la suite et on continue tant qu'il y a du stock
        prec = &((*prec)->suiv);
    }

    (*prec) = NULL;
    // Dès qu'on est sortie, on a une instance d'une partie entière générée aléatoirement

    return liste;
}

void LibererInstance(instance_t *debut)
{
    instance_t *parcourir, *prec;
    parcourir = debut;
    while (parcourir)
    {
        prec = parcourir;
        parcourir = parcourir->suiv;
        free(prec);
    }
    debut = NULL;
}

int meilleur_action(float M[64][3], int etat, set_t s)
{

    // L'ensemble contient toutes les valeurs/plats/codes possibles

    // On prend ensuite parmis ces plats/codes celui de qualité maximal
    int indice_meilleure_action = rand() % (s.fin + 1);
    float max = M[etat][indice_meilleure_action];

    for (int i = 0; i < s.fin; i++)
    {
        if (max < M[etat][s.tab[i]])
        {
            max = M[etat][s.tab[i]];
            indice_meilleure_action = s.tab[i];
        }
    }
    /*
    // Pour nous la meilleure est action est celle de plus grand indice actuellement
    // int max = -1;
    // for (int i = 0; i <= s.fin; i++)
    // {
    //     if (max < s.tab[i])
    //         max = s.tab[i];
    // }
    return max;
    */

    return indice_meilleure_action;
}

int meilleur_action_2(float **Cosimienne, int etat)
{

    // L'ensemble contient toutes les valeurs/plats/codes possibles

    // On prend ensuite parmis ces plats/codes celui de qualité maximal
    int indice_meilleure_action = rand() % 6;
    float max = Cosimienne[etat][indice_meilleure_action];

    for (int i = 0; i < 6; i++)
    {
        if (max < Cosimienne[etat][i])
        {
            max = Cosimienne[etat][i];
            indice_meilleure_action = i;
        }
    }
    /*
    // Pour nous la meilleure est action est celle de plus grand indice actuellement
    // int max = -1;
    // for (int i = 0; i <= s.fin; i++)
    // {
    //     if (max < s.tab[i])
    //         max = s.tab[i];
    // }
    return max;
    */

    return indice_meilleure_action;
}

int prix(int plat)
{
    int price;
    switch (plat)
    {
    case 0:
        price = 2;
        break;

    case 1:
        price = 3;
        break;

    case 2:
        price = 5;
        break;

    default:
        price = 0;
        break;
    }

    return price;
}

void enregistrerMatriceFichier(float M[64][3], char *filename)
{
    FILE *f = fopen(filename, "w+");
    if (f)
    {
        for (int i = 0; i < 64; i++)
        {

            for (int j = 0; j < 3; j++)
            {
                fprintf(f, "%f ", M[i][j]);
            }
            fprintf(f, "\n");
        }

        fclose(f);
    }
}

void chargerMatrice(float M[64][3], char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f)
    {
        int i = 0, j = 0;
        float val;
        while (feof(f))
        {
            fscanf(f, "%f", &val);
            if (i < 64)
            {
               M[i][j] = val;
                j++;
                if (j == 3)
                {
                    j = 0;
                    i++;
                }
            }
        }
        fclose(f);
    }
}

int suppressiondansset(set_t *s, int plat)
{
    // on cherche l'element à supprimer
    int indicetableau = 0;
    int supprimer = 0;

    //Recherche de la valeur
    while ( (indicetableau <= s->fin) && (s->tab[indicetableau] != plat) )
    {
        indicetableau++;
    }

    if (indicetableau <= s->fin)
    {
        //La valeur est présente

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

int profit_action_etat(int action, set_t *s)
{

    set_t demande = initSet(4);

    // action: N B T NN NB NNN
    switch (action)
    {
        case NACHOS:
            inserer_set2(&demande, 0);
            break;

        case BURRITOS:
            inserer_set2(&demande, 1);
            break;

        case TACO:
            inserer_set2(&demande, 2);
            break;

        case NACHOSNACHOS:
            inserer_set2(&demande, 0);
            inserer_set2(&demande, 0);
            break;

        case NACHOSBURRITOS:
            inserer_set2(&demande, 0);
            inserer_set2(&demande, 1);
            break;

        case NACHOSNACHOSNACHOS:
            inserer_set2(&demande, 0);
            inserer_set2(&demande, 0);
            inserer_set2(&demande, 0);
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
            gain += prix(plat);
        }
        else
        {
            gain -= prix(plat);
        }
    }
    LibererSet(&demande);

    return gain; // Selon le BODE cela peut être negatif
}

// Réaliser un 'run', c'est à dire une suite d'actions menant si possible à un état terminal,
// Ici on on s'arrete si le jeu est terminé ou alors si n=NB_ITE
int run_qualite_action_2(float **Cosimienne, instance_t *parcourir, float PROBA_X)
{
    // Fonction qui retourne l'état du jeu après un run (NULL si fini)
    int ite = 0;
    int suite_etat[NB_BURRITOS_TOTAL + NB_NACHOS_TOTAL + NB_TACO_TOTAL + 1], // dans le pire des cas les clients POP 1 ar 1 + etat vide final
        suite_action[NB_BURRITOS_TOTAL + NB_NACHOS_TOTAL + NB_TACO_TOTAL + 1],
        suite_recompense[NB_BURRITOS_TOTAL + NB_NACHOS_TOTAL + NB_TACO_TOTAL + 1];
    suite_recompense[0] = 0; // la premiere récompense est forcément nulle
    int proba;               // choix de l'action à effectuer
    int action;
    int recompense = 0; // Recompense du run
    int gain;

    // Connaitre l'état par rapport à une itération:
    int etat = 0, ancien_etat; // On passe forcement une fois dans la boucle

    // La suite d'action est determinée par la proba
    // La récompense dépend de la vente effectué [pour le moment on onsidere la case du tableau]
    // Q représente la matrice etat/action

    // On commence par générer une suite d'état/action/récompense
    set_t s = initSet(NBDEPLATS); // ensemble des possibles
    int plat1,
        plat2,
        plat3;
    while (parcourir)
    {
        // Il est possible d'effectuer une action, on determine laquelle

        // Determination de l'état dans lequel on se trouve
        etat = h(parcourir->repas[0], parcourir->repas[1], parcourir->repas[2]); // Ligne correspondant à notre état

        // Determination de plat demandé par les clients
        plat1 = etat / 16,
        plat2 = (etat % 16) / 4,
        plat3 = etat % 4;

        // Insertions des différentes possibilités
        inserer_set2(&s, plat1);
        inserer_set2(&s, plat2);
        inserer_set2(&s, plat3);
        // L'ensemble contient toutes demandes

        proba = rand() % 101;
        // On determine l'action à réaliser
        if (proba < PROBA_X)
        {
            // On choisit une action aléatoirement
            action = rand() % 6;
        }
        else
        {
            // On choisit la meilleur action à faire
            // On considere que c'est celle qui donne le benefice maximum OU ALORS EN FONCTION QUALITE ???
            action = meilleur_action_2(Cosimienne, etat);
        }

        // On calcul la récompense en fonction de notre action
        gain = profit_action_etat(action, &s);
        recompense += gain; // l'action correspondant à "vendre tel plat"
        suite_etat[ite] = etat;
        suite_action[ite] = action;
        suite_recompense[ite + 1] = gain;

        parcourir = parcourir->suiv;
        ite++;

        // On vide fictivement notre ensemble
        s.fin = -1;
    }
    ite--;
    float eps = (100-PROBA_X)/100.0;
    suite_etat[ite + 1] = 63; // Etat final forcement plus aucun de client

    // Q( s(n-1), a(n-1) ) += epsilon * (rn - Q( s(n-1),a(n-1) ))
    Cosimienne[suite_etat[ite]][suite_action[ite]] += eps * (suite_recompense[ite + 1] - Cosimienne[suite_etat[ite]][suite_action[ite]]); // la derniere recompense vaut forcement 0 ici

    // pour i = n-2 à 0 par pas de -1
    float Max;
    for (int i = ite - 2; i >= 0; i--)
    {
        // Définir M le maximum des Q(s(i+1), a) pour toute action a possible
        etat = suite_etat[i + 1];
        plat1 = etat / 16,
        plat2 = (etat % 16) / 4,
        plat3 = etat % 4;

        action = meilleur_action_2(Cosimienne, etat);
        Max = Cosimienne[etat][action];

        // Q(si, ai) += epsilon * (r(i+1) + gamma * M - Q(si,ai) )
        Cosimienne[suite_etat[i]][suite_action[i]] += eps * (suite_recompense[i + 1] + GAMMA * Max - Cosimienne[suite_etat[i]][suite_action[i]]);

        // On vide fictivement notre ensemble
        s.fin = -1;
    }

    return recompense; // Parcourir est l'état du jeu dans lequel on est à la fin
}

/*
// Réaliser un 'run', c'est à dire une suite d'actions menant si possible à un état terminal,
// Ici on on s'arrete si le jeu est terminé ou alors si n=NB_ITE
int run_qualite_action(float M[64][3], instance_t *parcourir)
{
    // Fonction qui retourne l'état du jeu après un run (NULL si fini)
    int ite = 0;
    int suite_etat[NB_BURRITOS_TOTAL + NB_NACHOS_TOTAL + NB_TACO_TOTAL + 1], // dans le pire des cas les clients POP 1 ar 1 + etat vide final
        suite_action[NB_BURRITOS_TOTAL + NB_NACHOS_TOTAL + NB_TACO_TOTAL + 1],
        suite_recompense[NB_BURRITOS_TOTAL + NB_NACHOS_TOTAL + NB_TACO_TOTAL + 1];
    suite_recompense[0] = 0; // la premiere récompense est forcément nulle
    int proba;               // choix de l'action à effectuer
    int action;
    int recompense = 0; // Recompense du run

    // Connaitre l'état par rapport à une itération:
    int etat = 0, ancien_etat; // On passe forcement une fois dans la boucle

    // La suite d'action est determinée par la proba
    // La récompense dépend de la vente effectué [pour le moment on onsidere la case du tableau]
    // Q représente la matrice etat/action

    // On commence par générer une suite d'état/action/récompense
    set_t s = initSet(NBDEPLATS); // ensemble des possibles
    int plat1,
        plat2,
        plat3;
    while (parcourir)
    {
        // Il est possible d'effectuer une action, on determine laquelle

        // Determination de l'état dans lequel on se trouve
        etat = h(parcourir->repas[0], parcourir->repas[1], parcourir->repas[2]); // Ligne correspondant à notre état

        // Determination de plat demandé par les clients
        plat1 = etat / 16,
        plat2 = (etat % 16) / 4,
        plat3 = etat % 4;

        // Insertions des différentes possibilités
        inserer_set(&s, plat1);
        inserer_set(&s, plat2);
        inserer_set(&s, plat3);

        // L'ensemble contient toutes les valeurs/plats/codes possibles

        proba = rand() % 101;
        if (proba < PROBA_X)
        {
            // On choisit une action aléatoirement
            action = s.tab[rand() % (s.fin + 1)];
        }
        else
        {
            // On choisit la meilleur action à faire
            action = meilleur_action(M, etat, s);
        }

        // On calcul la récompense en fonction de notre action
        recompense += prix(action); // l'action correspondant à "vendre tel plat"
        suite_etat[ite] = etat;
        suite_action[ite] = action;
        suite_recompense[ite + 1] = prix(action);
        parcourir = parcourir->suiv;
        ite++;

        // On vide fictivement notre ensemble
        s.fin = -1;
    }
    ite--;

    suite_etat[ite + 1] = 63; // Etat final forcement plus aucun de client

    // Q( s(n-1), a(n-1) ) += epsilon * (rn - Q( s(n-1),a(n-1) ))
    M[suite_etat[ite]][suite_action[ite]] += EPS * (suite_recompense[ite + 1] - M[suite_etat[ite]][suite_action[ite]]); // la derniere recompense vaut forcement 0 ici

    // pour i = n-2 à 0 par pas de -1
    float Max;
    for (int i = ite - 2; i >= 0; i--)
    {
        // Définir M le maximum des Q(s(i+1), a) pour toute action a possible
        etat = suite_etat[i + 1];
        plat1 = etat / 16,
        plat2 = (etat % 16) / 4,
        plat3 = etat % 4;

        // Insertions des différentes possibilités
        inserer_set(&s, plat1);
        inserer_set(&s, plat2);
        inserer_set(&s, plat3);
        action = meilleur_action(M, etat, s);

        // On recherche max ligne n

        int indice_max = rand() % NBDEPLATS;
        Max = M[etat][indice_max];
        for (int action_possible = 0; action_possible < NBDEPLATS; action_possible++)
        {
            if (Max < M[etat][action_possible])
            {
                indice_max = action_possible;
                Max = M[etat][indice_max];
            }
        }

        // Q(si, ai) += epsilon * (r(i+1) + gamma * M - Q(si,ai) )
        M[suite_etat[i]][suite_action[i]] += EPS * (suite_recompense[i + 1] + GAMMA * Max - M[suite_etat[i]][suite_action[i]]);

        // On vide fictivement notre ensemble
        s.fin = -1;
    }

    return recompense; // Parcourir est l'état du jeu dans lequel on est à la fin
}

*/

void insertionfile(int col, set_t * file)
{
  switch (col)
        {
        case NACHOS:
            inserer_set2(file, 0);

            break;

        case BURRITOS:
            inserer_set2(file, 1);
            break;

        case TACO:
            inserer_set2(file, 2);
            break;

        case NACHOSNACHOS:
            inserer_set2(file, 0);
            inserer_set2(file, 0);
            break;

        case NACHOSBURRITOS:
            inserer_set2(file, 0);
            inserer_set2(file, 1);
            break;

        case NACHOSNACHOSNACHOS:
            inserer_set2(file, 0);
            inserer_set2(file, 0);
            inserer_set2(file, 0);

            break;

        default:
            break;
        }
}


int ecoulementDesStocks(int sommestocks)
{
    int stocktotal=NB_BURRITOS_TOTAL+NB_NACHOS_TOTAL+NB_TACO_TOTAL;
    return(sommestocks/(stocktotal/3));


}

