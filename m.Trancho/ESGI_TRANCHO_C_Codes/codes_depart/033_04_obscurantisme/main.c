#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, b;
    printf("Entrez deux nombres : ");
    scanf("%d %d", &a, &b);
    if(!(a - b))
        printf("%d et %d sont égaux\n", a, b);
    else
        printf("Entre %d et %d, le plus petit est %d\n", a, b, ((long)(unsigned int)(a - b) == a - b) ? b : a);
    exit(EXIT_SUCCESS);
}