/*
gcc main.c graphic.c -o file_manager.exe -I/mingw64/include/SDL -Dmain=SDL_main -L/mingw64/lib -lmingw32 -lSDLmain -lSDL -lSDL_ttf -lSDL_image -mwindows -mconsole
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "graphic.h"

int main(int argc, char *argv[]) {
    getcwd(currentPath, sizeof(currentPath));
    initSDL();
    drawFiles();
    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                handleClick(event.button.x, event.button.y);
            }
        }
        SDL_Delay(100);
    }
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
