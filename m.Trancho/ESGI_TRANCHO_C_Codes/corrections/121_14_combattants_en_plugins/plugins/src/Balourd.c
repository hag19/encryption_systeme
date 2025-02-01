/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 121.
 */

#include "../../include/Personnage.h"
#include "../../include/Spell.h"
#include "../../include/AI.h"

#ifdef _WIN32 /* Windows does not allow dynamic symbols export from executable, thus this horrible .c includes */
/* (C'est une mauvaise pratique, mais Windows ne laisse pas le choix, à ne pas reproduire s'il est possible de l'éviter)*/
#include "../../src/Personnage.c"
#include "../../src/Spell.c"
#include "../../src/AI.c"
#endif

#include <math.h>

void Spell_coup_lourd(Personnage * self, Personnage * other) {
  int deg = pow((float)(self->current.atk) / other->current.def, 2.f);
  if(deg <= 0) {
    deg = 1;
  }
  other->current.vie -= deg;
  printf("%s frappe %s et lui inflige %d dégats.\n", self->nom, other->nom, deg);
  Personnage_keep_in_bounds(other);
}

int AI_bouriner(const Personnage * self, const Personnage * other) {
  if(rand() % 3 == 0) {
    return 2;
  }
  if(other->current.vie < 0.20 * other->start.vie) {
    return 0;
  }
  if(self->current.vie < 0.50 * self->start.vie) {
    return 1;
  }
  return 0;
}

Personnage Personnage_instantiate() {
  return (Personnage) {
    .nom = "Balourd",
    .start = (Stats) {
      .vie = 120,
      .atk = 100,
      .def = 150,
      .vit = 6
    },
    .coups = {
      &Spell_coup_lourd,
      &Spell_se_soigner,
      &Spell_boost_atk,
      &Spell_boost_def
    },
    .choix = &AI_bouriner
  };
}