/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	int nombre = 0;
	int repetitions = 0;
	do {
		printf("Entrez un nombre positif : ");
		scanf("%d", &nombre);
		++repetitions;
		if(repetitions < 2) {
		    continue;
		}
		printf("Entrez un nombre négatif : ");
		scanf("%d", &nombre);
		nombre *= -1;
	} while(nombre < 0);
	printf("Oh, un nombre positif : %d\n", nombre);
	exit(EXIT_SUCCESS);
}