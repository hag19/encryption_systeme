#include <stdio.h>
#include <stdlib.h>

int main() {
    float racine = 1.414213562373095048;
    printf("racine de 2 vaut %g\n", racine);
    printf("variable : %.18f\n", racine);
    printf("texte    : 1.414213562373095048\n");
    /* C'est différent, étrange ... */
    float clavier;
    printf("Recopiez :\n>1.414213562373095048\n>");
    scanf("%f", &clavier);
    printf("copie : %.18f\n", clavier);
    printf("texte : 1.414213562373095048\n");
    /* C'est la machine qui bug ! */
    exit(EXIT_SUCCESS);
}