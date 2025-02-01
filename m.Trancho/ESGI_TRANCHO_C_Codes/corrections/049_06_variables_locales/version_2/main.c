/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 49.
 */

#include <stdio.h>
#include <stdlib.h>

/* Le code relatif aux cases du switch est copiés dans des     */
/* fonctions. Ces opérations sont maintenant locales aux       */
/* fonction indépendamment des nommages dans la fonction       */
/* principale. Ces traitements nécessitent cependant de        */
/* l'information de main : valeurs des deux opérandes          */
/* (l'opération appartient à la logique du code de main).      */
/* int first et int second des fonctions sont les paramèters   */
/* des fonctions. Ces variables permettent de copier les       */
/* valeurs passées en argument à l'appel. Puis, elles peuvent  */
/* ensuite être utilisées comme variables locales aux          */
/* fonctions. */

void afficher_addition(int first, int second) {
  int res = first + second;
  printf(" = %d\n", res);
}

void afficher_multiplication(int first, int second) {
  long res = (long)first * second;
  printf(" = %ld\n", res);
}

void afficher_division(int first, int second) {
  double res = (double)first / second;
  printf(" = %lg\n", res);
}

int main() {
  int first, second;
  char res;
  printf(">>> ");
  scanf("%d %c %d", &first, &res, &second);
  switch(res) {
    case '+' :
      afficher_addition(first, second);
    break;
      
    case '*' :
      afficher_multiplication(first, second);
    break;
      
    case '/' :
      afficher_division(first, second);
    break;
  }
  exit(EXIT_SUCCESS);
}