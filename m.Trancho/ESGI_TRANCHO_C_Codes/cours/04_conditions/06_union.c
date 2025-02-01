/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	float x_personnage;
	printf("Quelle est l'abscisse du personnage ? ");
	scanf("%f", &x_personnage);
	if((x_personnage <= 1) || (x_personnage >= 4)) {
		printf("Le personnage est sur le sol.\n");
	} else {
		printf("Oups, regardez sous vos pieds !\n");
	}
	exit(EXIT_SUCCESS);
}