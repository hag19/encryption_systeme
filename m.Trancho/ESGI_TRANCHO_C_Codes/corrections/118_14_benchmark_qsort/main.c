/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 118.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE_DEMO      10
#define TAILLE_PERF      10000
#define TAILLE_BENCHMARK 10000000

void afficherInt(const void * elem) {
  printf("%d", *(int *)elem);
}

int copierInt(void * dest, const void * src) {
  *(int *)dest = *(const int *)src;
  return 1;
}

void randomInt(void * elem) {
  *(int *)elem = rand() % 1000000000;
}

int cmpInt(const void * first, const void * second) {
  return *(int *)first - *(int *)second;
}

/* afficher_tableau affiche la liste de ses éléments au format */
/* [e1, e2, ..., eN]                                           */
void afficher_tableau(const void * values, size_t elem, int taille, void (*afficherElement)(const void *));
/* copie_tableau recopie les éléments de source dans           */
/* destination                                                 */
void copier_tableau(void * destination, const void * source, size_t elem, int taille, int (*copierElement)(void *, const void *));
/* aleatoire remplit un tableau par des valeurs aléatoires */
void aleatoire(void * valeurs, size_t elem, int taille, void (*randomElement)(void *));
/* swap échange les valeurs référencées par deux adresses */
void swap(void * a, void * b, size_t elem);
/* trier_algo est une implémentation du tri par tas */
void trier_algo(void * valeurs, size_t elem, int taille, int (*cmpElements)(const void *, const void *));
/* trier_eleve est votre méthode pour trier un tableau */
void trier_eleve(void * valeurs, size_t elem, int taille, int (*cmpElements)(const void *, const void *));
/* verif_trier renvoie 1 si la tableau est trié et 0 sinon */
int verif_trier(const void * valeurs, size_t elem, int taille, int (*cmpElements)(const void *, const void *));

int main() {
  srand(time(NULL));
  int * valeurs = (int *)malloc(TAILLE_BENCHMARK * sizeof(int));
  int * methode_algo = (int *)malloc(TAILLE_BENCHMARK * sizeof(int));
  int * methode_qsort = (int *)malloc(TAILLE_BENCHMARK * sizeof(int));
  clock_t start, stop;
  
  aleatoire(valeurs, sizeof(int), TAILLE_DEMO, randomInt);
  copier_tableau(methode_algo, valeurs, sizeof(int), TAILLE_DEMO, copierInt);
  copier_tableau(methode_qsort, valeurs, sizeof(int), TAILLE_DEMO, copierInt);
  printf("non trié : ");
  afficher_tableau(valeurs, sizeof(int), TAILLE_DEMO, afficherInt);
  trier_algo(methode_algo, sizeof(int), TAILLE_DEMO, cmpInt);
  printf("methode_algo : ");
  afficher_tableau(methode_algo, sizeof(int), TAILLE_DEMO, afficherInt);
  qsort(methode_qsort, TAILLE_DEMO, sizeof(int), cmpInt);
  printf("methode_qsort : ");
  afficher_tableau(methode_qsort, sizeof(int), TAILLE_DEMO, afficherInt);
  
  aleatoire(valeurs, sizeof(int), TAILLE_PERF, randomInt);
  copier_tableau(methode_algo, valeurs, sizeof(int), TAILLE_PERF, copierInt);
  copier_tableau(methode_qsort, valeurs, sizeof(int), TAILLE_PERF, copierInt);
  printf("tableau de taille %d :\n", TAILLE_PERF);
  start = clock();
  trier_algo(methode_algo, sizeof(int), TAILLE_PERF, cmpInt);
  stop = clock();
  double temps_algo = (stop - start);
  printf("methode_algo %s\n", verif_trier(methode_algo, sizeof(int), TAILLE_PERF, cmpInt) ? "est trié" : "n'est pas trié");
  printf("Temps écoulé : %g s\n", temps_algo / CLOCKS_PER_SEC);
  start = clock();
  qsort(methode_qsort, TAILLE_PERF, sizeof(int), cmpInt);
  stop = clock();
  double temps_qsort = (stop - start);
  printf("methode_qsort %s\n", verif_trier(methode_qsort, sizeof(int), TAILLE_PERF, cmpInt) ? "est trié" : "n'est pas trié");
  printf("Temps écoulé : %g s\n", temps_qsort / CLOCKS_PER_SEC);
  printf("Soit une différence qsort / algo de l'ordre d'un facteur %g\n", temps_qsort / temps_algo);
  
  aleatoire(valeurs, sizeof(int), TAILLE_BENCHMARK, randomInt);
  copier_tableau(methode_algo, valeurs, sizeof(int), TAILLE_BENCHMARK, copierInt);
  copier_tableau(methode_qsort, valeurs, sizeof(int), TAILLE_BENCHMARK, copierInt);
  printf("tableau de taille %d :\n", TAILLE_BENCHMARK);
  start = clock();
  trier_algo(methode_algo, sizeof(int), TAILLE_BENCHMARK, cmpInt);
  stop = clock();
  temps_algo = (stop - start);
  printf("methode_algo %s\n", verif_trier(methode_algo, sizeof(int), TAILLE_BENCHMARK, cmpInt) ? "est trié" : "n'est pas trié");
  printf("Temps écoulé : %g s\n", temps_algo / CLOCKS_PER_SEC);
  start = clock();
  qsort(methode_qsort, TAILLE_BENCHMARK, sizeof(int), cmpInt);
  stop = clock();
  temps_qsort = (stop - start);
  printf("methode_qsort %s\n", verif_trier(methode_qsort, sizeof(int), TAILLE_BENCHMARK, cmpInt) ? "est trié" : "n'est pas trié");
  printf("Temps écoulé : %g s\n", temps_qsort / CLOCKS_PER_SEC);
  printf("Soit une différence qsort / algo de l'ordre d'un facteur %g\n", temps_qsort / temps_algo);
  free(valeurs);
  free(methode_algo);
  free(methode_qsort);
  exit(EXIT_SUCCESS);
}

void afficher_tableau(const void * values, size_t elem, int taille, void (*afficherElement)(const void *)) {
  int i;
  printf("[");
  for(i = 0; i < taille; ++i) {
    if(i) printf(", ");
    afficherElement((unsigned char *)values + elem * i);
  }
  printf("]\n");
}

void copier_tableau(void * destination, const void * source, size_t elem, int taille, int (*copierElement)(void *, const void *)) {
  int i;
  for(i = 0; i < taille; ++i) {
    copierElement((unsigned char *)destination + elem * i, (unsigned char *)source + elem * i);
  }
}

void aleatoire(void * valeurs, size_t elem, int taille, void (*randomElement)(void *)) {
  int i;
  for(i = 0; i < taille; ++i) {
    randomElement((unsigned char *)valeurs + elem * i);
  }
}

void swap(void * a, void * b, size_t elem) {
  int i;
  for(i = 0; i < elem; ++i) {
    *((unsigned char *)a + i) ^= *((unsigned char *)b + i);
    *((unsigned char *)b + i) ^= *((unsigned char *)a + i);
    *((unsigned char *)a + i) ^= *((unsigned char *)b + i);
  }
}

void trier_algo(void * valeurs, size_t elem, int taille, int (*cmpElements)(const void *, const void *)) {
  int indice;
  int current;
  int parent;
  for(indice = 1; indice < taille; ++indice) {
    current = indice;
    parent = (current - 1) / 2;
    while((current != 0) && (cmpElements((unsigned char *)valeurs + elem * current, (unsigned char *)valeurs + elem * parent) > 0)) {
      swap((unsigned char *)valeurs + elem * current, (unsigned char *)valeurs + elem * parent, elem);
      current = parent;
      parent = (current - 1) / 2;
    }
  }
  for(indice = taille - 1; indice >= 1; --indice) {
    swap((unsigned char *)valeurs + elem * indice, valeurs, elem);
    parent = 0;
    while(parent * 2 + 1 < indice) {
      if((parent * 2 + 2 >= indice) || (cmpElements((unsigned char *)valeurs + elem * (parent * 2 + 1), (unsigned char *)valeurs + elem * (parent * 2 + 2)) > 0)) {
        current = parent * 2 + 1;
      } else {
        current = parent * 2 + 2;
      }
      if(cmpElements((unsigned char *)valeurs + elem * current, (unsigned char *)valeurs + elem * parent) < 0) {
        break;
      }
      swap((unsigned char *)valeurs + elem * current, (unsigned char *)valeurs + elem * parent, elem);
      parent = current;
    }
  }
}

int verif_trier(const void * valeurs, size_t elem, int taille, int (*cmpElements)(const void *, const void *)) {
  int i;
  for(i = 1; i < taille; ++i) {
    if(cmpElements((unsigned char *)valeurs + elem * (i - 1), (unsigned char *)valeurs + elem * i) > 0)
      return 0;
  }
  return 1;
}