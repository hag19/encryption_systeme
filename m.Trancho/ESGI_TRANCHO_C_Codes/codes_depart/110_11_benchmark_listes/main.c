#include <stdio.h>
#include <stdlib.h>
typedef struct LinkedList * LinkedList;
struct LinkedList {
  int value;
  LinkedList next;
};

/* Renvoie une liste vide */
LinkedList LL_empty();
void LL_free(LinkedList * liste);
int LL_add_tail(LinkedList * liste, int value);
int LL_add_tail(LinkedList * liste, int value);
int LL_add_head(LinkedList * liste, int value);
int LL_insert(LinkedList * liste, int id, int value);
int LL_pop_tail(LinkedList * liste, int * value);
int LL_pop_head(LinkedList * liste, int * value);
int LL_delete(LinkedList * liste, int id, int * value);
void LL_print(FILE * flow, const LinkedList * liste);
int main(){
  LinkedList list = LL_empty();
  return 0;
}



/* Renvoie une liste vide */
LinkedList LL_empty(){
LinkedList newlist = (LinkedList *)malloc(sizeof(LinkedList));
if(newlist==NULL){
  return ;
  }
  return newlist;
}
/* Libère la liste */
void LL_free(LinkedList * liste){
while(*liste!=NULL){
  LinkedList temp = *liste;
  *liste = (*liste)->next;
  free(temp);
}
};

/* Ajoute un élément en fin */
int LL_add_tail(LinkedList * liste, int value){
LinkedList newnode = (LinkedList)malloc(sizeof(LinkedList));
if(newnode==NULL){
  return 0;
}
newnode->next = NULL;
newnode->value = value;
while(*liste!=NULL){
  liste = &(*liste)->next;
}
(*liste)->next = newnode; 
}

/* Ajoute un élément en tête */
int LL_add_head(LinkedList * liste, int value){
LinkedList newnode = (LinkedList)malloc(sizeof(LinkedList));
if(newnode==NULL){
  return 0;
}
newnode->next = *liste;
newnode->value = value;
*liste = newnode;
}

/* Ajoute un élément à une position donnée */
int LL_insert(LinkedList * liste, int id, int value){
  while(liste!=NULL && id>0){
    liste = &(*liste)->next;
    id--;
  }
  (*liste)->value = value;
}

/* Supprime l'élément en fin */
int LL_pop_tail(LinkedList * liste, int * value){
  while(*liste!=NULL){
    liste = &(*liste)->next;
  }

}

/* Supprime l'élément en tête */
int LL_pop_head(LinkedList * liste, int * value){
  LinkedList temp = *liste;
  *liste = (*liste)->next;
  *value = temp->value;
  free(temp);
}

/* Supprime l'élément à une position donnée */
int LL_delete(LinkedList * liste, int id, int * value){
  LinkedList temp = *liste;
  while(liste!=NULL && id>0){
    temp = *liste;
    liste = &(*liste)->next;
    id--;
  }
  temp->next = (*liste)->next;
  *value=(*liste)->value;
  free(*liste);
}

/* Affiche la liste */
void LL_print(FILE * flow, const LinkedList * liste){
  while(*liste!=NULL){
    fprintf(flow, "%d ", (*liste)->value);
    liste = &(*liste)->next;
  }
  fprintf(flow, "\n");
}

