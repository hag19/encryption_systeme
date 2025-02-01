/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	float x, y;
	printf("Entrez des coordonnées x y : ");
	scanf("%f %f", &x, &y);
	if((x >= 0) && (x <= 1) && (y >= 0) && (y <= 1)) {
		printf("Bien joué : (%g, %g) est dans la boîte ((0, 0), (1, 1))\n", x, y);
	} else {
		printf("Raté : (%g, %g) n'est pas dans la boîte ((0, 0), (1, 1))\n", x, y);
	}
	exit(EXIT_SUCCESS);
}