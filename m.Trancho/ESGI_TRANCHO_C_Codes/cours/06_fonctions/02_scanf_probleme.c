/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	int age = -1;
	while(age < 0) {
	  printf("Entrez votre age : ");
	  scanf("%d", &age);
	}
	printf("Vous avez donc %d ans\n", age);
	exit(EXIT_SUCCESS);
}