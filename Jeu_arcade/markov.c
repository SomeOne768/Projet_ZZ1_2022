#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "markov.h"


        

int prochainEtatMarkov(const int M[9][9], int actuel) //mettre matrice du monde correspondant
{
   srand(time(NULL));
   
    int aleatoire=rand()%101;
    int col = 0;
    int sommecumulee=M[actuel][col];
    // printf("somme %d:%d\n", col,sommecumulee);

    while(sommecumulee<aleatoire)
    {
        col++;
        sommecumulee=sommecumulee+M[actuel][col];
        // printf("somme %d:%d\n", col,sommecumulee);

    }
    
    return col;

}

