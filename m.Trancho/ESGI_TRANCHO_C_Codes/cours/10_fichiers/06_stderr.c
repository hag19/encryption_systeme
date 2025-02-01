/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE * fichier = NULL;
	if((fichier = fopen("fichier_a_ne_pas_creer", "r")) == NULL) {
	  fprintf(stderr, "Erreur main() : \"fichier_a_ne_pas_creer\" est introuvable\n");
	  exit(EXIT_FAILURE);
	}
	fclose(fichier);
	exit(EXIT_SUCCESS);
}