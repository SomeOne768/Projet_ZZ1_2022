#include <stdlib.h>
#include <stdio.h>
#include "apparition.h"
#include "affichageSDL.h"
#include "modelisation_temps.h"

// void deplacementChariot(int x, int y, )
// {
//     if (emplacementClient==0)
//     {}
//     else
//     {
//         if (emplacementClient==1)
//         {

//         }
//         else
//         {

//         }
//     }
// } A REMPLIR ET UTILISER PLUS TARD SI VERSION SIMPLE FONCTIONNE

void nouveauxclients(int *presenceclient)
{
    for (int i = 0; i < 3; i++)
    {
        presenceclient[i] = 0;
    }
    while (presenceclient[0] == 0 && presenceclient[1] == 0 && presenceclient[2] == 0)
    {
        // On ajoute des rand sinon trop de proximite
        presenceclient[0] = rand() % 2;
        rand() % 7;
        presenceclient[1] = rand() % 2;
        rand() % 13;
        presenceclient[2] = rand() % 2;
        rand() % 17;
    }

    // printf("client0 %d , client1 %d,client2 %d \n", presenceclient[0], presenceclient[1],presenceclient[2]);
}

int quellecommandesurcetemplacement(int *compteurs)
{
    int qui = -1;

    if (!(estfini(compteurs)))
    {
        qui = rand() % NBDEPLATS;

        while ((compteurs[qui]) < 1)
        {
            qui = rand() % NBDEPLATS;
        }
    }
    return qui;
}

void quellecommandesurquelemplacement(int *presence, int *quisuremplacement, int *compteurs)
{
    for (int k = 0; k < NBDEMPLACEMENTS; k++)
    {
        if (presence[k])
        {
            quisuremplacement[k] = quellecommandesurcetemplacement(compteurs);
            if (quisuremplacement[k] == -1)
            {
                presence[k] = 0;
            }
            else
            {
                compteurs[quisuremplacement[k]]--;
            }
        }
    }
}

void service(int quiestservi, int *profitvente, int *tempspreparation, int *compteursvente, int *tempsattente, int perdiode) // quiestservi= quisuremplacement[i]  int *compteurN, int *compteurT, int *compteurB,
{
    switch (quiestservi)
    {
    case 0:
        //(*compteurN)++;
        (*profitvente) += prix(0, perdiode);
        (*tempspreparation) = 8;
        // printf("Nachos \n");
        compteursvente[0]++;

        break;

    case 1:
        //(*compteurB)++;
        (*profitvente) += prix(1, perdiode);
        (*tempspreparation) = 24;
        // printf("Burritos \n");
        compteursvente[1]++;

        break;

    case 2:
        //(*compteurT)++;
        (*profitvente) += prix(2, perdiode);
        (*tempspreparation) = 30;
        // printf("Tacos \n");
        compteursvente[2]++;

        break;

    default:
        break;
    }
    (*tempsattente) -= (*tempspreparation);
}
