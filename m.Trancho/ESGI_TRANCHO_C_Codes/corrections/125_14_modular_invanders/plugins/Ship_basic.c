/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 125.
 */

#include <Ship.h>

Ship * Ship_instantiate(int team, Position position) {
	Ship * ship = Ship_alloc(
		team,
		position
	);
	List_add(&(ship->components), Component_load("extensions/Component_canon.so", Position_create(1.5, -1.5)));
	List_add(&(ship->components), Component_load("extensions/Component_canon.so", Position_create(-1.5, -1.5)));
	List_add(&(ship->components), Component_load("extensions/Component_backpulsor.so", Position_create(-1., 2.5)));
	List_add(&(ship->components), Component_load("extensions/Component_backpulsor.so", Position_create(1., 2.5)));
	List_add(&(ship->components), Component_load("extensions/Component_repair.so", Position_create(2., 1.)));
	List_add(&(ship->components), Component_load("extensions/Component_repair.so", Position_create(-2., 1.)));
	List_add(&(ship->components), Component_load("extensions/Component_direction.so", Position_create(4., 1.)));
	List_add(&(ship->components), Component_load("extensions/Component_direction.so", Position_create(-4., 1.)));
	List_add(&(ship->components), Component_load("extensions/Component_brakes.so", Position_create(3., 0.)));
	List_add(&(ship->components), Component_load("extensions/Component_brakes.so", Position_create(-3., 0.)));
	List_add(&(ship->components), Component_load("extensions/Component_armor.so", Position_create(0., -1.5)));
	List_add(&(ship->components), Component_load("extensions/Component_armor.so", Position_create(2., -1.5)));
	List_add(&(ship->components), Component_load("extensions/Component_armor.so", Position_create(-2., -1.5)));
	List_add(&(ship->components), Component_load("extensions/Component_cockpit.so", Position_create(0., 0.)));
	return ship;
}