/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE * fichier = fopen("02_lecture_fichier.c", "r");
	int caractere;
	/* tant qu'on lit un caractère dans le fichier */
	while((caractere = fgetc(fichier)) != EOF) {
	  putchar(caractere); /* on affiche le caractere */
	}
	fclose(fichier);
	exit(EXIT_SUCCESS);
}