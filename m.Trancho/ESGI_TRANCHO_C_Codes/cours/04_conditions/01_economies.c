/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	const int prix_jeu = 60;
	int argent = 0;
	printf("Combien avez-vous d'argent ? ");
	scanf("%d", &argent);

	if(prix_jeu < argent) {
		printf("J'achète le jeu !\n");
	} else {
		printf("Il faudra encore economiser ...\n");
	}
	exit(EXIT_SUCCESS);
}