/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	char texte[] = "Hello !";
	char * pointeur = NULL;
	for(pointeur = texte; *pointeur != '\0'; ++pointeur) {
	  if(*pointeur >= 'a' && *pointeur <= 'z')
		*pointeur += 'A' - 'a';
	}
	printf("%s\n", texte); /* affiche "HELLO !" */
	exit(EXIT_SUCCESS);
}