#ifndef DEF_HEADER_AI
#define DEF_HEADER_AI

#include "Personnage.h"

/* Priorise d'attaquer l'adversaire. */
int AI_hit_prior(const Personnage * self, const Personnage * other);

/* Priorise de se booster avant de combattre. */
int AI_buff_prior(const Personnage * self, const Personnage * other);

#endif