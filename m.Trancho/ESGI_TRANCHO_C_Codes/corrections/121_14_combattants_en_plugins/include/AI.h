/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 121.
 */

#ifndef DEF_HEADER_AI
#define DEF_HEADER_AI

#include "Personnage.h"

int AI_hit_prior(const Personnage * self, const Personnage * other);

int AI_buff_prior(const Personnage * self, const Personnage * other);

#endif