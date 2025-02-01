/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE * input = fopen("03_cesar.c", "r");
	FILE * output = fopen("resultat.txt", "w");
	int caractere;
	const int cle = 5;
	/* tant qu'on lit un caractère dans le fichier */
	while((caractere = fgetc(input)) != EOF) {
	  /* on le code s'il est alphabéthique */
	  if(caractere >= 'a' && caractere <= 'z')
		caractere = (caractere - 'a' + cle) % 26 + 'a';
	  else if(caractere >= 'A' && caractere <= 'Z')
		caractere = (caractere - 'A' + cle) % 26 + 'A';
	  /* on l'écrit dans le fichier de sortie*/
	  fputc(caractere, output);
	}
	fclose(input);
	fclose(output);
	exit(EXIT_SUCCESS);
}