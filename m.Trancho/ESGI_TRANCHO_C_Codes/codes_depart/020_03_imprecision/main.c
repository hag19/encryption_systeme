#include <stdio.h>
#include <stdlib.h>

int main() {
    float resultat = 1.;
    float ajout = 1e-9;
    printf("resultat = %.15f\n", resultat);
    printf("on ajoute  %.15f\n", ajout);
    resultat += ajout;
    printf("resultat = %.15f\n", resultat);
    /* Pourquoi resultat ne change pas ? */
    exit(EXIT_SUCCESS);
}