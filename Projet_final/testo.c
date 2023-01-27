#include <stdio.h>
#include <time.h>
#include "modelisation_temps.h"
#include "apprentissage.h"
#include <stdlib.h>

 
void verif_valeur_Cosimienne(double **M)
{
    set_t s = initSet(6);
    int c0, c1, c2;
    for(int jour=0; jour<3; jour++){
    for (c0 = 0; c0 <= NBDEPLATS; c0++)
    {
        for (c1 = 0; c1 <= NBDEPLATS; c1++)
        {
            for (c2 = 0; c2 <= NBDEPLATS; c2++)
            {

                printf("%d%d%d%d==", jour, c0, c1, c2);
                // dehachage(h(jour, c0, c1, c2));

                // printf(" | %d  \tligne:%d\n", meilleur_action(M, h(jour, c0, c1, c2)), h(jour, c0, c1, c2) );
                for(int i=0; i<6; i++)
                {
                    printf("| %lf", M[h(jour, c0, c1, c2)][i]);
                }
                
                printf("\n");                
            }
        }
    }
    }
}

int main()
{
   srand( time(NULL) );

    // test matrice

    // float M[64][3];
    // init_matrice(M);
    // afficherMatrice(M);

    // test de la fonction de hachage

    // int i,j,k;
    // for(i=0; i<4; i++)
    // {
    //     for(j=0; j<4; j++)
    //     {
    //         for(k=0; k<4; k++)
    //         {
    //             printf("c0,c1,c2:%d%d%d => h:%d\n", i,j,k, h(i,j,k));
    //         }
    //     }
    // }

    // Test generation d'une instance
    // instance_t *monde = generer_instance();

    // if(!monde)
    // {
    //     printf("Monde est à NULL\n");
    // }
    // else
    // {
    //     //Test d'un run
    //     run_qualite_action(M, monde);
    // }

    // //test validité du pointeur après exec
    // if(monde)
    // {
    //     printf("Monde toujours valide\n");
    // }
    // else
    // {
    //     printf("Monde est à NULL\n");
    // }

    // //test d'une serie de run
    // int i,somme_profit = 0;
    // for(i=0; i<10; i++) somme_profit += run_qualite_action(M, monde);

    // //Verification des changements sur la matrice
    // afficherMatrice(M);

    // test de convergence vers une solution optimale
    //  instance_t *monde;
    //  int i, profit_avant = 1, profit_apres = 0;
    //  int nb_monde = 10000;
    //  while(nb_monde)
    //  {
    //      nb_monde--;
    //      monde = generer_instance();

    //     profit_avant = 1;
    //     profit_apres = 0;
    //     printf("Je débute l'apprentiessage d'un nouveau monde\n");

    //     while(profit_apres-profit_avant)
    //     {
    //         profit_avant = profit_apres;
    //         profit_apres = 0;
    //         for(i=0; i<100; i++)profit_apres += run_qualite_action(M, monde);
    //     }
    //     LibererInstance(monde);
    //     enregistrerMatriceFichier(M, "Matrice2.txt");
    //     printf("Il reste: %d\n", nb_monde);

    // }
    // // printf("profit avant %d, profit apres%d\n", profit_avant, profit_apres);
    // enregistrerMatriceFichier(M, "Matrice2.txt");

    //Verification generation d'un jeu entier
    // instance_t *parcourir =  generer_instance2();
    // while(parcourir)
    // {
    //     afficherInstance(*parcourir);
    //     parcourir = parcourir->suiv;
    // }
    // afficherMatrice(M);
    // init_matrice(M);
    // afficherMatrice(M);

    // Verification du choix des meilleures actoins

    // int plat1, plat2, plat3, action;
    // init_matrice(M);
    // set_t s = initSet(4);
    // int etat;
    // for (int c0 = 0; c0 < 4; c0++)
    // {
    //     for (int c1 = 0; c1 < 4; c1++)
    //     {
    //         for (int c2 = 0; c2 < 4; c2++)
    //         {
    //             etat = h(c0, c1, c2);
    //             plat1 = etat / 16,
    //             plat2 = (etat % 16) / 4,
    //             plat3 = etat % 4;
    //             inserer_set(&s, plat1);
    //             inserer_set(&s, plat2);
    //             inserer_set(&s, plat3);

    //             // printf("ensemble:");
    //             // for(int pp=0; pp<s.fin;)

    //             action = meilleur_action(M, etat, s);
    //             printf("%d:%d:%d   meilleure: %d\n", c0, c1, c2, action);
    //             s.fin = -1;
    //         }
    //     }
    // }




    // ON PASSE AU TEST DE LA COSIMIENNE

    // float **Cosimienne = init_matrice_cosimienne();

    // instance_t *monde;
    // int recompense, nb_ite = 1000, profit_avant, profit_apres;
    // float X = 60;


    // while (nb_ite)
    // {

    //     monde = generer_instance();
    //     profit_avant = 1;
    //     profit_apres = 0;

    //     printf("Je débute l'apprentiessage d'un nouveau monde\n");

    //     while (profit_apres - profit_avant)
    //     {
    //         profit_avant = profit_apres;
    //         profit_apres = 0;
    //         for (int i = 0; i < 100; i++)
    //             profit_apres += run_qualite_action_2(Cosimienne, monde, X);
    //     }
    //     nb_ite--;
    //     printf("Il reste: %d\n", nb_ite);
    //     LibererInstance(monde);
    // }

    // afficherMatrice(Cosimienne, 64, 6);

    // verif_valeur_Cosimienne();


    // //TEST VERIFICATION SUPPRESSION SET
    // set_t s = initSet(3);
    // inserer_set2(&s, 0);
    // inserer_set2(&s, 0);
    // inserer_set2(&s, 1);

    // printf("depart:%d%d%d fin %d\n", s.tab[0], s.tab[1], s.tab[2], s.fin);


    // printf("Suppression 0:\n");
    // suppressiondansset(&s, 0);
    // printf("%d%d fin%d\n", s.tab[0], s.tab[1], s.tab[2],  s.fin);

    // printf("Suppression 0:\n");
    // suppressiondansset(&s, 0);
    // printf("%d\n", s.tab[0]);
    
    // printf("Suppression 0:\n");
    // suppressiondansset(&s, 0);
    // printf("%d\n", s.tab[0]);


    
    
    
    
    
    
    //Test d'un run 2

    // double **Cosimienne = init_matrice_cosimienne(192, 6);

    // instance_t *monde;
    // int recompense, nb_ite = 1000, profit_avant, profit_apres;
    // float X = 95,
    //       dec =  (95-10)/50000;



    // while (nb_ite)
    // {
    //     X-= dec;
    //     monde = generer_instance();
    //     profit_avant = 1;
    //     profit_apres = 0;

    //     printf("Je débute l'apprentiessage d'un nouveau monde\n");

    //     while (profit_apres - profit_avant)
    //     {
    //         profit_avant = profit_apres;
    //         profit_apres = 0;
    //         for (int i = 0; i < 100; i++)
    //             profit_apres += run_qualite_action(Cosimienne, monde, X, 1-(X/100.0));
    //     }
    //     nb_ite--;
    //     printf("Il reste: %d\n", nb_ite);
    //     LibererInstance(monde);
    // }

    // afficherMatrice(Cosimienne, 192, 6);
    // enregistrerMatriceFichier(Cosimienne, 192, 6, "testdumidi.txt");




    // //test fuite mémoire
    // instance_t *monde = generer_instance();
    // double **Cosimienne = init_matrice_cosimienne(192, 6);
    // run_qualite_action(Cosimienne, monde, 90, 1);
    // LibererMatrice(Cosimienne, 192);
    // LibererInstance(monde);

    //TEST INSERTION FILE
    // set_t file = initSet(3);
    
    // insertionfile(col, &file);



    //Verification matrice entrainee

    double **M = init_matrice_cosimienne(192, 6);
    chargerMatrice(M, 192, 6, "esclavagisme.txt");

    // verif_valeur_Cosimienne(M);

    //  afficherMatrice(M, 1, 6);
    verif_valeur_Cosimienne(M);
    return 0;
}