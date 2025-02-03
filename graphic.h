#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

extern SDL_Surface *screen;
extern TTF_Font *font;
extern char currentPath[256];

void initSDL();
int isDirectory(const char *path);
void renderText(const char *text, int x, int y);
void drawFiles();
void handleClick(int x, int y);

#endif // GRAPHIC_H
