/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 65.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define CAPACITE_MAX 1000

int valeurs[CAPACITE_MAX];
int taille;

void init() {
  taille = 0;
}

void ajouter(int valeur) {
  if(taille >= CAPACITE_MAX) {
    printf("[Info] : taille maximale atteinte.\n");
    return;
  }
  valeurs[taille++] = valeur;
}

void supprimer() {
  if(taille <= 0) {
    printf("[Info] : aucune valeur.\n");
    return;
  }
  printf("[Info] : dernière valeur de la liste : %d\n", 
    valeurs[--taille]);
}

void afficher() {
  printf("Liste : [");
  int i;
  for(i = 0; i < taille; ++i) {
    if(i) {
      printf(", ");
    }
    printf("%d", valeurs[i]);
  }
  printf("]\n");
}

void trier(int vals[], int taille) {
  int min_cur = 0;
  int max_cur = taille - 1;
  int i;
  /* Tant que les curseurs de fin et de début ne se croisent   */
  /* pas :                                                     */
  while(min_cur < max_cur) {
    for(i = min_cur; i < max_cur + 1; ++i) {
      /* Nous échangeons le minimum actuel avec la position    */
      /* regardée si plus petite :                             */
      if(vals[i] < vals[min_cur]) {
        vals[i] ^= vals[min_cur];
        vals[min_cur] ^= vals[i];
        vals[i] ^= vals[min_cur];
      }
      /* Nous échangeons la maximum avec la position actuelle  */
      /* si plus grande :                                      */
      if(vals[i] > vals[max_cur]) {
        vals[i] ^= vals[max_cur];
        vals[max_cur] ^= vals[i];
        vals[i] ^= vals[max_cur];
      }
    }
    /* Nous avançons d'un pas en tête et reculons d'un pas en  */
    /* queue de la liste.                                      */
    ++min_cur;
    --max_cur;
  }
}

void stats() {
  int tmp_vals[CAPACITE_MAX];
  int i;
  double somme = 0;
  if(taille <= 0) {
    printf("[Info] : aucune valeur.\n");
    return;
  }
  /* Nous sommons et sauvegardons les valeurs de la liste      */
  /* actuelle.                                                 */
  for(i = 0; i < taille; ++i) {
    somme += tmp_vals[i] = valeurs[i];
  }
  /* Nous trions la liste de valeurs sauvegardées pour         */
  /* déterminer médianes et quartiles.                         */
  trier(tmp_vals, taille);
  double moyenne = somme / taille;
  somme = 0;
  /* Nous sommons les carrés des distances à la moyenne pour   */
  /* calculer l'écart type :                                   */
  for(i = 0; i < taille; ++i) {
    somme += pow(moyenne - valeurs[i], 2.);
  }
  double ecart_type = sqrt(somme / taille);
  double min, q1, q2, q3, max;
  /* Nous calculons extremums et quartiles depuis la liste     */
  /* triée des valeurs :                                       */
  min = tmp_vals[0];
  q1 = 0.25 * (tmp_vals[(taille - 1) / 4] 
             + tmp_vals[(taille - 0) / 4] 
             + tmp_vals[(taille + 1) / 4] 
             + tmp_vals[(taille + 2) / 4]);
  q2 = 0.5 * (tmp_vals[(taille - 1) / 2] 
            + tmp_vals[taille / 2]);
  q3 = 0.25 * (tmp_vals[(3 * taille - 3) / 4] 
             + tmp_vals[(3 * taille - 2) / 4] 
             + tmp_vals[(3 * taille - 1) / 4] 
             + tmp_vals[(3 * taille) / 4]);
  max = tmp_vals[taille - 1];
  printf("Statistiques :\n"
         " - moyenne :       %g\n"
         " - ecart type :    %g\n"
         " - minimum :       %g\n"
         " - 1er quartile :  %g\n"
         " - mediane :       %g\n"
         " - 3eme quartile : %g\n"
         " - maximum :       %g\n",
         moyenne,
         ecart_type,
         min, q1, q2, q3, max);
}

void rechercher(int valeur) {
  int i;
  for(i = 0; i < taille; ++i) {
    if(valeurs[i] == valeur) {
      printf("%d trouvé à l'indice %d.\n", valeur, i);
    }
  }
}

void do_action(char action[]) {
  /* Nous référeçons les action possibles via cette fonction   */
  /* et récupérons des paramètres si nécessaire :              */
  if(strcmp(action, "ajouter") == 0) {
    int v;
    scanf("%d", &v);
    ajouter(v);
  } else if(strcmp(action, "supprimer") == 0) {
    supprimer();
  } else if(strcmp(action, "rechercher") == 0) {
    int v;
    scanf("%d", &v);
    rechercher(v);
  } else if(strcmp(action, "afficher") == 0) {
    afficher();
  } else if(strcmp(action, "statistiques") == 0) {
    stats();
  } else if(strcmp(action, "trier") == 0) {
    trier(valeurs, taille);
  } else if(strcmp(action, "quitter") == 0) {
  } else {
    printf("[Info] : Action invalide.\n"
           "Actions possibles :\n"
           " - ajouter [VALEUR]\n"
           " - supprimer\n"
           " - rechercher [VALEUR]\n"
           " - afficher\n"
           " - statistiques\n"
           " - trier\n"
           " - quitter\n");
  }
}

int main() {
  char action[50];
  init();
  do {
    printf(">>> ");
    scanf("%s", action);
    do_action(action);
  } while(strcmp(action, "quitter") != 0);
  exit(EXIT_SUCCESS);
}