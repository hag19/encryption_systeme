/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 17.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  int a, b;
  /* demander des valeurs pour a et b                          */
  /* printf affiche à l'utilisateur un message significatif    */
  /* pour lui indiquer qu'il devra entrer deux valeurs         */
  /* entières.                                                 */
  printf("Entrez deux entiers : ");
  /* La lecture des deux entiers se fait au clavier par scanf  */
  /* scanf affecte les variables a et b à l'aide de leur       */
  /* adresse (donnée par la précédence par &)                  */
  scanf("%d %d", &a, &b);
  /* afficher l'addition de a et b                             */
  /* l'addition des valeurs connues pour a et b se fait par    */
  /* l'opération + ce qui est effectué ici est le remplacement */
  /* de a et b par leur valeur puis l'opération arithmétique   */
  /* d'addition des deux valeurs qui donne un résultat de même */
  /* type (int).                                               */
  printf("%d + %d = %d\n", a, b, a + b);
  /* échanger les valeurs de a et de b                         */
  /* une affectation écrase la valeur, nous proposons ici      */
  /* l'utilisation d'une variable temporaire :                 */
  int tmp; /* | tmp |  a  |  b  |                              */
  tmp = a; /* |  a  |  a  |  b  |                              */
  a = b;   /* |  a  |  b  |  b  |                              */
  b = tmp; /* |  a  |  b  |  a  |                              */
  /* afficher la soustraction de a et b                        */
  printf("%d - %d = %d\n", a, b, a - b);
  long c;
  /* affecter à c le résultat de la multiplication de a et b   */
  /* notons que nous souhaitons ranger le résultat de la       */
  /* multiplication de a (int : 4 octets) et b (int : 4        */
  /* octets) dans c (long : 8 octets).                         */
  /* Or, a * b renvoie un résultat (int : 4 octets) dont nous  */
  /* perdrions une partie. Une solution peut être de           */
  /* transformer une opérande en (long : 8 octets).            */
  /* L'évalution de a * b se fait alors sur 8 octets avant     */
  /* d'être affectée.                                          */
  c = (long)a * b;
  printf("%d * %d = %ld\n", a, b, c);
  float d;
  /* affecter à d le résultat de la division fractionnaire de  */
  /* a et b */
  /* a et b sont des entier, la division sera donc la division */
  /* entière. Pour obtenir une division fractionnaire, une     */
  /* proposition est la transformation d'une opérande en       */
  /* flottant. */
  d = (float)a / b;
  printf("%d / %d = %g\n", a, b, d);
  exit(EXIT_SUCCESS);
}