/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 11.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  /* Pour corriger le code de Charlie,                         */
  /* il suffit de choisir le long double si disponible :       */
  /* dans le cas de Windows, on peut gagner en précision avec  */
  /* le double.                                                */
  /* Code Charlie : float racine = 1.414213562373095048;       */
  long double racine = 1.414213562373095048l;
  /* Code Charlie : printf("racine de 2 vaut %g\n", racine);   */
  printf("racine de 2 vaut %Lg\n", racine);
  /* Code Charlie : printf("variable : %.18f\n", racine);      */
  printf("variable : %.18Lf\n", racine);
  printf("texte    : 1.414213562373095048\n");
  /* Code Charlie : C'est différent, étrange ...               */
  /* Code Charlie : float clavier;                             */
  long double clavier;
  printf("Recopiez :\n>1.414213562373095048\n>");
  /* Code Charlie : scanf("%f", &clavier);                     */
  scanf("%Lf", &clavier);
  /* Code Charlie : printf("copie : %.18f\n", clavier);        */
  printf("copie : %.18Lf\n", clavier);
  printf("texte : 1.414213562373095048\n");
  /* Code Charlie : C'est la machine qui bug !                 */
  exit(EXIT_SUCCESS);
}