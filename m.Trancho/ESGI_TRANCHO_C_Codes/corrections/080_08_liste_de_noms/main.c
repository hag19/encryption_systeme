/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 80.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ** mots = NULL;
int taille = 0;
int capacite = 0;

/* Mise à jouer de la capacité du tableau : */
void update() {
  if(taille < capacite) {
    return ;
  }
  capacite = taille * 2 + 10;
  if((mots = (char **)realloc(mots, capacite * sizeof(char *))) == NULL) {
    printf("Allocation impossible.\n");
    exit(EXIT_SUCCESS);
  }
}

int rechercher(const char * mot) {
  int i;
  for(i = 0; i < taille; ++i) {
    if(strcmp(mots[i], mot) == 0) {
      return i;
    }
  }
  return -1;
}

int ajouter(const char * mot) {
  update();
  if(rechercher(mot) >= 0) {
    return 0;
  }
  mots[taille++] = strdup(mot);
  return 1;
}

int supprimer(const char * mot) {
  int i;
  if((i = rechercher(mot)) < 0) {
    return 0;
  }
  free(mots[i]);
  for( ; i < taille - 1; ++i) {
    mots[i] = mots[i + 1];
  }
  --taille;
  return 1;
}

void afficher() {
  printf("Mots : {\n");
  int i;
  for(i = 0; i < taille; ++i) {
    printf("  - \"%s\"\n", mots[i]);
  }
  printf("}\n");
}

void do_action(const char * action) {
  char buffer[100];
  if(strcmp(action, "ajouter") == 0) {
    scanf("%s", buffer);
    if(ajouter(buffer)) {
      printf("[Info] : ajout réussi.\n");
    } else {
      printf("[Info] : %s existe déjà.\n", buffer);
    }
  } else if(strcmp(action, "supprimer") == 0) {
    scanf("%s", buffer);
    if(supprimer(buffer)) {
      printf("[Info] : suprpression réussie.\n");
    } else {
      printf("[Info] : %s n'existe pas dans la liste.\n", 
        buffer);
    }
  } else if(strcmp(action, "rechercher") == 0) {
    scanf("%s", buffer);
    if(rechercher(buffer) >= 0) {
      printf("[Info] : %s trouvé.\n", buffer);
    } else {
      printf("[Info] : %s non trouvé.\n", buffer);
    }
  } else if(strcmp(action, "afficher") == 0) {
    afficher();
  } else if(strcmp(action, "quitter") == 0) {
    
  } else {
    printf("[Info] : \"%s\" action inconnue.\n", action);
    printf("Actions possibles :\n"
           " - ajouter [mot]\n"
           " - supprimer [mot]\n"
           " - rechercher [mot]\n"
           " - afficher\n"
           " - quitter\n");
  }
}

int main() {
  char buffer[100];
  do {
    printf(">>> ");
    scanf("%s", buffer);
    do_action(buffer);
  } while(strcmp(buffer, "quitter") != 0);
  for(--taille; taille >= 0; --taille) {
    free(mots[taille]);
  }
  if(mots) free(mots);
  exit(EXIT_SUCCESS);
}