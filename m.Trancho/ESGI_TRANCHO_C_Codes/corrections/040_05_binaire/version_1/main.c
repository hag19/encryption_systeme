/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 40.
 */

/* Version petits entiers (maximum : environ 4 000 000) */
#include <stdio.h>
#include <stdlib.h>

int main() {
  unsigned int nombreUser;
  unsigned int nombre;
  
  /* base10 permet de représenter les puissances de 2 */
  unsigned long base10 = 1;
  /* binaireView permet de sauvegarder la représentation       */
  /* binaire sous une représentation octale :                  */
  unsigned long binaireView = 0;
  
  /* Nous demandons la saisie d'un entier à l'utilisateur : */
  printf("Entrez un nombre : ");
  scanf("%u", &nombreUser);
  nombre = nombreUser;
  
  /* Tant que le nombre sur lequel nous travaillons est        */
  /* différent de 0                                            */
  while(nombre) {
    /* Nous ajoutons un 1 si son reste modulo 2 fait 1 */
    if(nombre % 2 == 1) {
      binaireView += base10;
    }
    /* Nous passons au chiffre suivant pour la puissance de 2  */
    /* représenté en base octale                               */
    base10 *= 010;
    /* Nous divisons le nombre par 2 pour passer au chiffre    */
    /* binaire suivant                                         */
    nombre /= 2;
  }
  
  /* Nous affichons le résultat en base octale ce qui donne la */
  /* représentation binaire pour des petits nombres :          */
  printf("%u = (%lo)_2\n", nombreUser, binaireView);
  exit(EXIT_SUCCESS);
}