#include <Component.h>

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

void draw(Component * component, SDL_Surface * ecran, int x, int y, int s, int t) {
	int offset = 1;
	if(t > 1) {
		offset = -1;
	}
	boxRGBA(ecran, x - s, y - s, x + s, y + s, 204, 204, 204, 255);
	filledCircleRGBA(ecran, x, y, 0.75 * s, 153, 153, 153, 255);
	filledCircleRGBA(ecran, x, y, 0.5 * s, 204, 204, 204, 255);
	boxRGBA(ecran, x - 1.1 * s, y - 0.1 * s - 1. * offset * s, x + 1.1 * s, y + 0.1 * s - 1. * offset * s, 153, 153, 153, 255);
}

Component * Component_instantiate(Position position) {
	Component * component = Component_alloc(
		CT_PULSOR, 
		Stats_base(50., 20., 10., -1),
		1, 1,
		position
	);
	component->stats.forward_force = 10.;
	component->stats.backward_force = 50.;
	component->stats.left_force = 10.;
	component->stats.right_force = 10.;
	component->draw = draw;
	return component;
}