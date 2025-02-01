/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 94.
 */

/* Alternative avec utilisation de types structurés : */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Association nom - numéro. */
typedef struct Node Node;
struct Node {
  char * nom;
  long numero;
};

/* Liste dynamique d'associations nom - numéro. */
typedef struct Liste Liste;
struct Liste {
  Node * data;
  int taille;
  int capacite;
};

/* Initialisation d'une liste. */
Liste Liste_creer();

/* Ajout d'une association à la liste. */
/* Renvoie 0 si échec. */
int Liste_ajouter(Liste *, const char * nom, long numero);

/* Recherche dans la liste par nom. */
/* Renvoie 1 et affecte numero si trouvé. */
/* Renvoie 0 si échec. */
int Liste_rechercher(const Liste *, const char * nom, long * numero);

/* Libère la liste. */
void Liste_free(Liste *);

int main() {
  Liste liste = Liste_creer();
  char tmpNom[50];
  long tmpNumero;
  for(;;) {
    printf("Nom (None pour arrêter) : ");
    scanf("%s", tmpNom);
    if(strcmp(tmpNom, "None") == 0) {
      break;
    }
    printf("Numéro : ");
    scanf("%ld", &tmpNumero);
    if(! Liste_ajouter(&liste, tmpNom, tmpNumero)) {
      fprintf(stderr, "Erreur ajout de (\"%s\", %ld) dans la liste.\n", tmpNom, tmpNumero);
      Liste_free(&liste);
      exit(EXIT_FAILURE);
    }
  }
  for(;;) {
    printf("Nom à rechercher (None pour arrêter) :\n>>> ");
    scanf("%s", tmpNom);
    if(strcmp(tmpNom, "None") == 0) {
      break;
    }
    if(! Liste_rechercher(&liste, tmpNom, &tmpNumero)) {
      printf("\"%s\" non trouvé.\n", tmpNom);
      continue;
    }
    printf("Le numéro de \"%s\" est %ld\n", tmpNom, tmpNumero);
  }
  Liste_free(&liste);
  exit(EXIT_SUCCESS);
}

/* Partie implémentation */

Liste Liste_creer() {
  Liste res = {NULL, 0, 0};
  return res;
}

int Liste_update(Liste * liste) {
  if(liste->taille >= liste->capacite) {
    liste->capacite = liste->capacite * 2 + 10;
    if((liste->data = (Node *)realloc(liste->data, liste->capacite * sizeof(Node))) == NULL) {
      return 0;
    }
  }
  return 1;
}

int Liste_ajouter(Liste * liste, const char * nom, long numero) {
  if(! Liste_update(liste)) {
    fprintf(stderr, "Erreur extension de la liste.\n");
    return 0;
  }
  if((liste->data[liste->taille].nom = strdup(nom)) == NULL) {
    fprintf(stderr, "Erreur duplication de \"%s\".\n", nom);
    return 0;
  }
  liste->data[liste->taille].numero = numero;
  ++(liste->taille);
  return 1;
}

int Liste_rechercher(const Liste * liste, const char * nom, long * numero) {
  int i;
  for(i = 0; i < liste->taille; ++i) {
    if(strcmp(liste->data[i].nom, nom) == 0) {
      if(numero) {
        *numero = liste->data[i].numero;
      }
      return 1;
    }
  }
  return 0;
}

void Liste_free(Liste * liste) {
  int i;
  for(i = 0; i < liste->taille; ++i) {
    free(liste->data[i].nom);
  }
  if(liste->data) {
    free(liste->data);
    liste->data = NULL;
  }
}