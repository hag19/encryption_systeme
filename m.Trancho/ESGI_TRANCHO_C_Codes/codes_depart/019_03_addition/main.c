#include <stdio.h>
#include <stdlib.h>

int main() {
    long big = 0;
    int ajout;
    printf("big vaut %ld, faîtes le grossir : ", big);
    scanf("%d", &ajout);
    big = ajout+++big;
    printf("big vaut %ld !\n", big);
    exit(EXIT_SUCCESS);
}