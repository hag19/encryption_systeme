/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

void afficher_terrain(int hauteur, int largeur, char terrain[hauteur][largeur]) {
    int ligne, colonne;
    for(ligne = 0; ligne < hauteur; ++ligne) {
        for(colonne = 0; colonne < largeur - 1; ++colonne) {
            putchar(terrain[ligne][colonne]);
        }
        putchar('\n');
    }
}

int main() {
    char terrain[5][7] = {
        "#.####",
        "#.#..#",
        "#...##",
        "#.#..#",
        "####.#"
    };
    afficher_terrain(5, 7, terrain);
    exit(EXIT_SUCCESS);
}