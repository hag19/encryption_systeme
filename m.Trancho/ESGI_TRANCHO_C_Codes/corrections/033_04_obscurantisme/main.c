/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 33.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  int a, b;
  
  printf("Entrez deux nombres : ");
  scanf("%d %d", &a, &b);
  
  /* ! (a - b) vaut une valeur de vérité :                     */
  /* * ! (a - b) est vrai si (a - b) est faux                  */
  /*   le faux est 0, donc (a - b) == 0                        */
  /*   d'où a == b                                             */
  /* * ! (a - b) est faux si (a - b) est vrai                  */
  /*   le vrai est toute valeur différente de 0                */
  /*   donc, il suffit que a - b != 0, alors                   */
  /*   a != b                                                  */
  /* ! (a - b) est donc vrai si a == b et faux si a != b,      */
  /* alors ! (a - b) est équivalent à a == b                   */
  if(a == b) {
    printf("%d et %d sont égaux\n", a, b);
    
  } else {
    /* nous proposons l'ajout d'une variable qui offre plus de */
    /* sémantique sur le résultat obtenu.                      */
    /* Notons que si (a - b) est négatif, alors (a - b) ne     */
    /* peut pas être  représenté par la même valeur en signé   */
    /* et non signé (bit de signe comme bit de poids fort)     */
    /* (unsigned int)(a - b) donne donc une valeur différent   */
    /* de (a - b).                                             */
    /* (unsigned int)(a - b) ne tient pas sur la plage signée  */
    /* des int (4 octets) mais peut se représenter sur la      */
    /* plage signée des long (8 octets).                       */
    /* Par conséquent si (a - b) est positif, sa valeur reste  */
    /* inchangée par la transformation                         */
    /* (long)(unsigned int)(a - b), mais deviendra un résultat */
    /* positif si (a - b) est négatif.                         */
    /* ((long)(unsigned int)(a - b) == a - b) est donc vraie   */
    /* si a - b >= 0 d'où a >= b et fausse si a - b < 0 .      */
    /* dans le cas vrai, l'expression ternaire vaut b et dans  */
    /* le cas vrai vaut a.                                     */
    /* une possibilité est donc de proposer la vérification de */
    /* (a < b) pour donner a si vrai et b si faux.             */
    /* Ceci offre plus de lisibilité et pour ajouter du sens à */
    /* cette expression, c'est en réalité le calcul du minimum */
    /* des deux valeurs. */
    int minimum = (a < b) ? a : b;
    printf("Entre %d et %d, le plus petit est %d\n", a, b, minimum);
    
  }
  exit(EXIT_SUCCESS);
}