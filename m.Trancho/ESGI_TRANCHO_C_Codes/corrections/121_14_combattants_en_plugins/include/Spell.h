/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 121.
 */

#ifndef DEF_HEADER_SPELL
#define DEF_HEADER_SPELL

#include "Personnage.h"

void Spell_coup_simple(Personnage * self, Personnage * other);

void Spell_se_soigner(Personnage * self, Personnage * other);

void Spell_boost_atk(Personnage * self, Personnage * other);

void Spell_boost_def(Personnage * self, Personnage * other);

#endif