#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#define ICON_SIZE 64
#define FILES_PER_ROW 5
#define PADDING 20

SDL_Surface *screen = NULL;
TTF_Font *font = NULL;
SDL_Surface *icon_folder, *icon_file;
char currentPath[256];

void initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
    if (!screen) {
        printf("SDL_SetVideoMode failed: %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption("File Explorer", NULL);
    if (TTF_Init() == -1) {
        printf("TTF_Init failed: %s\n", TTF_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    font = TTF_OpenFont("arial.ttf", 16);
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
    }
    icon_folder = IMG_Load("images/folder.png");
    icon_file = IMG_Load("images/file.png");
}

int isDirectory(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

void renderText(const char *text, int x, int y) {
    SDL_Color color = {0, 0, 0};
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, color);
    if (textSurface) {
        SDL_Rect pos = {x, y, 0, 0};
        SDL_BlitSurface(textSurface, NULL, screen, &pos);
        SDL_FreeSurface(textSurface);
    }
}

void drawFiles() {
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    struct dirent *entry;
    DIR *dp = opendir(currentPath);
    if (!dp) return;

    int x = PADDING, y = PADDING, count = 0;
    while ((entry = readdir(dp)) != NULL) {
        char fullPath[512];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", currentPath, entry->d_name);
        SDL_Surface *icon = isDirectory(fullPath) ? icon_folder : icon_file;
        SDL_Rect pos = {x, y, 0, 0};
        SDL_BlitSurface(icon, NULL, screen, &pos);
        renderText(entry->d_name, x, y + ICON_SIZE + 5);

        x += ICON_SIZE + PADDING;
        count++;
        if (x + ICON_SIZE > 800) {
            x = PADDING;
            y += ICON_SIZE + 40;
        }
    }
    closedir(dp);
    SDL_Flip(screen);
}

void handleClick(int x, int y) {
    struct dirent *entry;
    DIR *dp = opendir(currentPath);
    if (!dp) return;

    int itemX = PADDING, itemY = PADDING;
    int index = 0;
    while ((entry = readdir(dp)) != NULL) {
        char fullPath[512];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", currentPath, entry->d_name);
        SDL_Surface *icon = isDirectory(fullPath) ? icon_folder : icon_file;
        SDL_Rect pos = {itemX, itemY, ICON_SIZE, ICON_SIZE};

        if (x >= pos.x && x <= pos.x + ICON_SIZE && y >= pos.y && y <= pos.y + ICON_SIZE) {
            if (index == 0) { // Retour en arrière
                chdir("..");
            } else if (isDirectory(fullPath)) { // Ouvrir un dossier
                chdir(fullPath);
            }
            getcwd(currentPath, sizeof(currentPath));
            drawFiles();
            closedir(dp);
            return;
        }

        itemX += ICON_SIZE + PADDING;
        if (itemX + ICON_SIZE > 800) {
            itemX = PADDING;
            itemY += ICON_SIZE + 40;
        }
        index++;
    }
    closedir(dp);
}

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
