/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	int i;
	unsigned int valeur;
	for(i = 0; i < 31; ++i) {
	  valeur = ((unsigned int)1 << i);
	  printf("%12u | 0x%08X | %2de bit à 1\n", valeur, valeur, i + 1);
	}
	exit(EXIT_SUCCESS);
}