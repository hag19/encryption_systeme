/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 9.
 */

/* Code Alice : import studio                                  */
/* Potentielle idée d'importation des fonctionnalités          */
/* standards :                                                 */
/* - stdio : standard inputs and outputs | entrées / sorties   */
/* - stdlib : standard library                                 */
#include <stdio.h>
#include <stdlib.h>

/* main est le point d'entrée d'un programme en langage C      */
/* (première fonction lancée).                                 */
/* On l'écrit "int main ()" car c'est en réalité une fonction  */
/* qui renvoie un entier (code d'erreur) et ici ne prend pas   */
/* d'arguments. */
int main() {
  /* Code Alice : pi <- 3,14                                   */
  float pi;
  /* Pour utiliser une variable en langage C, il faut la       */
  /* déclarer.                                                 */
  pi = 3.14;
  /* en langage C, la notation numérique est à l'anglaise, on  */
  /* utilise un '.'                                            */
  /* Code Alice : print(pi)                                    */
  /* Code Alice : Pourquoi ça n'affiche pas pi ???             */
  printf("%f\n", pi);
  /* pi ne s'affiche pas car print n'est pas une fonction      */
  /* connue en C.                                              */
  /* La fonction à utiliser est printf.                        */
  /* printf requière une chaîne avec indication de formats     */
  /* commençant par % pour associer à chaque % une des valeurs */
  /* listées après la chaîne (dans le même ordre). */
  printf("%.1f\n", pi);
  /* Pour choisir un nombre de décimales / chiffres après la   */
  /* virgule, il faut ajouter ce nombre précédé d'un '.' dans  */
  /* le format après le % .                                    */
  printf("%g\n", pi);
  /* %g propose automatiquement un affichage convenable pour   */
  /* un oeil humain.                                           */
  printf("%e\n", pi);
  /* %e affiche sous notation scientifique.                    */
  exit(EXIT_SUCCESS);
  /* exit prend un argument qui correspond à un code d'erreur :*/
  /* EXIT_SUCCESS indique que le programme s'est terminé en    */
  /* fonctionnant tel qu'il attendait de l'être.               */
  /* Note : dans le cas particulier de la fonction main :      */
  /* return 0 aurait pu être utilisé.                          */
}