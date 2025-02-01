/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	int case_cochee = 1;
	printf("case_cochée ? %d\n", case_cochee);
	case_cochee = ! case_cochee;
	printf("case_cochée ? %d\n", case_cochee);
	case_cochee = ! case_cochee;
	printf("case_cochée ? %d\n", case_cochee);
	exit(EXIT_SUCCESS);
}