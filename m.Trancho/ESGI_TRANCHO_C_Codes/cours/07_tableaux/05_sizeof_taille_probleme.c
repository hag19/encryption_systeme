/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

void afficher_taille_tableau(float tableau[]) {
    printf("depuis une fonction : %lu\n", sizeof(tableau));
}

int main() {
    float tableau[16];
    printf("depuis main : %lu\n", sizeof(tableau));
    afficher_taille_tableau(tableau);
    exit(EXIT_SUCCESS);
}