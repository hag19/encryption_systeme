/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 102.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * allocStr(const char * texte) {
  char * res = NULL;
  if((res = (char *)malloc((1 + strlen(texte)) * sizeof(char))) == NULL) {
    return NULL;
  }
  strcpy(res, texte);
  return res;
}

int rechercher(const char * texte, char ** noms, int taille) {
  int i;
  for(i = 0; i < taille; ++i) {
    if(strcmp(texte, noms[i]) == 0) {
      return i;
    }
  }
  return -1;
}

/* L'ajout pouvant se faire depuis la lecture d'un fichier et  */
/* la saisie utilisateur, nous factorisons le code pour        */
/* réaliser l'ajout par cette fonction.                        */
void ajouter(const char * nom, long numero, char *** noms, long ** numeros, int * taille, int * capacite) {
  if(*taille >= *capacite) {
    *capacite = *capacite * 2 + 10;
    if((*noms = (char **)realloc(*noms, *capacite * sizeof(char *))) == NULL) {
      printf("Erreur allocation liste des noms\n");
      exit(EXIT_FAILURE);
    }
    if((*numeros = (long *)realloc(*numeros, *capacite * sizeof(long))) == NULL) {
      printf("Erreur allocation liste des numeros\n");
      exit(EXIT_FAILURE);
    }
  }
  if(((*noms)[*taille] = allocStr(nom)) == NULL) {
    printf("Erreur allocation nom \"%s\"\n", nom);
    exit(EXIT_FAILURE);
  }
  (*numeros)[*taille] = numero;
  ++(*taille);
}

int main(int argc, char * argv[]) {
  char ** noms = NULL;
  long * numeros = NULL;
  char tmpNom[50];
  long tmpNumero;
  int taille = 0, capacite = 0;
  int position;
  char * inputPath = NULL;
  char * outputPath = NULL;
  FILE * input = NULL;
  FILE * output = NULL;
  int i;
  /* Nous bouclons sur les arguments à la recherche des        */
  /* options possibles                                         */
  for(i = 1; i < argc - 1; ++i) {
    if(strcmp(argv[i], "-i") == 0) {
      inputPath = argv[i + 1];
      ++i;
      continue;
    } else if(strcmp(argv[i], "-o") == 0) {
      outputPath = argv[i + 1];
      ++i;
      continue;
    }
  }
  /* Si fichier d'entrée est fourni, nous ajoutons les         */
  /* éléments depuis ce fichier.                               */
  if(inputPath) {
    if((input = fopen(inputPath, "r")) != NULL) {
      fscanf(input, "%s", tmpNom);
      while(strcmp(tmpNom, "None") != 0) {
        fscanf(input, "%ld", &tmpNumero);
        ajouter(tmpNom, tmpNumero, &noms, &numeros, &taille, &capacite);
        fscanf(input, "%s", tmpNom);
      }
      fclose(input);
      input = NULL;
    } else {
      fprintf(stderr, "Ouverture en lecture de \"%s\" impossible.\n", inputPath);
    }
  }
  /* Nous ajoutons les éléments saisis par l'utilisateur. */
  for(;;) {
    printf("Nom (None pour arrêter) : ");
    scanf("%s", tmpNom);
    if(strcmp(tmpNom, "None") == 0) {
      break;
    }
    printf("Numéro : ");
    scanf("%ld", &tmpNumero);
    ajouter(tmpNom, tmpNumero, &noms, &numeros, &taille, &capacite);
  }
  /* Nous sauvegardons les ajouts de l'utilisateur. */
  if(outputPath) {
    if((output = fopen(outputPath, "w+")) != NULL) {
      for(i = 0; i < taille; ++i) {
        fprintf(output, "%s %ld\n", noms[i], numeros[i]);
      }
      fprintf(output, "None\n");
      fclose(output);
      output = NULL;
    } else {
      fprintf(stderr, "Ouverture en écriture de \"%s\" impossible.\n", outputPath);
    }
  }
  /* Nous laissons l'utilisateur rechercher des associations   */
  /* depuis des noms.                                          */
  for(;;) {
    printf("Nom à rechercher (None pour arrêter) :\n>>> ");
    scanf("%s", tmpNom);
    if(strcmp(tmpNom, "None") == 0) {
      break;
    }
    if((position = rechercher(tmpNom, noms, taille)) < 0) {
      printf("\"%s\" non trouvé.\n", tmpNom);
      continue;
    }
    printf("Le numéro de \"%s\" est %ld\n", tmpNom, numeros[position]);
  }
  for(--taille; taille >= 0; --taille) {
    free(noms[taille]);
  }
  free(noms);
  noms = NULL;
  free(numeros);
  numeros = NULL;
  exit(EXIT_SUCCESS);
}