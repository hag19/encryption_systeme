#include <Component.h>

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

void draw(Component * component, SDL_Surface * ecran, int x, int y, int s, int t) {
	boxRGBA(ecran, x - s, y - s, x + s, y + s, 204, 204, 204, 255);
	boxRGBA(ecran, x - 0.8 * s, y - 0.4 * s, x + 0.8 * s, y + 0.4 * s, 153, 153, 153, 255);
	boxRGBA(ecran, x - 0.4 * s, y - 0.8 * s, x + 0.4 * s, y + 0.8 * s, 153, 153, 153, 255);
	boxRGBA(ecran, x - 0.6 * s, y - 0.2 * s, x + 0.6 * s, y + 0.2 * s, 51, 153, 51, 255);
	boxRGBA(ecran, x - 0.2 * s, y - 0.6 * s, x + 0.2 * s, y + 0.6 * s, 51, 153, 51, 255);
}

Component * Component_instantiate(Position position) {
	Component * component = Component_alloc(
		CT_UTILITY, 
		Stats_base(200., 100., 10., -1),
		1, 1,
		position
	);
	component->stats.repair = 100.;
	component->draw = draw;
	return component;
}