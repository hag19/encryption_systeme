/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 40.
 */

/* Version grands entiers */
#include <stdio.h>
#include <stdlib.h>

int main() {
  unsigned long nombreUser;
  unsigned long nombre;
  
  /* Nous construisons la plus grande puissance de 2 par       */
  /* l'hexadécimal. Nous avons besoin de construire le plus    */
  /* grand nombre en binaire commençant par 1 :                */
  /* 1000 0000 ... 0000 */
  unsigned long base2 = 0x8000000000000000;
  
  /* Nous récupérons la saisie de l'utilisateur : */
  printf("Entrez un nombre : ");
  scanf("%lu", &nombreUser);
  nombre = nombreUser;
  
  /* Nous recherchons la plus grande puissance de 2 que l'on   */
  /* pourrait soustraire au nombre de l'utilisateur.           */
  /* (Ceci permet d'éviter l'affichage de 0 inutiles)          */
  while(base2 > nombre) {
    base2 /= 2;
  }
  
  /* Nous commençons l'affichage : */
  printf("%lu = (", nombreUser);
  /* Tant que nous avons une puissance de 2 : */
  while(base2 > 0) {
    /* Si la puissance peut se soustraire au nombre */
    if(base2 <= nombre) {
      /* Nous affichons le 1 présent dans la représentation    */
      /* binaire                                               */
      printf("1");
      nombre -= base2;
    } else {
      /* Sinon la puissance est absente de la représentation   */
      /* binaire                                               */
      printf("0");
    }
    /* Nous passons à la puissance suivante */
    base2 /= 2;
  }
  printf(")_2\n");
  exit(EXIT_SUCCESS);
}