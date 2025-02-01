/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 50.
 */

#include <stdio.h>
#include <stdlib.h>

/* Lecture d'un entier, recommence en cas d'erreur. */
int scanInt() {
  int res = 0;
  /* scanf renvoie le nombre de formats correctement lus. */
  while(scanf("%d", &res) != 1) {
    printf("\n[Info] : Un entier sur %lu octets est attendu.\n", sizeof(int));
    /* Pour débloquer la lecture de scanf à la ligne suivante, */
    /* on peut consommer la ligne actuelle.                    */
    while(getchar() != '\n');
  }
  return res;
}

/* Liste de caractères valides : permet l'anticipation de      */
/* l'erreur en amont.                                          */
int carIsOp(char op) {
  return '+' == op
  ||     '-' == op
  ||     '/' == op
  ||     '*' == op
  ||     '%' == op
  ||     '^' == op;
    
}

/* Lecture d'un opérateur valide. */
char scanOp() {
  char res = 0;
  int valid = 0;
  do {
    scanf(" %c", &res);
    valid = carIsOp(res);
    if(! valid) {
      printf("\n[Info] : Opérateur incorrect. Attendu +, -, *, /, %% ou ^.\n");
    }
  } while(! valid);
  return res;
}

/* Opérations : */

long addInt(int first, int second) {
  return (long)first + second;
}

long subInt(int first, int second) {
  return (long)first - second;
}

long mulInt(int first, int second) {
  return (long)first * second;
}

double divInt(int first, int second) {
  if(second == 0) {
    printf("\n[Info] : division par 0.\n");
    /* Le choix est d'informer l'utilisateur mais non de       */
    /* corriger l'erreur.                                      */
  }
  return (double)first / second;
}

int modInt(int first, int second) {
  if(second == 0) {
    printf("\n[Info] : division par 0.\n");
    /* Le choix est d'informer l'utilisateur mais non de       */
    /* corriger l'erreur.                                      */
  }
  return first % second;
}

long powInt(int first, int second) {
  if(second < 0) {
    return 0;
  }
  long res = 1;
  for(; second > 0; --second) {
    res *= first;
  }
  return res;
}

void compute(int first, char op, int second) {
  switch(op) {
  
    case '+' : {
      printf(" = %ld\n", addInt(first, second));
    } break;
    
    case '-' : {
      printf(" = %ld\n", subInt(first, second));
    } break;
    
    case '*' : {
      printf(" = %ld\n", mulInt(first, second));
    } break;
    
    case '/' : {
      printf(" = %lg\n", divInt(first, second));
    } break;
    
    case '%' : {
      printf(" = %d\n", modInt(first, second));
    } break;
    
    case '^' : {
      printf(" = %ld\n", powInt(first, second));
    } break;
  }
}

int main() {
  int first, second;
  char op;
  printf(">>> ");
  first = scanInt();
  op = scanOp();
  second = scanInt();
  compute(first, op, second);
  exit(EXIT_SUCCESS);
}