#include <stdio.h>
#include "apprentissage.h"
#include "apparition.h"






void afficherInstance(instance_t instance)
{
    for (int i = 0; i < 3; i++)
    {
        printf("c:%d,p:%d ", instance.client[i], instance.repas[i]);
    }
    printf("\n");
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

// Action de meilleur qualité
int meilleur_action(double **Cosimienne, int etat)
{

    // L'ensemble contient toutes les valeurs/plats/codes possibles

    // On prend ensuite parmis ces plats/codes celui de qualité maximal
    int indice_meilleure_action = rand() % 6;
    double max = Cosimienne[etat][indice_meilleure_action];

    for (int i = 0; i < 6; i++)
    {
        if (max < Cosimienne[etat][i])
        {
            max = Cosimienne[etat][i];
            indice_meilleure_action = i;
        }
    }


    return indice_meilleure_action;
}

// Enregistrement de la matrice apprise
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

// Réaliser un 'run', c'est à dire une suite d'actions menant si possible à un état terminal,
// Ici on on s'arrete si le jeu est terminé ou alors si n=NB_ITE
int run_qualite_action(double **Cosimienne, instance_t *parcourir, double PROBA_X, double eps,  int stocktotal)
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
    int etat; // On passe forcement une fois dans la boucle

    // La suite d'action est determinée par la proba
    // La récompense dépend de la vente effectué [pour le moment on onsidere la case du tableau]
    // Q représente la matrice etat/action

    // On commence par générer une suite d'état/action/récompense
    set_t s = initSet(NBDEPLATS); // ensemble des possibles
    int plat1,
        plat2,
        plat3,
        periode = 0;
    while (parcourir)
    {
        // Il est possible d'effectuer une action, on determine laquelle

        // Determination de l'état dans lequel on se trouve
        periode = ecoulementDesStocks(parcourir->stock_restant, stocktotal);
        plat1 = parcourir->repas[0];// Determination de plat demandé par les clients
        plat2 = parcourir->repas[1];
        plat3 = parcourir->repas[2];

        etat = h(periode, plat1, plat2, plat3); // Ligne correspondant à notre état

        


        // Insertions des différentes possibilités
        inserer_set_avec_doublon(&s, plat1);
        inserer_set_avec_doublon(&s, plat2);
        inserer_set_avec_doublon(&s, plat3);
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
            action = meilleur_action(Cosimienne, etat);
        }

        // On calcul la récompense en fonction de notre action
        gain = profit_action_etat(action, &s, periode);

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

    eps = (100 - PROBA_X) / 100.0;
    suite_etat[ite + 1] = 63; // Etat final forcement plus aucun de client

    // Q( s(n-1), a(n-1) ) += epsilon * (rn - Q( s(n-1),a(n-1) ))
    Cosimienne[suite_etat[ite]][suite_action[ite]] += eps * (suite_recompense[ite + 1] - Cosimienne[suite_etat[ite]][suite_action[ite]]); // la derniere recompense vaut forcement 0 ici

    // pour i = n-2 à 0 par pas de -1
    double Max;
    for (int i = ite - 2; i >= 0; i--)
    {
        // Définir M le maximum des Q(s(i+1), a) pour toute action a possible
        etat = suite_etat[i + 1];
        plat1 = etat / 16,
        plat2 = (etat % 16) / 4,
        plat3 = etat % 4;

        action = meilleur_action(Cosimienne, etat);
        Max = Cosimienne[etat][action];

        // Q(si, ai) += epsilon * (r(i+1) + gamma * M - Q(si,ai) )
        Cosimienne[suite_etat[i]][suite_action[i]] += eps * (suite_recompense[i + 1] + GAMMA * Max - Cosimienne[suite_etat[i]][suite_action[i]]);

        // On vide fictivement notre ensemble
        s.fin = -1;
    }

    LibererSet(&s);
    return recompense; // Parcourir est l'état du jeu dans lequel on est à la fin
}


void insertionfile(int col, set_t * file)
{
  switch (col)
        {
        case NACHOS:
            inserer_set_avec_doublon(file, 0);

            break;

        case BURRITOS:
            inserer_set_avec_doublon(file, 1);
            break;

        case TACO:
            inserer_set_avec_doublon(file, 2);
            break;

        case NACHOSNACHOS:
            inserer_set_avec_doublon(file, 0);
            inserer_set_avec_doublon(file, 0);
            break;

        case NACHOSBURRITOS:
            inserer_set_avec_doublon(file, 0);
            inserer_set_avec_doublon(file, 1);
            break;

        case NACHOSNACHOSNACHOS:
            inserer_set_avec_doublon(file, 0);
            inserer_set_avec_doublon(file, 0);
            inserer_set_avec_doublon(file, 0);

            break;

        default:
            break;
        }
}


int ecoulementDesStocks(int sommestocks, int stocktotal)
{
    int tiers = stocktotal/3;
    int n = 3 - sommestocks/tiers;
    n = (n==3) ? 2:n;

    return n;

}

