/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 41.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  int first, second;
  int a, b;
  int tmp;
  int q, r;
  
  /* Nous demandons deux entiers à l'utilisateur */
  printf("Entrez deux entiers : ");
  scanf("%d %d", &first, &second);
  /* Nous copions ces valeurs dans des variables de travail : */
  a = first;
  b = second;
  
  /* Si la première est plus petite, nous les échangeons : */
  if(a < b) {
    tmp = a;
    a = b;
    b = tmp;
  }
  
  /* Tant que le second est différent de 0 */
  /* (le second sera le reste précédent) */
  while(b != 0) {
    /* Nous calculons quotient et reste par la division        */
    /* euclidienne :                                           */
    q = a / b;
    r = a % b;
    /* Nous les affichons : */
    printf("%d = %d * %d + %d\n", a, b, q, r);
    /* Nous préparons l'étape suivante : */
    a = b;
    b = r;
  }
  
  /* Le résultat est le dernier reste non nul : sauvegardé     */
  /* dans a                                                    */
  printf("pgcd(%d, %d) = %d\n", first, second, a);
  
  exit(EXIT_SUCCESS);
}