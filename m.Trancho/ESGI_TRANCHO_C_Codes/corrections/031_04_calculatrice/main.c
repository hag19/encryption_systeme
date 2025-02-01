/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 31.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  /* Nous obtenons le choix de l'utilisateur depuis un menu    */
  /* proposé :                                                 */
  int choix_menu;
  printf("1 - Calculer\n2 - Quitter\n---\nVotre choix : ");
  scanf("%d", &choix_menu);
  
  /* Selon ce choix, nous y répondons : */
  switch(choix_menu) {
    case 1 :
      break;
    default :
      printf("Le choix %d n'est pas proposé.\n", choix_menu);
      /* En cas de choix invalide, nous continuons vers le     */
      /* choix de s'arrêter :                                  */
    case 2 :
      /* Nous pouvons terminer le programme ici : */
      printf("Bien, au revoir.\n");
      exit(EXIT_SUCCESS);
  }
  /* Dans la suite de ce code, le choix était de calculer,     */
  /* sinon le programme s'est terminé : ceci nous permet de    */
  /* continuer dans une zone non indentée.                     */
  
  /* Nous récupérons opérandes et opérateur comme dans une     */
  /* calculatrice :                                            */
  int first, second;
  char op_symb;
  printf(">>> ");
  scanf("%d %c %d", &first, &op_symb, &second);
  
  /* Nous affichons les valeurs récupérées puis le résultat    */
  /* selon l'opérateur :                                       */
  printf("%d %c %d = ", first, op_symb, second);
  switch(op_symb) {
  
    case '+' :
      printf("%ld\n", (long)first + second);
      break;
      
    case '-' :
      printf("%ld\n", (long)first - second);
      break;
      
    case '*' :
      printf("%ld\n", (long)first * second);
      break;
      
    case '/' :
      if(second == 0) {
        printf("inf\n");
        break;
      }
      printf("%lg (~ %d)\n", (double)first / second, first / second);
      break;
      
    case '%' :
      if(second == 0) {
        printf("NaN\n");
        break;
      }
      printf("%d\n", first % second);
      break;
      
    default :
      printf("?\n");
  }
  exit(EXIT_SUCCESS);
}