/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OP(name, symb, a, b) \
  printf("%s de %d et %d :\n", #name, a, b); \
  printf("%d %s %d = %d\n", a, symb, b, name(a, b));

int addition(int a, int b) { return a + b; }
int soustraction(int a, int b) { return a - b; }
int multiplication(int a, int b) { return a * b; }
int division(int a, int b) { return a / b; }
int modulo(int a, int b) { return a % b; }
int decalageGauche(int a, int b) { return a << b; }
int decalageDroite(int a, int b) { return a >> b; }

int main() {
	int first, second;
	char op[5];
	printf(">>> ");
	scanf("%d %s %d", &first, op, &second);
	if(strcmp("+", op) == 0) {
	  OP(addition, "+", first, second);
	} else if(strcmp("-", op) == 0) {
	  OP(soustraction, "-", first, second);
	} else if(strcmp("*", op) == 0) {
	  OP(multiplication, "*", first, second);
	} else if(strcmp("/", op) == 0) {
	  OP(division, "/", first, second);
	} else if(strcmp("%", op) == 0) {
	  OP(modulo, "%", first, second);
	} else if(strcmp("<<", op) == 0) {
	  OP(decalageGauche, "<<", first, second);
	} else if(strcmp(">>", op) == 0) {
	  OP(decalageDroite, ">>", first, second);
	}
	exit(EXIT_SUCCESS);
}