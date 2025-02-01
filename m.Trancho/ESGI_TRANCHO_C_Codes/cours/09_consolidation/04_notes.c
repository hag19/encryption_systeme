/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	float * notes = NULL;
	float somme = 0;
	int nombre;
	int i;
	printf("Combien de CC ? ");
	scanf("%d", &nombre);
	if(nombre <= 0) {
	  printf("Pas de notes pas de moyenne.\n");
	  exit(EXIT_FAILURE);
	}
	/* allocation dynamique depuis le nombre donné par l'utilisateur */
	if((notes = (float *)malloc(sizeof(float) * nombre)) == NULL) {
	  printf("Erreur d'allocation.\n");
	  exit(EXIT_FAILURE);
	}
	for(i = 0; i < nombre; ++i) {
	  scanf("%f", notes + i);
	  somme += notes[i];
	}
	printf("La moyenne de ");
	for(i = 0; i < nombre; ++i) {
	  if(i && i == nombre - 1) printf(" et ");
	  else if(i > 0) printf(", ");
	  printf("%g", notes[i]);
	}
	printf(" est %g\n", somme / nombre);

	free(notes);
	notes = NULL;
	exit(EXIT_SUCCESS);
}