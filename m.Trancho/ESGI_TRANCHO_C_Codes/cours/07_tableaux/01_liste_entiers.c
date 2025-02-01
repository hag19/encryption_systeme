/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	int liste[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, -1};
	int i;
	for(i = 0; liste[i] >= 0; ++i) {
		if(i) {
		    printf(", ");
		}
		printf("%d", liste[i]);
	}
	printf("\n");
	exit(EXIT_SUCCESS);
}