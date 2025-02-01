#ifndef DEF_HEADER_ESGI_SPACE_CRAFT_POSITION
#define DEF_HEADER_ESGI_SPACE_CRAFT_POSITION

typedef struct Position Position;
struct Position {
	double x;
	double y;
};

Position Position_create(double x, double y);

double Position_distance(Position first, Position second);

#endif