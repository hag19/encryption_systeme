/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 110.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node {
  int value;
  Node * next;
};

Node * Node_alloc(int value) {
  Node * node = NULL;
  if((node = (Node *)malloc(sizeof(Node))) == NULL) {
    fprintf(stderr, "Erreur allocation Node.\n");
    return NULL;
  }
  node->value = value;
  node->next = NULL;
  return node;
}

void Node_free(Node ** liste) {
  if(liste == NULL || *liste == NULL) {
    return;
  }
  Node_free(&((*liste)->next));
  free(*liste);
  *liste = NULL;
}

int Node_ajouter(Node ** liste, int value) {
  Node * current = NULL;
  if((current = Node_alloc(value)) == NULL) {
    return 0;
  }
  current->next = *liste;
  *liste = current;
  return 1;
}

void Node_afficher(const Node * liste) {
  printf("[");
  for(; liste != NULL; liste = liste->next) {
    printf("%d", liste->value);
    if(liste->next != NULL) printf(", ");
  }
  printf("]\n");
}

int main() {
  Node * liste = NULL;
  int valeurs[] = {1, 2, 3, 4, -1};
  int i;
  for(i = 0; valeurs[i] >= 0; ++i) {
    if(! Node_ajouter(&liste, valeurs[i])) {
      Node_free(&liste);
      fprintf(stderr, "Erreur ajout liste : arrêt.\n");
      exit(EXIT_FAILURE);
    }
  }
  Node_afficher(liste);
  Node_free(&liste);
  exit(EXIT_SUCCESS);
}