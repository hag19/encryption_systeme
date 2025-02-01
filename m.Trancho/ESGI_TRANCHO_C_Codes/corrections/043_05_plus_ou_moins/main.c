/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 43.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  /* srand permet d'initialiser le générateur pseudo aléatoire */
  /* à une graine donnée. */
  /* Pour avoir un aléatoire variant d'une exécution à         */
  /* l'autre, nous l'initilisons par le nombre de secondes     */
  /* écoulées depuis le 1er Janvier 1970.                      */
  srand(time(NULL));
  
  const int max = 1000;
  /* rand renvoie une valeur aléatoire sur un int.             */
  /* En effectuant un modulo, nous récupérons une valeur       */
  /* aléatoire tronquée de celle-ci vivant entre 0 et max :    */
  int nombre = rand() % (max + 1);
  
  int user;
  
  printf("Nous avons choisi un nombre entre 0 et %d\n", max);
  do {
    /* Nous récupérons la saisie de l'utilisateur : */
    printf("A quel nombre pensez-vous ? ");
    scanf("%d", &user);
    
    /* Nous lui indiquons le positionnement de son nombre par  */
    /* rapport au nombre caché :                               */
    if(user < nombre) {
      printf("Trop petit.\n");
    } else if(user > nombre) {
      printf("Trop grand.\n");
    }
    /* Nous continuerons tant que le nombre de l'utilisateur   */
    /* n'est pas le même que le nombre caché.                  */
  } while (user != nombre);
  
  printf("Bien joué, le nombre était en effet %d\n", nombre);
  
  exit(EXIT_SUCCESS);
}