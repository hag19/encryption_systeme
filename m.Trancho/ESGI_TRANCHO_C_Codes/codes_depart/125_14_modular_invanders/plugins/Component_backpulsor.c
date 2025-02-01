#include <Component.h>

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

void draw(Component * component, SDL_Surface * ecran, int x, int y, int s, int t) {
	int offset = 1;
	if(t > 1) {
		offset = -1;
	}
	filledCircleRGBA(ecran, x, y - offset * s, s, 204, 204, 204, 255);
	boxRGBA(ecran, x - 0.75 * s, y - s + 0.5 * offset * s, x + 0.75 * s, y + s + 0.5 * offset * s, 153, 153, 153, 255);
	boxRGBA(ecran, x - s, y - s, x + s, y + s, 204, 204, 204, 255);
}

Component * Component_instantiate(Position position) {
	Component * component = Component_alloc(
		CT_PULSOR, 
		Stats_base(10., 10., 0., -1),
		1, 2,
		position
	);
	component->stats.forward_force = 200.;
	component->draw = draw;
	return component;
}