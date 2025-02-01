#include "../include/Stats.h"

Stats Stats_zero() {
	return (Stats){
		.forward_force = 0.,
		.backward_force = 0.,
		.right_force = 0.,
		.left_force = 0.,
		.mass = 0.,
		.health = 0.,
		.armor = 0.,
		.damage = 0.,
		.repair = 0.,
		.points = 0
	};
}

Stats Stats_base(double mass, double health, double armor, int points) {
	Stats stats = Stats_zero();
	stats.mass = mass;
	stats.health = health;
	stats.armor = armor;
	stats.points = points;
	return stats;
}