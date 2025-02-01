/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 125.
 */

#include <Component.h>

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

void draw(Component * component, SDL_Surface * ecran, int x, int y, int s, int t) {
	boxRGBA(ecran, x - s, y - s, x + s, y + s, 204, 204, 204, 255);
	filledCircleRGBA(ecran, x, y, 0.75 * s, 153, 153, 153, 255);
	filledCircleRGBA(ecran, x, y, 0.6 * s, 204, 204, 204, 255);
	boxRGBA(ecran, x - 0.7 * s, y - 0.2 * s, x + 0.7 * s, y + 0.2 * s, 153, 153, 153, 255);
}

Component * Component_instantiate(Position position) {
	Component * component = Component_alloc(
		CT_PULSOR, 
		Stats_base(10., 10., 10., -1),
		1, 1,
		position
	);
	component->stats.forward_force = 10.;
	component->stats.backward_force = 10.;
	component->stats.left_force = 100.;
	component->stats.right_force = 100.;
	component->draw = draw;
	return component;
}