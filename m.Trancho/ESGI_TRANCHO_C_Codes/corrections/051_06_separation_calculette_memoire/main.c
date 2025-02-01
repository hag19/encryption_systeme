/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 51.
 */

#include <stdio.h>
#include <stdlib.h>

/* Effectue le calcul entre first et second pour un opérateur  */
/* donné par le caractère op                                   */
/* Renvoie le résultat du calcul (first si l'opérareur n'est   */
/* pas connu, second si '=')                                   */
int applyOp(int first, int second, char op);

/* Affiche le menu dans la console */
void printMenu();

/* Gère l'interaction du choix de l'option par l'utilisateur */
int choixMenu();

/* lance l'option calculer : renvoie le résultat */
int optionCalculer();

/* lance l'option modifier la variable : renvoie la nouvelle   */
/* valeur de la variable                                       */
int optionModifier(int variable);

/* lance l'option d'affichage de la variable */
void optionAfficher(int variable);

/* lance et gère la calculette */
void runCalculette();

int main() {
  runCalculette();
  printf("Au revoir.\n");
  exit(EXIT_SUCCESS);
}

int applyOp(int first, int second, char op) {
  switch(op) {
    case '+' : return first + second;
    case '-' : return first - second;
    case '*' : return first * second;
    case '/' : return first / second;
    case '%' : return first % second;
    case '=' : return second;
  }
  printf("Opérateur \'%c\' non connu.\n", op);
  return first;
}

void printMenu() {
  printf("1 - Calculer\n2 - Modifier variable\n3 - Voir variable\n0 - Quitter\n---\n");
}

int choixMenu() {
  int choix;
  printMenu();
  printf("Votre choix : ");
  scanf("%d", &choix);
  return choix;
}

int optionCalculer() {
  int resultat;
  int first, second;
  char op;
  printf(">>> ");
  scanf("%d %c %d", &first, &op, &second);
  resultat = applyOp(first, second, op);
  printf(">>> %d %c %d = %d\n", first, op, second, resultat);
  return resultat;
}

int optionModifier(int variable) {
  int second;
  char op;
  printf(">>> variable = %d ", variable);
  scanf(" %c %d", &op, &second);
  variable = applyOp(variable, second, op);
  printf(">>> variable = %d\n", variable);
  return variable;
}

void optionAfficher(int variable) {
  printf(">>> variable = %d\n", variable);
}

void runCalculette() {
  int variable = 0;
  int choix;
  while(choix = choixMenu()) {
    switch(choix) {
      case 1 : optionCalculer(); break;
      case 2 : variable = optionModifier(variable); break;
      case 3 : optionAfficher(variable); break;
      default : break;
    }
  }
}