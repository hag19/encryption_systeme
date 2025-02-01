#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "arraylist.h"
#include "hashmap.h"

#define BENCHMARKS
#undef BENCHMARKS

#ifdef BENCHMARKS
#define CAPACITY   10000
#define ELEMENTS   1000000
#define RESEARCHES 10000
#else
#define CAPACITY 5
#define ELEMENTS 20
#endif

int main() {
  HashMap * map = HashMap_creer(CAPACITY);
  ArrayList * liste = ArrayList_creer(CAPACITY);
  long seed = time(NULL);
  int value;
  long i;
#ifdef BENCHMARKS
  int count;
  fprintf(stderr, "Filling ArrayList\n");
  clock_t start, stop;
  start = clock();
#endif
  srand(seed);
  for(i = 0; i < ELEMENTS; ++i) {
    value = rand() % ELEMENTS;
    ArrayList_ajouter(liste, value);
  }
#ifdef BENCHMARKS
  stop = clock();
  fprintf(stderr, "Filling completed in %g s\n", (double)(stop - start) / CLOCKS_PER_SEC);
  fprintf(stderr, "Filling HashMap\n");
  start = clock();
#endif
  srand(seed);
  for(i = 0; i < ELEMENTS; ++i) {
    value = rand() % ELEMENTS;
    HashMap_ajouter(map, value);
  }
#ifdef BENCHMARKS
  stop = clock();
  fprintf(stderr, "Filling completed in %g s\n", (double)(stop - start) / CLOCKS_PER_SEC);
#endif
#ifndef BENCHMARKS
  HashMap_afficher(stdout, map);
  ArrayList_afficher(stdout, liste);
#else
  seed *= 42;
  fprintf(stderr, "Research in ArrayList\n");
  start = clock();
  srand(seed);
  count = 0;
  for(i = 0; i < RESEARCHES; ++i) {
    value = rand() % ELEMENTS;
    count += ArrayList_compter(liste, value);
  }
  stop = clock();
  fprintf(stderr, "Research completed in %g s\n", (double)(stop - start) / CLOCKS_PER_SEC);
  fprintf(stderr, "Counting %d elements\n", count);
	
  fprintf(stderr, "Research in HashMap\n");
  start = clock();
  srand(seed);
  count = 0;
  for(i = 0; i < RESEARCHES; ++i) {
    value = rand() % ELEMENTS;
    count += HashMap_compter(map, value);
  }
  stop = clock();
  fprintf(stderr, "Research completed in %g s\n", (double)(stop - start) / CLOCKS_PER_SEC);
  fprintf(stderr, "Counting %d elements\n", count);
#endif
  HashMap_free(&map);
  ArrayList_free(&liste);
  exit(EXIT_SUCCESS);
}