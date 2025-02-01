/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	int deux = 2;
	if(deux == 1)
		printf("Pas possible !\n");
	if(deux = 1)
		printf("Non plus !\n");
	printf("deux = 1 ???\n");
	if(deux == 1)
		printf("Oui oui !\n");
	printf("deux = %d !\n", deux);
	exit(EXIT_SUCCESS);
}