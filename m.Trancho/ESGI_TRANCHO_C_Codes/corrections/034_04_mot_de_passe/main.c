/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 34.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  int first_pass = 0, second_pass = 0;
  
  /* Pour tester le code, il est possible d'ajouter la lecture */
  /* des valeurs à l'exécution :                               */
  printf("Entrez les deux codes secrets : ");
  scanf("%d %d", &first_pass, &second_pass);
  
  /* Les combinaisons possibles sont : */
  /* first_pass | second_pass */
  /* -----------+------------ */
  /*         42 | 1337        */
  /*       1337 | 42          */
  /*       1235 | 1235        */
  
  /* Dans le cas de (1337, 42), first_pass > second_pass */
  if(first_pass > second_pass) {
    int tmp = first_pass;
    first_pass = second_pass;
    second_pass = tmp;
  }
  /* Après l'échange, les combinaisons sont réduites à */
  /* first_pass | second_pass */
  /* -----------+------------ */
  /*         42 | 1337        */
  /*       1235 | 1235        */
  
  /* La condition de l'accès refusé n'est pas logiquement      */
  /* triviale. Une proposition est de considérer :             */
  /* acces_refuse = ! acces_autorise                           */
  /* Pour acces_autorise, ceci est vrai si une des             */
  /* combinaisons est donnée :                                 */
  /* acces_autorise = (combinaison 42, 1337) ||                */
  /* (combinaison 1235, 1235) */
  /* La vérification d'une combinaison demande que les deux    */
  /* mots de passe soient vérifiés :                           */
  /* (combinaison a, b) = (first_pass == a &&                  */
  /* second_pass == b) */
  /* À partir de cette construction, il est possible de        */
  /* construire la condition d'accès refusé comme étant la     */
  /* suivante : */
  if( !((first_pass == 42 && second_pass == 1337)
    || (first_pass == 1235 && second_pass == 1235))) {
    
    printf("Accès refusé.\n");
    exit(EXIT_SUCCESS);
  }
  
  printf("Bienvenue !\n");
  exit(EXIT_SUCCESS);
}