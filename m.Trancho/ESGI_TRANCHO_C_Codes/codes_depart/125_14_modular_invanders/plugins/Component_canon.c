#include <Component.h>
#include <Ship.h>
#include <Game.h>

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

void Projectile_draw(Projectile * projectile, SDL_Surface * ecran, int x, int y, int s, int t) {
	int offset = 1;
	if(t > 1) {
		offset = -1;
	}
	filledCircleRGBA(ecran, x, y, 2. * s, 255, 0, 0, 53);
	filledCircleRGBA(ecran, x, y, 0.25 * s, 255, 0, 0, 255);
	filledCircleRGBA(ecran, x, y + 0.5 * s * offset, 0.125 * s, 255, 255, 0, 255);
}

int Projectile_action(Projectile * projectile, Ship * ship, Game * game) {
	if(projectile->used || projectile->position.y < 0 || projectile->position.y > game->height) {
		projectile->used = 1;
		return 0;
	}
	int offset = 1;
	if(ship->team > 1) {
		offset = -1;
	}
	projectile->position.y -= offset * 10.;
	if(ship->team > 1) {
		if(Ship_attack(projectile, 1., game->player)) {
			Ship_apply_damages(200., game->player);
		}
	} else {
		void process(Ship * ship) {
			if(projectile->used) {
				return;
			}
			if(Ship_attack(projectile, 1., ship)) {
				Ship_apply_damages(200., ship);
			}
		};
		List_foreach(game->opponents, (void (*)(void *))process);
	}
	return 1;
}

Projectile * Projectile_instantiate(Position position) {
	Projectile * projectile = Projectile_alloc(position);
	projectile->action = Projectile_action;
	projectile->draw = Projectile_draw;
	return projectile;
}

void draw(Component * component, SDL_Surface * ecran, int x, int y, int s, int t) {
	int offset = 1;
	if(t > 1) {
		offset = -1;
	}
	filledCircleRGBA(ecran, x, y + offset * s, s, 204, 204, 204, 255);
	boxRGBA(ecran, x - 0.4 * s, y - s - 1.5 * offset * s, x + 0.4 * s, y + s - 1.5 * offset * s, 153, 153, 153, 255);
	boxRGBA(ecran, x - 0.6 * s, y - s, x + 0.6 * s, y + s, 204, 204, 204, 255);
	boxRGBA(ecran, x - 0.6 * s, y - 0.2 * s - 2.5 * offset * s, x + 0.6 * s, y + 0.2 * s - 2.5 * offset * s, 204, 204, 204, 255);
	filledCircleRGBA(ecran, x, y + offset * s, 0.8 * s, 153, 153, 153, 255);
	filledCircleRGBA(ecran, x, y + offset * s, 0.5 * s, 153, 51, 51, 255);
}

void action(Component * component, Ship * ship, Game * game) {
	int offset = 1;
	if(ship->team > 1) {
		offset = -1;
	}
	List_add(&(ship->projectiles), Projectile_instantiate(Position_create(
		ship->position.x + offset * SHIP_SCALE * component->position.x,
		ship->position.y + offset * SHIP_SCALE * component->position.y
	)));
}

Component * Component_instantiate(Position position) {
	Component * component = Component_alloc(
		CT_WEAPON, 
		Stats_base(50., 20., 10., -1),
		1, 3,
		position
	);
	component->stats.damage = 200.;
	component->draw = draw;
	component->action = action;
	return component;
}