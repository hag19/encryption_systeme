/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 125.
 */

#include "../include/Projectile.h"

#include <stdlib.h>
#include <assert.h>

static int LastProjectileId = 0;

Projectile * Projectile_alloc(Position position) {
  Projectile * projectile = NULL;
  assert(projectile = (Projectile *)malloc(sizeof(Projectile)));
  projectile->position = position;
  projectile->projectileId = ++LastProjectileId;
  projectile->used = 0;
  projectile->action = NULL;
  projectile->draw = NULL;
  projectile->userData = NULL;
  return projectile;
}

void Projectile_free(Projectile * projectile) {
  if(projectile == NULL) {
    return;
  }
  free(projectile->userData);
  free(projectile);
}