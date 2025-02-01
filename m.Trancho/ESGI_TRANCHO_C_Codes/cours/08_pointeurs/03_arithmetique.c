/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	int tableau[] = {1, 2, 3, -1};
	int * pointeur = tableau;
	printf("tableau :        %p\n", tableau);
	printf("&tableau[1] :    %p\n", &tableau[1]);
	printf("&pointeur[1] :   %p\n", &pointeur[1]);
	printf("(tableau + 1) :  %p\n", tableau + 1);
	printf("(pointeur + 1) : %p\n", pointeur + 1);
	exit(EXIT_SUCCESS);
}