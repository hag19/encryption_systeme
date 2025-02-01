/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 121.
 */

#include "../include/Spell.h"

void Spell_coup_simple(Personnage * self, Personnage * other) {
  int deg = self->current.atk / other->current.def;
  if(deg <= 0) {
    deg = 1;
  }
  other->current.vie -= deg;
  printf("%s frappe %s et lui inflige %d dégats.\n", self->nom, other->nom, deg);
  Personnage_keep_in_bounds(other);
}

void Spell_se_soigner(Personnage * self, Personnage * other) {
  self->current.vie *= 1.10;
  printf("%s se soigne.\n", self->nom);
  Personnage_keep_in_bounds(self);
}

void Spell_boost_atk(Personnage * self, Personnage * other) {
  self->current.atk *= 1.20;
  printf("%s aiguise sa lame.\n", self->nom);
  Personnage_keep_in_bounds(self);
}

void Spell_boost_def(Personnage * self, Personnage * other) {
  self->current.def *= 1.30;
  printf("%s se renforce.\n", self->nom);
  Personnage_keep_in_bounds(self);
}