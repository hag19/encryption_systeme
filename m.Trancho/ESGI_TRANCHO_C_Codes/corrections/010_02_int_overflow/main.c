/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 10.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  /* Code Bob : int gros_nombre;                               */
  unsigned long gros_nombre;
  /* 1. En général, unsigned long donne un entier sous 8       */
  /* octets sans valeurs négatives et est donc le plus grand   */
  /* type d'entiers atomiques.                                 */
  /* Sous un compilateur 32 bits (selon votre installation,    */
  /* principalement sous Windows), il faudra utiliser unsigned */
  /* long long pour passer sur 8 octets.                       */
  printf("Entrez un gros nombre : ");
  /* Code Bob scanf("%d", gros_nombre);                        */
  scanf("%lu", &gros_nombre);
  /* Bob doit utiliser le format %lu pour lire un unsigned     */
  /* long (respectivement %llu pour unsigned long long).       */
  /* A noter que Bob a oublié de passer gros_nombre par son    */
  /* adresse &gros_nombre .                                    */
  /* Code Bob : printf("%d, un gros nombre ?\n");              */
  printf("%lu, un gros nombre ?\n", gros_nombre);
  /* Bob a oublié de lister la valeur de gros_nombre après la  */
  /* chaîne. */
  /* Le format d'affichage est de même %lu                     */
  /* (respectivement %llu). */
  gros_nombre = 999999999999999999;
  /* Code Bob : printf("%d, un gros nombre !\n");              */
  printf("%lu, un gros nombre !\n", gros_nombre);
  gros_nombre = 0xffffffffffffffff;
  /* 2. */
  printf("%lu\n", gros_nombre);
  /* 3. */
  printf("%lx\n", gros_nombre);
  int entier = 0xffffffffffffffff;
  /* 4. gros nombre affiché en hexadécimal comme un int        */
  /* (4 octets).                                               */
  printf("%lx\n", entier);
  /* int est limité à la fois par le bit de signe et par son   */
  /* occupation mémoire.                                       */
  printf("%016lx\n", entier);
  exit(EXIT_SUCCESS);
}