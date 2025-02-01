/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LISTOP(name, symb) {#name, #symb, name}

int addition(int a, int b) { return a + b; }
int soustraction(int a, int b) { return a - b; }
int multiplication(int a, int b) { return a * b; }
int division(int a, int b) { return a / b; }
int modulo(int a, int b) { return a % b; }
int decalageGauche(int a, int b) { return a << b; }
int decalageDroite(int a, int b) { return a >> b; }

typedef struct OperationBinaire OperationBinaire;
struct OperationBinaire {
  char * nom;
  char * symbole;
  int (* operateur)(int, int);
};

OperationBinaire * getFromSymbole(const char * symbole, OperationBinaire * liste) {
  for(; liste->nom != NULL; ++liste) {
    if(strcmp(symbole, liste->symbole) == 0) {
      return liste;
    }
  }
  return NULL;
}

int main() {

	/* Ajoutez vos opérations ici : */
	OperationBinaire operations[] = {
	  LISTOP(addition, +),
	  LISTOP(soustraction, -),
	  LISTOP(multiplication, *),
	  LISTOP(division, /),
	  LISTOP(modulo, %),
	  LISTOP(decalageGauche, <<),
	  LISTOP(decalageDroite, >>),
	  {NULL}
	};

	int first, second;
	OperationBinaire *ops = NULL;
	char op[5];
	printf(">>> ");
	scanf("%d %s %d", &first, op, &second);
	if((ops = getFromSymbole(op, operations)) != NULL) {
	  printf("%s de %d et %d :\n", ops->nom, first, second);
	  printf("%d %s %d = %d\n", first, ops->symbole, second, ops->operateur(first, second));
	}
	exit(EXIT_SUCCESS);
}