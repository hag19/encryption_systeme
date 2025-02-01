#ifndef DEF_HEADER_ESGI_SPACE_CRAFT_STATS
#define DEF_HEADER_ESGI_SPACE_CRAFT_STATS

#include <stdio.h>

typedef struct Stats Stats;
struct Stats {
	double forward_force;
	double backward_force;
	double right_force;
	double left_force;
	double mass;
	double health;
	double armor;
	double damage;
	double repair;
	int points;
};

Stats Stats_zero();

Stats Stats_base(double mass, double health, double armor, int points);

#endif