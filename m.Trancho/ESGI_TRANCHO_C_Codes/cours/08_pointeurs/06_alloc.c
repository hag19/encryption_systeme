/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	int i;
	int taille = 5;
	int * tableau = NULL;
	if((tableau = (int *)calloc(taille, sizeof(int))) == NULL) {
		exit(EXIT_FAILURE);
	}
	for(i = 0; i < taille; ++i) {
		tableau[i] = i;
	}
	for(i = 0; i < taille; ++i) {
		if(i) { printf(", "); }
		printf("%d", tableau[i]);
	}
	printf("\n");

	taille = 10;
	if((tableau = (int *)realloc(tableau, sizeof(int) * taille)) == NULL) { 
		exit(EXIT_FAILURE);
	}
	for(i = 5; i < taille; ++i) {
		tableau[i] = 10 - i;
	}
	for(i = 0; i < taille; ++i) {
		if(i) { printf(", "); }
		printf("%d", tableau[i]);
	}
	printf("\n");
	free(tableau);
	tableau = NULL;
	exit(EXIT_SUCCESS);
}