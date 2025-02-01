/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	const int taille_liste = 16;
	int liste[taille_liste];
	int i;

	for(i = 0; i < taille_liste; ++i) {
		if(i < 2) {
		    liste[i] = i;
		} else {
		    liste[i] = liste[i - 1] + liste[i - 2];
		}
	}

	for(i = 0; i < taille_liste; ++i) {
		if(i) {
		    printf(", ");
		}
		printf("%d", liste[i]);
	}
	printf("\n");
	exit(EXIT_SUCCESS);
}