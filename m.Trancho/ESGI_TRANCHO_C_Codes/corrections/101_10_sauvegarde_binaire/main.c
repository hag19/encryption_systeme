/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 101.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int savePerso(FILE * output, const char * nom, int vie, int atk, int def, int vit) {
  int tailleNom = strlen(nom);
  /* Nous sauvegardons les éléments constituants le personnage */
  /* en écriture binaire.                                      */
  /* fwrite prend une adresse sur les données à écrire, la     */
  /* taille d'un élément, le nombre d'éléments et où l'écrire. */
  /* Nous vérifions que le nombre d'éléments souhaités ont     */
  /* bien été écrits.                                          */
  if(fwrite(&tailleNom, sizeof(int), 1, output) != 1
  || fwrite(nom, sizeof(char), tailleNom, output) != tailleNom
  || fwrite(&vie, sizeof(int), 1, output) != 1
  || fwrite(&atk, sizeof(int), 1, output) != 1
  || fwrite(&def, sizeof(int), 1, output) != 1
  || fwrite(&vit, sizeof(int), 1, output) != 1) {
    fprintf(stderr, "Erreur d'écriture du personnage \"%s\".\n", nom);
    return 0;
  }
  return 1;
}

int loadPerso(FILE * input, char ** nom, int * vie, int * atk, int * def, int * vit) {
  int tailleNom;
  /* fread fonctionne similairement à fwrite. */
  /* Nous récupérons la taille. */
  if(fread(&tailleNom, sizeof(int), 1, input) != 1) {
    fprintf(stderr, "Erreur de lecture d'un personnage.\n");
    return 0;
  }
  /* Depuis la connaissance de la taille, nous allons la plage */
  /* mémoire pour recevoir le nom inscrit dans le fichier.     */
  if((*nom = (char *)malloc((tailleNom + 1) * sizeof(char))) == NULL) {
    fprintf(stderr, "Erreur alloc nom\n");
    return 0;
  }
  /* Nous lisons le nom depuis le fichier : affectation des    */
  /* caractères.                                               */
  if(fread(*nom, sizeof(char), tailleNom, input) != tailleNom) {
    fprintf(stderr, "Erreur de lecture d'un personnage.\n");
    free(*nom);
    *nom = NULL;
    return 0;
  }
  (*nom)[tailleNom] = '\0';
  /* Nous lisons les autres stats. */
  if(fread(vie, sizeof(int), 1, input) != 1
  || fread(atk, sizeof(int), 1, input) != 1
  || fread(def, sizeof(int), 1, input) != 1
  || fread(vit, sizeof(int), 1, input) != 1) {
    fprintf(stderr, "Erreur de lecture du personnage \"%s\".\n", *nom);
    free(*nom);
    *nom = NULL;
    return 0;
  }
  return 1;
}

int main(int argc, char * argv[]) {
  if(argc <= 1) {
  printf("Attendu :\n"
  "\t%s -create [FICHIER] [NOM] [VIE] [ATK] [DEF] [VIT]\n"
  "\t%s -read [FICHIER]\n", argv[0], argv[0]);
  exit(EXIT_FAILURE);
  }
  if(strcmp(argv[1], "-create") == 0 && argc > 7) {
    FILE * output = NULL;
    if((output = fopen(argv[2], "w+")) == NULL) {
      fprintf(stderr, "Erreur ouverture \"%s\"\n", argv[2]);
      exit(EXIT_FAILURE);
    }
    savePerso(output, argv[3], atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]));
    fclose(output);
  } else if(strcmp(argv[1], "-read") == 0 && argc > 2) {
    char * nom = NULL;
    int vie, atk, def, vit;
    FILE * input = NULL;
    if((input = fopen(argv[2], "r")) == NULL) {
      fprintf(stderr, "Erreur ouverture \"%s\"\n", argv[2]);
      exit(EXIT_FAILURE);
    }
    loadPerso(input, &nom, &vie, &atk, &def, &vit);
    printf("Personnage : {\n"
           "  Nom : %s\n"
           "  Vie : %d\n"
           "  Attaque : %d\n"
           "  Défense : %d\n"
           "  Vitesse : %d\n"
           "}\n", nom, vie, atk, def, vit);
    free(nom);
    nom = NULL;
    fclose(input);
  }
  exit(EXIT_SUCCESS);
}