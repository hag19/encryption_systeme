#include <Component.h>

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

void draw(Component * component, SDL_Surface * ecran, int x, int y, int s, int t) {
	boxRGBA(ecran, x - s, y - s, x + s, y + s, 204, 204, 204, 255);
	filledCircleRGBA(ecran, x, y, s, 153, 153, 153, 255);
	Sint16 startAngle = 180;
	int offset = 1;
	if(t > 1) {
		startAngle += 180;
		offset = -1;
	}
	filledPieRGBA(ecran, x - s * 0.2 * offset, y, s * 0.7, startAngle, startAngle + 60, 51, 204, 255, 255);
	filledPieRGBA(ecran, x, y, s * 0.8, startAngle + 60, startAngle + 120, 51, 204, 255, 255);
	filledPieRGBA(ecran, x + s * 0.2 * offset, y, s * 0.7, startAngle + 120, startAngle + 180, 51, 204, 255, 255);
}

Component * Component_instantiate(Position position) {
	Component * component = Component_alloc(
		CT_COCKPIT, 
		Stats_base(500., 500., 100., +20),
		1, 1,
		position
	);
	component->draw = draw;
	return component;
}