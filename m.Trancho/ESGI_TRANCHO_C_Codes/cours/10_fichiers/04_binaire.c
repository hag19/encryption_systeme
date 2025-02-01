/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int sauvegarderListe(const char * filepath, const int * liste, int taille) {
  FILE * output = fopen(filepath, "wb");
  /* écriture de la taille : une variable */
  if(fwrite(&taille, sizeof(int), 1, output) != 1) {
    printf("Erreur écriture taille\n");
    return 0;
  }
  /* écriture de la liste : un tableau */
  if(fwrite(liste, sizeof(int), taille, output) != taille) {
    printf("Erreur écriture liste\n");
    return 0;
  }
  fclose(output);
  return 1;
}

int chargerListe(const char * filepath, int ** liste, int * taille) {
  FILE * input = fopen(filepath, "rb");
  /* lecture de la taille : nécessaire à l'allocation */
  if(fread(taille, sizeof(int), 1, input) != 1) {
    printf("Erreur lecture taille\n");
    return 0;
  }
  /* allocation de la liste */
  if((*liste = (int *)malloc(sizeof(int) * *taille)) == NULL) {
    printf("Erreur allocation liste\n");
    return 0;
  }
  /* lecture des éléments de la liste */
  if(fread(*liste, sizeof(int), *taille, input) != *taille) {
    printf("Erreur lecture liste\n");
    return 0;
  }
  fclose(input);
  return 1;
}

int main() {
	const char * liste_path = "liste.bin";
	int liste[] = {5, 42, 1};
	if(! sauvegarderListe(liste_path, liste, 3)) {
		fprintf(stderr, "Echec écriture liste : arrêt.\n");
		exit(EXIT_FAILURE);
	}
	int * res = NULL;
	int taille = 0;
	if(! chargerListe(liste_path, &res, &taille)) {
		fprintf(stderr, "Echec lecture liste : arrêt.\n");
		exit(EXIT_FAILURE);
	}
	int i;
	printf("liste : [");
	for(i = 0; i < taille; ++i) {
		if(i) printf(", ");
		printf("%d", res[i]);
	}
	printf("]\n");
	free(res);
	exit(EXIT_SUCCESS);
}