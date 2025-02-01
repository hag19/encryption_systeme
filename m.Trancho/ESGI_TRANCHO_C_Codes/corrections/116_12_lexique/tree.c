/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 116.
 */

#include "tree.h"

#include <stdlib.h>

Node * Node_alloc(char key, int value) {
  Node * res = NULL;
  if((res = (Node *)malloc(sizeof(Node))) == NULL) {
    return NULL;
  }
  res->key = key;
  res->value = value;
  res->lower = NULL;
  res->upper = NULL;
  res->next = NULL;
  res->prev = NULL;
  return res;
}

void Node_free(Node ** node) {
  if(node == NULL || *node == NULL) {
    return;
  }
  Node_free(&((*node)->lower));
  Node_free(&((*node)->upper));
  Node_free(&((*node)->next));
  free(*node);
  *node = NULL;
}

int Node_ajouter_chaine(Node ** node, const char * chaine) {
  Node * prev = *node;
  for(;;) {
    while(*node != NULL) {
      if(*chaine < (*node)->key) {
        node = &((*node)->lower);
      } else if(*chaine > (*node)->key) {
        node = &((*node)->upper);
      } else {
        break;
      }
    }
    if(*node == NULL) {
      if((*node = Node_alloc(*chaine, 0)) == NULL) {
        return 0;
      }
      (*node)->prev = prev;
    }
    ++((*node)->value);
    if(*chaine == '\0') {
      break;
    }
    ++chaine;
    node = &((*node)->next);
    prev = *node;
  }
  return 1;
}

static void Node_afficher_aux(FILE * flow, const Node * node, char * chaine, int offset) {
  if(node == NULL) return;
  Node_afficher_aux(flow, node->lower, chaine, offset);
  if((*(chaine + offset) = node->key) == '\0') {
    fprintf(flow, "%s : %d\n", chaine, node->value);
  }
  Node_afficher_aux(flow, node->next, chaine, offset + 1);
  Node_afficher_aux(flow, node->upper, chaine, offset);
}

void Node_afficher(FILE * flow, const Node * node) {
  char buff[100] = "";
  Node_afficher_aux(flow, node, buff, 0);
}

static void Node_afficher_all_aux(FILE * flow, const Node * node, char * chaine, int offset) {
  if(node == NULL) return;
  Node_afficher_all_aux(flow, node->lower, chaine, offset);
  if(node->key != '\0') {
    *(chaine + offset) = node->key;
    *(chaine + offset + 1) = '\0';
    fprintf(flow, "%d : %s\n", node->value, chaine);
  }
  Node_afficher_all_aux(flow, node->next, chaine, offset + 1);
  Node_afficher_all_aux(flow, node->upper, chaine, offset);
}

void Node_afficher_all(FILE * flow, const Node * node) {
  char buff[100] = "";
  Node_afficher_all_aux(flow, node, buff, 0);
}