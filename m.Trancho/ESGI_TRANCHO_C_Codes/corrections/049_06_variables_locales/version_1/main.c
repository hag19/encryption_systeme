/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 49.
 */

#include <stdio.h>
#include <stdlib.h>

/* Une erreur de compilation survenait pour redéfinition de la */
/* variable "res". Ceci arrivait dans le scope du switch car   */
/* par scope chaque variable doit pouvoir s'identifier par son */
/* nom. Dans le cas de scopes imbriqués, une varaible de même  */
/* nom peut être déclarée et masque celle du scope parent.     */

int main() {
  int first, second;
  char res;
  printf(">>> ");
  scanf("%d %c %d", &first, &res, &second);
  switch(res) {
    case '+' : {
      /* int res vit dans le scope relatif au case '+' et      */
      /* masque char res                                       */
      int res = first + second;
      printf(" = %d\n", res);
    } break;
      
    case '*' : {
      /* long res vit dans le scope relatif au case '*' et     */
      /* masque char res                                       */
      long res = (long)first * second;
      printf(" = %ld\n", res);
    } break;
      
    case '/' : {
      /* double res vit dans le scope relatif au case '/' et   */
      /* masque char res                                       */
      double res = (double)first / second;
      printf(" = %lg\n", res);
    } break;
  }
  exit(EXIT_SUCCESS);
}