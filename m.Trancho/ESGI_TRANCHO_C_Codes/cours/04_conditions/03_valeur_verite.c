/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	const int deux = 2;
	printf("2 == deux ? valeur de vérité : %d\n", 
		    2 == deux);
	printf("1 == deux ? valeur de vérité : %d\n", 
		    1 == deux);
	exit(EXIT_SUCCESS);
}