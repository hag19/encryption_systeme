/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 39.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  /* Nous récupérons les informations fournies par Oscar : */
  unsigned int k = 2015201261;
  unsigned int p = 4285404239;
  /* Nous sauvegarderons la clé secrète d'Oscar dans s : */
  unsigned int s = 1;
  
  /* Nous recherchons itérativement la solution à l'équation   */
  /* qui validerait la clé secrète :                           */
  while(((unsigned long)k * s) % p != 1) {
    ++s;
  }
  
  /* Nous affichons l'équation : */
  printf("%u * %u = %lu [%u]\n", s, k, ((unsigned long)k * s) % p, p);
  
  /* Nous vérifions que la clé fonctionne pour l'exemple donné */
  /* dans un exercice précédent :                              */
  if((((unsigned long)s * 0xfee1900d) % p) == 0x5c003212) {
  
    printf("Nous avons la clé secrète d\'Oscar !\nCette clé vaut %u (0x%x)", s, s);
    
  } else {
  
    printf("Visiblement, ceci n\'a pas fonctionné...\n");
  }
  
  exit(EXIT_SUCCESS);
}