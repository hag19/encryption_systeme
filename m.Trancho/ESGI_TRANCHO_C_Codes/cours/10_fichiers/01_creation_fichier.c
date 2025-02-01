/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE * fichier = NULL;
	if((fichier = fopen("MonFichier.txt", "w")) == NULL) {
	  printf("Erreur de création de mon fichier.\n");
	  exit(EXIT_FAILURE);
	}
	printf("Fichier créé avec succès.\n");
	fclose(fichier);
	fichier = NULL;
	exit(EXIT_SUCCESS);
	exit(EXIT_SUCCESS);
}