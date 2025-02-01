/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 23.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  unsigned int entier;
  printf("Entrez un entier : ");
  scanf("%u", &entier);
  /* Extraction des octets à l'aide d'un décalage par l'hexadécimal : */
  /* - diviser par 0x10 permet de tronquer un chiffre en hexadécimal (soit 4 bits). */
  /* - le reste d'une divisio par 0x10 permet de récupérer le dernier chiffre en hexadécimal (4 bits). */
  /* Nous appliquons ce procédé pour récupérer les valeurs des octets (8 bits) dans entier : */
  printf("%u = %u.%u.%u.%u\n", entier, entier / 0x1000000, (entier / 0x10000) % 0x100, (entier / 0x100) % 0x100, entier % 0x100);
  
  unsigned char a, b, c, d;
  printf("Saisir une adresse IPv4 : ");
  scanf("%hhu.%hhu.%hhu.%hhu", &a, &b, &c, &d);
  /* Construction de la valeur sur un entier par décalage par une puissance de 16^2 = 256 : */
  entier = a * 0x1000000 + b * 0x10000 + c * 0x100 + d * 0x1;
  printf("%u.%u.%u.%u = %u\n", a, b, c, d, entier);
  
  exit(EXIT_SUCCESS);
}