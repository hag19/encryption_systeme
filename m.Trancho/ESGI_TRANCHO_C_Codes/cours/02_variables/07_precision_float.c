/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	float un_float = 1e30f;
	double un_double = 1e30;
	long double un_long_double = 1e30l;
	printf("float       : %f\n", un_float);
	printf("double      : %f\n", un_double);
	printf("long double : %Lf\n", un_long_double);
	exit(EXIT_SUCCESS);
}