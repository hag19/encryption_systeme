/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 19.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  long big = 0;
  int ajout;
  printf("big vaut %ld, faîtes le grossir : ", big);
  scanf("%d", &ajout);
  /* Le +++ est une mauvaise pratique même si le langage       */
  /* l'accepte. Dans le cas présent, ceci revient aux          */
  /* écritures suivantes :                                     */
  /* big = ajout+++big;                                        */
  /* big = ajout++ + big;                                      */
  /* big = ajout + big;                                        */
  /* big = big + ajout;                                        */
  /* big += ajout;                                             */
  big += ajout;
  printf("big vaut %ld !\n", big);
  exit(EXIT_SUCCESS);
}