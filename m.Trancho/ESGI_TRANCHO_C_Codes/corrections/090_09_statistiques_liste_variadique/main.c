/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 90.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  /* Déclaration de mini et maxi : variables permettant de     */
  /* connaître les valeurs maximales et minimales du tour de   */
  /* boucle précédent.                                         */
  int mini = 0, maxi = 0;
  /* Nous tiendrons à jour le nombre d'entiers positifs lus    */
  /* (pour calcul de moyenne).                                 */
  int nombre = 0;
  /* La moyenne non pondérée étant donnée comme la somme des   */
  /* éléments divisée par leur nombre, nous tiendrons à jour   */
  /* la somme des entiers positifs rencontrés.                 */
  double somme = 0;
  /* Nous récupérerons l'élément courant fourni par            */
  /* l'utilisateur.                                            */
  int current;
  /* Première saisie : */
  printf("Entrez des entiers positifs : ");
  scanf("%d", &current);
  /* Cette saisie avant la boucle permet de s'assurer d'avoir  */
  /* une valeur valide : un entier positif. Si ce n'est pas le */
  /* cas, nous n'entrons pas dans la boucle.                   */
  while(current >= 0) {
    /* Phase de traitrement de l'entier courant fourni (assuré */
    /* positif par la condition de la boucle.                  */
    if(nombre == 0) {
      /* Dans le cas du premier tour de boucle (aucun élément  */
      /* comptabilisé précédemment, nous initialisons mini et  */
      /* maxi avec la valeur de current.                       */
      mini = current;
      maxi = current;
    } else if(current < mini) {
      /* Sinon si ce n'est pas le premier tour, dans le cas où */
      /* l'élément est plus petit que la plus petite valeur    */
      /* rencontrée, nous mettons à jour le minimum            */
      mini = current;
    } else if(current > maxi) {
      /* Nous procédons similairement pour le maximum que fait */
      /* pour le minimum                                       */
      maxi = current;
    }
    /* Nous tenons à jour la somme des éléments en ajoutant    */
    /* l'élément courant.                                      */
    somme += current;
    /* Nous comptabilisons un élément de plus. */
    ++nombre;
    /* Nous lisons à nouveau un entier, s'il est positif ceci  */
    /* relance la boucle et le traitement, sinon ceci arrête   */
    /* la boucle et évite comptabilisation d'un entier         */
    /* négatif.                                                */
    scanf("%d", &current);
  }
  /* Dans le cas où  nous n'effectuons pas une division par    */
  /* zéro.                                                     */
  if(nombre) {
    /* La somme devient la moyenne */
    somme /= nombre;
  }
  printf("min : %d\n", mini);
  printf("max : %d\n", maxi);
  printf("moyenne : %g\n", somme);
  exit(EXIT_SUCCESS);
}