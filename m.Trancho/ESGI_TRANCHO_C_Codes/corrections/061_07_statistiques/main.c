/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 61.
 */

#include <stdio.h>
#include <stdlib.h>

#define TAILLE 10
/* min_index renvoie l'indice du plus petit élément de values */
int min_index(int values[], int taille);
/* min_value renvoie le plus petit élément de values */
int min_value(int values[], int taille);
/* max_index renvoie l'indice du plus grand élément de values */
int max_index(int values[], int taille);
/* max_value renvoie le plus grand élément de values */
int max_value(int values[], int taille);
/* moyenne renvoie la moyenne des éléments de values */
float moyenne(int values[], int taille);

int main() {
  int valeurs[TAILLE] = {5, 9, 1, 4, 8, 3, 0, 6, 2, 7};
  printf("minimum : valeurs[%d] = %d\n", 
    min_index(valeurs, TAILLE), min_value(valeurs, TAILLE));
  printf("maximum : valeurs[%d] = %d\n", 
    max_index(valeurs, TAILLE), max_value(valeurs, TAILLE));
  printf("moyenne : %g\n", moyenne(valeurs, TAILLE));
  exit(EXIT_SUCCESS);
}

int min_index(int values[], int taille) {
  int index = 0;
  int i;
  for(i = 1; i < taille; ++i) {
    if(values[i] < values[index]) {
      index = i;
    }
  }
  return index;
}

int min_value(int values[], int taille) {
  return values[min_index(values, taille)];
}

int max_index(int values[], int taille) {
  int index = 0;
  int i;
  for(i = 1; i < taille; ++i) {
    if(values[i] > values[index]) {
      index = i;
    }
  }
  return index;
}

int max_value(int values[], int taille) {
  return values[max_index(values, taille)];
}

float moyenne(int values[], int taille) {
  long somme = 0;
  int i;
  for(i = 0; i < taille; ++i) {
    somme += values[i];
  }
  return (float)somme / taille;
}