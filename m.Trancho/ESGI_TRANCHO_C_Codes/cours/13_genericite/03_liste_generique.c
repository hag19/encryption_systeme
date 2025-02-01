/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Liste Liste;
struct Liste {
  void * data;
  long taille;
  long capacite;
  size_t elementTaille;
  void (* elementFree)(void *);
  void (* elementPrint)(void *);
};

int Liste_create(
    Liste * liste, long capacite, size_t elementTaille,
    void (* elementFree)(void *), void (* elementPrint)(void *)) {
  liste->data = NULL;
  liste->taille = 0;
  liste->capacite = capacite;
  liste->elementTaille = elementTaille;
  liste->elementFree = elementFree;
  liste->elementPrint = elementPrint;
  if((liste->data = malloc(elementTaille * capacite)) == NULL) {
    fprintf(stderr, "Liste_create : Erreur allocation liste.\n");
    return 1; /* code d'erreur allocation */
  }
  return 0;
}

void Liste_free(Liste * liste) {
  if(liste == NULL || liste->data == NULL) {
  	return;
  }
  long i;
  if(liste->elementFree) {
    for(i = 0; i < liste->taille; ++i) {
      liste->elementFree((unsigned char *)(liste->data) + (i * liste->elementTaille));
    }
  }
  free(liste->data);
  liste->data = NULL;
}

void Liste_afficher(Liste * liste) {
  long i;
  printf("[");
  for(i = 0; i < liste->taille; ++i) {
    if(i) printf(", ");
    liste->elementPrint((unsigned char *)(liste->data) + (i * liste->elementTaille));
  }
  printf("]\n");
}

int Liste_ajouter(Liste * liste, void * element) {
  if(liste->taille >= liste->capacite) {
    void * tmp = NULL;
    int new_capacite = liste->capacite * 2 + 10;
    if((tmp = realloc(liste->data, new_capacite * liste->elementTaille)) == NULL) {
      fprintf(stderr, "Liste_ajouter : Erreur reallocation.\n");
      return 1; /* code d'erreur allocation */
    }
    liste->data = tmp;
    liste->capacite = new_capacite;
  }
  memcpy((unsigned char *)(liste->data) + (liste->taille * liste->elementTaille), element, liste->elementTaille);
  ++(liste->taille);
  return 0;
}

void intPrint(int * value) {
  printf("%d", *value);
}

int main() {
  Liste intListe;
  if(Liste_create(&intListe, 0, sizeof(int), NULL, (void (*)(void *))&intPrint)) {
    fprintf(stderr, "Erreur allocation intListe : arrêt.\n");
    exit(EXIT_FAILURE);
  }
  int valeur;
  printf("Entrez des valeurs positives : ");
  scanf("%d", &valeur);
  while(valeur >= 0) {
    Liste_ajouter(&intListe, &valeur);
    scanf("%d", &valeur);
  }
  Liste_afficher(&intListe);
  Liste_free(&intListe);
  
  exit(EXIT_SUCCESS);
}