#include <stdio.h>
#include <stdlib.h>

int main() {
    int gros_nombre;
    printf("Entrez un gros nombre : ");
    scanf("%d", gros_nombre);
    printf("%d, un gros nombre ?\n");
    gros_nombre = 999999999999999999;
    printf("%d, un gros nombre !\n");
    exit(EXIT_SUCCESS);
}