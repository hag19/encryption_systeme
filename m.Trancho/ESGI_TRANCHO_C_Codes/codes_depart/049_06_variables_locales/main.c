#include <stdio.h>
#include <stdlib.h>

int main() {
  int first, second;
  char res;
  printf(">>> ");
  scanf("%d %c %d", &first, &res, &second);
  switch(res) {
    case '+' : 
      int res = first + second;
      printf(" = %d\n", res);
      break;
  	
    case '*' : 
      long res = (long)first * second;
      printf(" = %ld\n", res);
      break;
  	
    case '/' : 
      double res = (double)first / second;
      printf(" = %lg\n", res);
      break;
  }
  exit(EXIT_SUCCESS);
}