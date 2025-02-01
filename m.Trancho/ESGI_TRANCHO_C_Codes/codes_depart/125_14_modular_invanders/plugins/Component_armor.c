#include <Component.h>

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

void draw(Component * component, SDL_Surface * ecran, int x, int y, int s, int t) {
	boxRGBA(ecran, x - s, y - s, x + s, y + s, 204, 204, 204, 255);
	boxRGBA(ecran, x - 0.9 * s, y - 0.9 * s, x + 0.9 * s, y + 0.9 * s, 153, 153, 153, 255);
}

Component * Component_instantiate(Position position) {
	Component * component = Component_alloc(
		CT_ARMOR, 
		Stats_base(500., 200., 200., -1),
		1, 1,
		position
	);
	component->draw = draw;
	return component;
}