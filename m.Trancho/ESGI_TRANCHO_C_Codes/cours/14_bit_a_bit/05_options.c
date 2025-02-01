/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

typedef enum {
  OPTION1 = 0x0001,
  OPTION2 = 0x0002,
  OPTION3 = 0x0004
} Options;

int main() {
	Options first = OPTION1 | OPTION2;
	Options second = OPTION2 | OPTION3;
	Options result = first | second;
	if(result & OPTION1)
	  printf("option 1\n");
	if(result & OPTION2)
	  printf("option 2\n");
	if(result & OPTION3)
	  printf("option 3\n");
	exit(EXIT_SUCCESS);
}