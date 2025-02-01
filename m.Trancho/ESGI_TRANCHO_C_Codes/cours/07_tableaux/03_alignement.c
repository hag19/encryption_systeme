/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	int tableau[] = {1, 2, 3};
	printf("adresse de tableau    : %p\n", tableau);
	printf("adresse de tableau[0] : %p\n", &tableau[0]);
	printf("adresse de tableau[1] : %p\n", &tableau[1]);
	printf("adresse de tableau[2] : %p\n", &tableau[2]);
	exit(EXIT_SUCCESS);
}