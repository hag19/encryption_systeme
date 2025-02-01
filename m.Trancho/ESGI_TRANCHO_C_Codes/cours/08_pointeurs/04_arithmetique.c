/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	int tableau[] = {1, 2, 3, -1};
	int * pointeur = tableau;
	printf("&pointeur[1] :    %p\n", &pointeur[1]);
	printf("(pointeur + 1) :  %p\n", pointeur + 1);
	printf("pointeur[1] :     %d\n", pointeur[1]);
	printf("*(pointeur + 1) : %d\n", *(pointeur + 1));
	printf("*(1 + pointeur) : %d\n", *(1 + pointeur));
	printf("1[pointeur] :     %d\n", 1[pointeur]);
	exit(EXIT_SUCCESS);
}