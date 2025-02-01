/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 66.
 */

#include <stdio.h>
#include <stdlib.h>

char read_command() {
  char command;
  printf(">>> ");
  scanf(" %c", &command);
  return command;
}

int find(int valeur, int liste[], int taille) {
  int start = 0;
  int end = taille;
  int mid;
  while(end - start > 0) {
    mid = (start + end) / 2;
    if(liste[mid] < valeur) {
      start = mid + 1;
    } else if(liste[mid] > valeur) {
      end = mid;
    } else {
      return mid;
    }
  }
  if(taille > 0 && liste[start] == valeur) {
    return start;
  }
  return -1;
}

int add(int valeur, int liste[], int taille) {
  int i;
  for(i = taille; i >= 0 && liste[i - 1] > valeur; --i) {
    liste[i] = liste[i - 1];
  }
  liste[i] = valeur;
  return taille + 1;
}

void display(int liste[], int taille) {
  int i;
  printf("[");
  for(i = 0; i < taille; ++i) {
    if(i != 0) {
      printf(", ");
    }
    printf("%d", liste[i]);
  }
  printf("]\n");
}

int main() {
  int liste[1024];
  int taille = 0;
  char command;
  while((command = read_command()) != 'q') {
    switch(command) {
      case '+' : {
        int valeur;
        scanf("%d", &valeur);
        taille = add(valeur, liste, taille);
      } break;
      
      case '=' : {
        int valeur;
        scanf("%d", &valeur);
        if(find(valeur, liste, taille) >= 0) {
          printf("%d existe dans la liste.\n", valeur);
        } else {
          printf("%d non trouvé dans la liste.\n", valeur);
        }
      } break;
      
      case '.' : {
        display(liste, taille);
      } break;
      
      default : {
        printf(
          "commande non reconnue :\n"
          "+ [ENTIER] : ajouter une valeur\n"
          "= [ENTIER] : rechercher une valeur\n"
          ". : affiche la liste\n"
          "q : quitter\n"
        );
      } break;
    }
  }
  exit(EXIT_SUCCESS);
}