#include <stdio.h>
#include <stdlib.h>

/* Debut de votre code : */
/* Fin de votre code. */

void compute(int first, char op, int second) {
  switch(op) {
    case '+' : 
      printf(" = %ld\n", addInt(first, second));
      break;
    case '-' : 
      printf(" = %ld\n", subInt(first, second));
      break;
    case '*' : 
      printf(" = %ld\n", mulInt(first, second));
      break;
    case '/' : 
      printf(" = %lg\n", divInt(first, second));
      break;
    case '%' : 
      printf(" = %d\n", modInt(first, second));
      break;
    case '^' : 
      printf(" = %ld\n", powInt(first, second));
      break;
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