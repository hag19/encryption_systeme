#include <Ship.h>

Ship * Ship_instantiate(int team, Position position) {
	Ship * ship = Ship_alloc(
		team,
		position
	);
	List_add(&(ship->components), Component_load("extensions/Component_canon.so", Position_create(1., -2.75)));
	List_add(&(ship->components), Component_load("extensions/Component_canon.so", Position_create(-1., -2.75)));
	List_add(&(ship->components), Component_load("extensions/Component_canon.so", Position_create(2.5, -2.)));
	List_add(&(ship->components), Component_load("extensions/Component_canon.so", Position_create(-2.5, -2.)));
	List_add(&(ship->components), Component_load("extensions/Component_canon.so", Position_create(4., -1.)));
	List_add(&(ship->components), Component_load("extensions/Component_canon.so", Position_create(-4., -1.)));
	List_add(&(ship->components), Component_load("extensions/Component_canon.so", Position_create(0., -3.)));
	List_add(&(ship->components), Component_load("extensions/Component_backpulsor.so", Position_create(-1., 3.5)));
	List_add(&(ship->components), Component_load("extensions/Component_backpulsor.so", Position_create(1., 3.5)));
	List_add(&(ship->components), Component_load("extensions/Component_repair.so", Position_create(2., 1.)));
	List_add(&(ship->components), Component_load("extensions/Component_repair.so", Position_create(-2., 1.)));
	List_add(&(ship->components), Component_load("extensions/Component_direction.so", Position_create(4., 1.)));
	List_add(&(ship->components), Component_load("extensions/Component_direction.so", Position_create(-4., 1.)));
	List_add(&(ship->components), Component_load("extensions/Component_direction.so", Position_create(3., 3.)));
	List_add(&(ship->components), Component_load("extensions/Component_direction.so", Position_create(-3., 3.)));
	List_add(&(ship->components), Component_load("extensions/Component_brakes.so", Position_create(2., 0.)));
	List_add(&(ship->components), Component_load("extensions/Component_brakes.so", Position_create(-2., 0.)));
	List_add(&(ship->components), Component_load("extensions/Component_brakes.so", Position_create(1., -1.5)));
	List_add(&(ship->components), Component_load("extensions/Component_brakes.so", Position_create(-1., -1.5)));
	List_add(&(ship->components), Component_load("extensions/Component_direction.so", Position_create(0., 2.)));
	List_add(&(ship->components), Component_load("extensions/Component_cockpit.so", Position_create(0., 0.)));
	return ship;
}