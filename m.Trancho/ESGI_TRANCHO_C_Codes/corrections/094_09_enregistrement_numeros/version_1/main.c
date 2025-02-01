/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 94.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* allocStr permet de faire une copie allouée de la chaîne     */
/* texte.                                                      */
/* À noter qu'une fois que vous savez la coder et que vous     */
/* êtes conscients qu'une allocation dynamique y est réalisée, */
/* vous pouvez utiliser strdup pour dupliquer une chaîne de    */
/* caractères.                                                 */
char * allocStr(const char * texte) {
  char * res = NULL;
  /* Allocation de la plage mémoire nécessaire à la sauvegarde */
  /* des caractères et du marqueur de fin. */
  if((res = (char *)malloc((1 + strlen(texte)) * sizeof(char))) 
      == NULL) {
    return NULL;
  }
  /* Copie des caractères de la chaîne texte à la chaîne res   */
  /* (allouée).                                                */
  strcpy(res, texte);
  /* Renvoi de la chaîne allouée. */
  return res;
}

/* rechercher va regarder dans la table 'noms' de taille       */
/* 'taille' si une chaîne 'texte' existe.                      */
/* Ceci renvoie un indice positif ou nul si trouvé et -1       */
/* sinon.                                                      */
int rechercher(const char * texte, char ** noms, int taille) {
  int i;
  /* Parcours de éléments de noms */
  for(i = 0; i < taille; ++i) {
    /* Dans le cas où un élément correspond à la chaîne        */
    /* recherchée                                              */
    if(strcmp(texte, noms[i]) == 0) {
      /* nous renvoyons son indice */
      return i;
    }
  }
  /* Fin de la boucle : aucun élément de correspond à la       */
  /* chaîne recherchée, elle n'est pas présente. Nous          */
  /* renvoyons alors -1.                                       */
  return -1;
}

int main() {
  /* Tableau dynamique sur des chaînes de caractères. */
  char ** noms = NULL;
  /* Tableau dynamique sur des entiers. */
  long * numeros = NULL;
  /* buffer permettant la lecture temporaire d'un nom : chaîne */
  /* de caractères.                                            */
  char tmpNom[50];
  /* variable permettant la lecture temporaire d'un numéro :   */
  /* entier.                                                   */
  long tmpNumero;
  /* nombre d'éléments et capacité des tableaux dynamiques. */
  int taille = 0, capacite = 0;
  /* indice dans les tableaux : pour la recherche d'éléments. */
  int position;
  /* Boucle forever : condition d'arrêt à l'intérieur. */
  for(;;) {
    /* Lecture d'un nom : */
    printf("Nom (None pour arrêter) : ");
    scanf("%s", tmpNom);
    /* Si l'utilisateur a saisi "None" on arrête la boucle. */
    if(strcmp(tmpNom, "None") == 0) {
      break;
    }
    /* Lecture du numéro associé au nom : */
    printf("Numéro : ");
    scanf("%ld", &tmpNumero);
    /* Dans le cas où le nombre d'éléments a atteint la        */
    /* capacité des tableaux, allons augmenter la capacité     */
    /* pour accueilir le nouvel élément :                      */
    if(taille >= capacite) {
      /* Nous doublons la capacité et ajoutons 10 pour les     */
      /* petites capacités.                                    */
      capacite = capacite * 2 + 10;
      /* Réallocation de la liste de noms : */
      if((noms = (char **)realloc(noms, capacite 
          * sizeof(char *))) == NULL) {
        printf("Erreur allocation liste des noms\n");
        exit(EXIT_FAILURE);
      }
      /* Réallocation de la liste de numéros : */
      if((numeros = (long *)realloc(numeros, capacite 
          * sizeof(long))) == NULL) {
        printf("Erreur allocation liste des numeros\n");
        exit(EXIT_FAILURE);
      }
    }
    /* Ajout d'une copie du nom lu comme nouvel élément de la  */
    /* liste 'noms'.                                           */
    if((noms[taille] = allocStr(tmpNom)) == NULL) {
      printf("Erreur allocation nom \"%s\"\n", tmpNom);
      exit(EXIT_FAILURE);
    }
    /* Ajout du numéro lu à la liste 'numeros'. */
    numeros[taille] = tmpNumero;
    /* Comptabilisation d'un élément de plus. */
    ++taille;
  }
  /* Boucle de recherche d'associations nom - numéro : */
  for(;;) {
    /* Lecture clavier d'un nom à rechercher : */
    printf("Nom à rechercher (None pour arrêter) :\n>>> ");
    scanf("%s", tmpNom);
    /* Arrêt si "None" : */
    if(strcmp(tmpNom, "None") == 0) {
      break;
    }
    /* Récupération de la position dans la liste 'noms'. Si    */
    /* négatif : non trouvé.                                   */
    if((position = rechercher(tmpNom, noms, taille)) < 0) {
      /* On informe l'utilisateur de l'échec de sa requette et */
      /* on relance la boucle.                                 */
      printf("\"%s\" non trouvé.\n", tmpNom);
      continue;
    }
    /* Nous affichons le numéro associé depuis l'indice        */
    /* correspondant obtenu dans 'noms'.                       */
    printf("Le numéro de \"%s\" est %ld\n", tmpNom, 
      numeros[position]);
  }
  /* Nous libérons toutes les chaînes allouées : */
  for(--taille; taille >= 0; --taille) {
    free(noms[taille]);
  }
  /* Nous libérons les tableaux dynamiques : */
  free(noms);
  noms = NULL;
  free(numeros);
  numeros = NULL;
  exit(EXIT_SUCCESS);
}