/*******************************************************************************/
/* Gestion des règles. L'utilisateur entre ses règles dans la ligne de commande*/
/* Gestion de la possibilité de charger/enregistrer un jeu                     */
/*******************************************************************************/

#ifndef __regle_h__
#define __regle_h__


/*******************************************************************************/
/* extraire_regle: recupère une chaine saisie et deux chaine B et S en entrée  */
/* la saisie doit correspondre au format suivant : B12/S38 : nait si 1 ou 2    */
/* voisins et survit si 3 ou 8 voisins (pas un intervalle)                     */
/* Le tableau B est retourné est sous la forme B [0, 1, 2, 0, 0, .., 0] pour   */
/* notre exemple et le tableau S [0, 0, 0, 3, 0, 0, 0, 0, 1, 0]                */
/*******************************************************************************/
int extraire_regle(char *saisie, char *B, char *S);



#endif