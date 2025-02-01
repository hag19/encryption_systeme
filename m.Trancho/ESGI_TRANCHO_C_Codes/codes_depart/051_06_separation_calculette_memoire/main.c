#include <stdio.h>
#include <stdlib.h>

int main() {
  int first, second;
  int variable = 0;
  char op;
  int choix;
  int resultat;
  do {
    printf("1 - Calculer\n2 - Modifier variable\n3 - Voir variable\n0 - Quitter\n---\nVotre choix : ");
    scanf("%d", &choix);
    switch(choix) {
      case 1 :
        printf(">>> ");
        scanf("%d %c %d", &first, &op, &second);
        switch(op) {
          case '+' : resultat = first + second; break;
          case '-' : resultat = first - second; break;
          case '*' : resultat = first * second; break;
          case '/' : resultat = first / second; break;
          case '%' : resultat = first % second; break;
        }
        printf(">>> %d %c %d = %d\n", first, op, second, resultat);
        break;
      case 2 :
        printf(">>> variable = %d ", variable);
        scanf(" %c %d", &op, &second);
        switch(op) {
          case '+' : variable += second; break;
          case '-' : variable -= second; break;
          case '*' : variable *= second; break;
          case '/' : variable /= second; break;
          case '%' : variable %= second; break;
          case '=' : variable = second; break;
        }
        printf(">>> variable = %d\n", variable);
        break;
      case 3 :
        printf(">>> variable = %d\n", variable);
        break;
      default : break;
    }
  } while(choix != 0);
  printf("Au revoir.\n");
  exit(EXIT_SUCCESS);
}