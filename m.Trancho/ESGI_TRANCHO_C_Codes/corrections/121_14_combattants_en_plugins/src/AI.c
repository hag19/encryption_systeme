/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 121.
 */

#include "../include/AI.h"

int AI_hit_prior(const Personnage * self, const Personnage * other) {
  if(other->current.vie < 0.20 * other->start.vie) {
    return 0;
  }
  if(self->current.vie < 0.25 * self->start.vie) {
    return 1;
  }
  return 0;
}

int AI_buff_prior(const Personnage * self, const Personnage * other) {
  if(rand() % 5 == 0) {
    return rand() % 4;
  }
  if(self->current.vie < 0.25 * self->start.vie) {
    return 1;
  }
  if(self->current.def < 5. * self->start.def) {
    return 3;
  }
  if(self->current.atk < 5. * self->start.atk) {
    return 2;
  }
  return 0;
}