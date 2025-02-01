/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 91.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  const char * infos = "Linus Torvalds 52 ans C";
  /* Nous devons ici extraire les informations d'une chaîne de */
  /* caractères non modifiable telle que donnée précédemment   */
  /* par 'infos'.                                              */
  /* Nous préparons les variables dans lesquelles sauvegarder  */
  /* les informations récupérées.                              */
  char prenom[50];  /* Pour le prénom :  mot 1                 */
  char nom[50];     /* Pour le nom :     mot 2                 */
  int age;          /* Pour l'age :      entier 3              */
  char langage[50]; /* Pour le langage : mot 5                 */
  /* sscanf prend en paramètres :                              */
  /* - la chaîne de caractère depuis laquelle lire les         */
  /*   informations.                                           */
  /* - la chaîne formatée indiquant le type d'élément à lire.  */
  /* - les adresses dans lesquelles affecter les résultats.    */
  /* note : un tableau est l'adresse de son premier élément et */
  /* une chaîne de caractère lisible par %s est donc une       */
  /* adresse                                                   */
  sscanf(infos, "%s %s %d ans %s", prenom, nom, &age, langage);
  printf("Prenom : %s\nNom : %s\nAge : %d\nParle couramment la langue %s\n", prenom, nom, age, langage);
  exit(EXIT_SUCCESS);
}