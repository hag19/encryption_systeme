/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	int first, second;
	int count;
	printf(">>> ");
	while(scanf("%d + %d", &first, &second) == 2) {
		printf("%d\n", first + second);
		printf(">>> ");
	}
	printf("Terminé\n");
	exit(EXIT_SUCCESS);
}