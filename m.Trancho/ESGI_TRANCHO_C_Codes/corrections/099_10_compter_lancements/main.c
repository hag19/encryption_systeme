/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 99.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  /* Chemin du fichier où sauvegarder le nombre d'ouvertures. */
  const char * sauvegarde = "compteur.txt";
  /* Référence vers un fichier. */
  FILE * fich = NULL;
  /* Par défaut le nombre d'ouverture est 0. */
  int count = 0;
  /* Dans le cas où nous arrivons à ouvrir le fichier en       */
  /* lecture.                                                  */
  if((fich = fopen(sauvegarde, "r")) != NULL) {
    /* Nous récupérons la valeur inscrite pour mettre à jour   */
    /* le compteur d'ouvertures.                               */
    fscanf(fich, "%d", &count);
    /* Et nous fermons le fichier. */
    fclose(fich);
    fich = NULL;
  }
  /* Nous avons le nombre de fois où le fichier a été ouvert   */
  /* précédemment.                                             */
  /* Nous ouvrons cette fois le fichier en écriture pour       */
  /* mettre à jour son contenu.                                */
  if((fich = fopen(sauvegarde, "w+")) == NULL) {
    fprintf(stderr, "Erreur ouverture \"%s\"\n", sauvegarde);
    exit(EXIT_FAILURE);
  }
  /* Nous comptons un lancement de plus. */
  ++count;
  printf("Programme lancé %d fois\n", count);
  /* Nous inscrivons la valeur à jour dans le fichier. */
  fprintf(fich, "%d\n", count);
  fclose(fich);
  fich = NULL;
  exit(EXIT_SUCCESS);
}