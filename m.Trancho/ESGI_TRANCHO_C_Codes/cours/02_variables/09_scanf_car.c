/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	char caractere;
	printf("Entrez un caractere : ");
	scanf("%c", &caractere);
	printf("Voici votre caractere : '%c'\n", caractere);
	exit(EXIT_SUCCESS);
}