/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

void afficher_chaine(char * chaine) {
    for(; *chaine != '\0'; ++chaine) {
        putchar(*chaine);
    }
    putchar('\n');
}

int main() {
    char texte[] = "Hello ESGI !";
    afficher_chaine(texte);
    exit(EXIT_SUCCESS);
}