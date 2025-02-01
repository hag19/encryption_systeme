#include "../include/Position.h"

#include <math.h>

Position Position_create(double x, double y) {
	return (Position){
		.x = x,
		.y = y
	};
}

double Position_distance(Position first, Position second) {
	return sqrt((second.x - first.x) * (second.x - first.x) + (second.y - first.y) * (second.y - first.y));
}