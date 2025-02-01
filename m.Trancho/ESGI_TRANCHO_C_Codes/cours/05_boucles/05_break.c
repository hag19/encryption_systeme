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
		printf("Entrez un nombre positif s'il-vous-plaît : ");
		scanf("%d", &nombre);
		++repetitions;
		if(repetitions > 3) {
		    printf("Ça suffit !\n");
		    break;
		}
	} while(nombre < 0);

	if(nombre < 0) {
		printf("Ragequit.\n");
		exit(EXIT_FAILURE);
	}
	printf("Oh, un nombre positif : %d\n", nombre);
	exit(EXIT_SUCCESS);
}