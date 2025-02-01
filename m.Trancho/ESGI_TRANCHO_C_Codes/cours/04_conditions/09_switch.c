/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	int choix;
	printf("1 - Jouer\n2 - Options\n3 - Ragequit\n---\nVotre choix ? ");
	scanf("%d", &choix);
	switch(choix) {
		case 1 :
		    printf("Que le jeu commence !\n");
		    break;
		case 2 :
		    printf("Paramétrons ça.\n");
		    break;
		case 3 :
		    printf("Bien, au revoir !\n");
		    break;
		default :
		    printf("Hum, le choix %d, je ne comprends pas ce choix...\n", choix);
	}
	exit(EXIT_SUCCESS);
}