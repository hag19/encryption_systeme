/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 35.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  const int finT1 = 10084;
  const int finT2 = 25710;
  const int finT3 = 73516;
  const int finT4 = 158122;
  const float tauxT1 = 0.00;
  const float tauxT2 = 0.11;
  const float tauxT3 = 0.30;
  const float tauxT4 = 0.41;
  const float tauxT5 = 0.45;
  
  unsigned char couple = 0;
  unsigned int enfants = 0;
  float parts = 0;
  unsigned long revenusFoyer = 0;
  unsigned long revenusConjoint = 0;
  unsigned long quotientFamillial = 0;
  unsigned long impot = 0;
  
  printf("Quels sont vos revenus annuels nets personnels ?\n");
  scanf("%lu", &revenusFoyer);
  printf("Êtes-vous marié ou pacsé ? (Y ou n)\n");
  scanf(" %c", &couple);
  couple = (couple == 'Y' || couple == 'y' || couple == 'O' || couple == 'o');
  if(couple) {
    printf("Quels sont les revenus annuels nets de votre conjoint ?\n");
    scanf("%lu", &revenusConjoint);
    revenusFoyer += revenusConjoint;
  }
  printf("Combien avez-vous d'enfants ?\n");
  scanf("%u", &enfants);
  parts = 1 + 0.5 * enfants;
  if(couple) {
    parts += 1;
  } else if(enfants > 0) {
    parts += 0.5;
  }
  quotientFamillial = revenusFoyer / parts;
  
  if(quotientFamillial < finT1) {
    impot = quotientFamillial * tauxT1;
  } else {
    impot = finT1 * tauxT1;
    if(quotientFamillial < finT2) {
      impot += (quotientFamillial - finT1) * tauxT2;
    } else {
      impot += (finT2 - finT1) * tauxT2;
      if(quotientFamillial < finT3) {
        impot += (quotientFamillial - finT2) * tauxT3;
      } else {
        impot += (finT3 - finT2) * tauxT3;
        if(quotientFamillial < finT4) {
          impot += (quotientFamillial - finT3) * tauxT4;
        } else {
          impot += (finT4 - finT3) * tauxT4;
          impot += (quotientFamillial - finT4) * tauxT5;
        }
      }
    }
  }
  
  printf("Ceci vous fait donc un impôt de %lu x %g = %lu €\n", impot, parts, (unsigned long)(impot * parts));
  
  exit(EXIT_SUCCESS);
}