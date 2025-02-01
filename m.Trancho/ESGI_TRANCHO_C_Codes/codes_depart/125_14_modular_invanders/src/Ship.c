#include "../include/Ship.h"

#include <stdlib.h>

Controler Controler_create() {
	Controler control;
	control.move_forward = 0;
	control.move_backward = 0;
	control.move_left = 0;
	control.move_right = 0;
	control.ship_action = 0;
	control.reload_action = 0;
	return control;
}

Ship * Ship_alloc(int team, Position position) {
	/* TODO */
	return NULL;
}

Ship * Ship_load(const char * path, int team, Position position) {
	/* TODO */
	return NULL;
}

int Ship_attack(Projectile * projectile, double range, Ship * ship) {
	/* TODO */
	return 0;
}

void Ship_apply_damages(double damages, Ship * ship) {
	/* TODO */
}