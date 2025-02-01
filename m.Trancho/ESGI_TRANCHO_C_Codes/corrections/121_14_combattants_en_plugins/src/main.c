/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 121.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/Personnage.h"
#include "../include/Spell.h"
#include "../include/AI.h"

int main(int argc, char * argv[]) {
  
  srand(time(NULL));
  
  Personnage garde = Personnage_defensive_soldier();
  Personnage_init(&garde);
  printf("%s entre dans l'arène.\n", Personnage_nom(&garde));
  Personnage_display(&garde);
  
  int i;
  int tour = 0;
  for(i = 1; i < argc; ++i) {
  
    Personnage adv = Personnage_charger(argv[i]);
    Personnage_init(&adv);
    printf("%s entre dans l'arène.\n", Personnage_nom(&adv));
    Personnage_display(&adv);
    
    for(; Personnage_est_vivant(&garde) && Personnage_est_vivant(&adv); ++tour) {
      printf(">>> TOUR %d :\n", tour);
      if(Personnage_est_plus_rapide(&garde, &adv)) {
        Personnage_action(&garde, &adv);
        Personnage_action(&adv, &garde);
      } else {
        Personnage_action(&adv, &garde);
        Personnage_action(&garde, &adv);
      }
      Personnage_display(&garde);
      Personnage_display(&adv);
    }
    if(! Personnage_est_vivant(&adv)) {
      printf("%s est vaincu.\n", Personnage_nom(&adv));
    }
    Personnage_quit(&adv);
  }
  if(Personnage_est_vivant(&garde)) {
    printf("%s a survécu !\n", Personnage_nom(&garde));
  } else {
    printf("%s est vaincu !\n", Personnage_nom(&garde));
  }
  Personnage_quit(&garde);
  exit(EXIT_SUCCESS);
}