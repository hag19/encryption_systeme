/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	unsigned long giant = 0xffffffffffffffff;
	printf("int  : 0x%016x (%u)\n", giant, giant);
	printf("long : 0x%016lx (%lu)\n", giant, giant);
	exit(EXIT_SUCCESS);
}