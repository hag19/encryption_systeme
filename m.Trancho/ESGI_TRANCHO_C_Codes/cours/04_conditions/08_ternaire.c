/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	int a, b;
	int minimum;
	printf("Entrez deux entiers : ");
	scanf("%d %d", &a, &b);
	minimum = (a < b) ? a : b;
	printf("Le minimum de %d et %d est %d\n", a, b, minimum);
	exit(EXIT_SUCCESS);
}