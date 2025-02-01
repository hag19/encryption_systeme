/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 92.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  /* Nous préparons un pointeur qui référencera vers la plage  */
  /* mémoire des données allouée dynamiquement une fois que    */
  /* nous connaîtrons la taille souhaitée.                     */
  int * data = NULL;
  /* Taille des données : donnée par l'utilisateur. */
  int taille;
  /* Curseur vers l'élément courant dans nos données. */
  int i = 0;
  int j;
  /* Commande donnée par un caractère. */
  char op;
  /* Demande de la taille des données : */
  printf("taille de la mémoire : ");
  scanf("%d", &taille);
  /* Allocation d'une plage mémoire de 'taille' donnée où les  */
  /* valeurs sont initialisées à zéro (ce que fait calloc      */
  /* automatiquement).                                         */
  /* Notons qu'ici nous affectons data dans la condition par   */
  /* l'adresse renvoyée par calloc. La condition nous permet   */
  /* ici de vérifier si l'allocation a échoué ou non.          */
  /* En cas d'échec c'est NULL qui a été affecté à data et     */
  /* donc (data = ...) vaudrait NULL.                          */
  if((data = (int *)calloc(taille, sizeof(int))) == NULL) {
    /* Dans le cas où l'allocation dynamique échoue, nous      */
    /* l'indiquons à l'utilisateur.                            */
    printf("Erreur allocation\n");
    /* Puis, nous terminons l'execution. */
    exit(EXIT_FAILURE);
  }
  /* getchar lit un caractère : celui-ci sera utilisé comme    */
  /* commande ou termine si l'utilisateur entre le caractère   */
  /* 'q'.                                                      */
  op = getchar();
  while(op != 'q') {
    /* Selon le caractère entré nous lancerons une commande    */
    /* associée.                                               */
    /* Note : les caractères sont des entiers, un caractère    */
    /* donné entre '' est une constante entière.               */
    switch(op) {
      /* décalage du curseur vers la droite (retour au début   */
      /* si dépassement).                                      */
      case '>' : i = (i + 1) % taille; break;
      /* décalage du curseur vers la gauche (retour en fin si  */
      /* dépassement).                                         */
      case '<' : i = (i + taille - 1) % taille; break;
      /* incrémentation de la valeur au curseur. */
      case '+' : data[i]++; break;
      /* décrémentation de la valeur au curseur. */
      case '-' : data[i]--; break;
      /* affichage des éléments de la mémoire utilisée. */
      case '.' : {
        printf("[");
        for(j = 0; j < taille; ++j) {
          /* si l'indice j n'est pas 0, ce n'est pas le        */
          /* premier tour de boucle.                           */
          if(j) printf(", ");
          printf("%d", data[j]);
        }
        printf("]\n");
      } break;
      /* Toutes les valeurs en mémoire prennent la valeur      */
      /* regardée par le curseur.                              */
      case '=' : {
        for(j = 0; j < taille; ++j) {
          data[j] = data[i];
        }
      } break;
    }
    /* On lit la commande pour le tour de boucle suivant. */
    op = getchar();
  }
  /* Toute allocation doit être rendue, on pense à la libérer. */
  free(data);
  exit(EXIT_SUCCESS);
}