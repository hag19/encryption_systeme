#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

// Window parameters
const int largeur = 800;
const int hauteur = 600;
const char *titre = "ESGI Delivery";

// Genetic algorithm constants
#define SELECT 10     // Number of top routes to select
#define GENERATE 1000 // Population size

// Structure to hold city coordinates
typedef struct {
    int x;
    int y;
} Point;

// Structure to hold a route
typedef struct {
    Point *points;   // Array of city points in the route
    double distance; // Total distance of the route
} Chemin;

// Function prototypes
void Entries_init(Chemin *population, int popSize, Point *userPoints, int size);
void Entries_update(Chemin *population, int popSize, int selectionSize, int size);
void mutate(Chemin *route, int size);
double totalDistance(Chemin *route, int size);
int compareDistances(const void *a, const void *b);
void crossover(Chemin *parent1, Chemin *parent2, Chemin *offspring, int size);
void affichage(SDL_Surface *ecran, Chemin *solution, int size);
int Points_load(const char *path, Point *points, int *size);
int Points_save(const char *path, Point *points, int size);
void addInput(Point *points, int x, int y, int *size);

// Main function
int main(int argc, char *argv[]) {
    srand(time(NULL)); // Seed for random operations
    
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error in SDL_Init: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Create a window and set video mode
    SDL_Surface *ecran = SDL_SetVideoMode(largeur, hauteur, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!ecran) {
        fprintf(stderr, "Error in SDL_SetVideoMode: %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption(titre, NULL); // Set window title

    // Load user points if provided
    Point userPoints[100];
    int size = 0;
    if (argc > 1) {
        Points_load(argv[1], userPoints, &size); // Load points from file
    }
    
    // Initialize population
    Chemin population[GENERATE];
    for (int i = 0; i < GENERATE; i++) {
        population[i].points = (Point *)malloc(size * sizeof(Point)); // Allocate memory for each route
    }
    
    int active = 1;
    int optimise = 0;
    SDL_Event event;
    clock_t start;
    
    while (active) {
        affichage(ecran, &population[0], size); // Display the current best route
        SDL_Flip(ecran); // Refresh screen

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: // Quit event
                    active = 0;
                    break;
                case SDL_KEYDOWN: // Key press event
                    if (event.key.keysym.sym == SDLK_ESCAPE) active = 0;
                    else if (event.key.keysym.sym == SDLK_SPACE && !optimise) {
                        Entries_init(population, GENERATE, userPoints, size); // Initialize population
                        start = clock();
                        optimise = 1;
                    }
                    break;
                case SDL_MOUSEBUTTONUP: // Mouse button event
                    if (event.button.button == SDL_BUTTON_LEFT && !optimise) {
                        addInput(userPoints, event.button.x, event.button.y, &size); // Add a new point
                    }
                    break;
            }
        }
        
        if (optimise) {
            Entries_update(population, GENERATE, SELECT, size); // Evolve the population
            SDL_Delay(1); // Small delay for each update
        } else {
            SDL_Delay(1000 / 60); // Refresh rate delay
        }
    }

    // Free resources and quit
    SDL_FreeSurface(ecran);
    SDL_Quit();
    for (int i = 0; i < GENERATE; i++) {
        free(population[i].points); // Free allocated memory
    }
    exit(EXIT_SUCCESS);
}

// Initialize population with user points
void Entries_init(Chemin *population, int popSize, Point *userPoints, int size) {
    for (int i = 0; i < popSize; i++) {
        for (int j = 0; j < size; j++) {
            population[i].points[j] = userPoints[j]; // Copy each point to each route
        }
        population[i].distance = totalDistance(&population[i], size); // Calculate distance
    }
}

// Update population using genetic algorithm
void Entries_update(Chemin *population, int popSize, int selectionSize, int size) {
    for (int i = selectionSize; i < popSize; i++) {
        mutate(&population[i], size); // Mutate routes
        population[i].distance = totalDistance(&population[i], size); // Update distance
    }

    qsort(population, popSize, sizeof(Chemin), compareDistances); // Sort by distance

    for (int i = selectionSize; i < popSize; i++) {
        crossover(&population[i % selectionSize], &population[(i + 1) % selectionSize], &population[i], size); // Crossover to create new routes
    }
}

// Mutate a route by swapping two points
void mutate(Chemin *route, int size) {
    int i = rand() % size;
    int j = rand() % size;
    Point temp = route->points[i];
    route->points[i] = route->points[j];
    route->points[j] = temp; // Swap
}

// Calculate total distance of a route
double totalDistance(Chemin *route, int size) {
    double dist = 0.0;
    for (int i = 0; i < size - 1; i++) {
        int dx = route->points[i+1].x - route->points[i].x;
        int dy = route->points[i+1].y - route->points[i].y;
        dist += sqrt(dx * dx + dy * dy); // Sum Euclidean distances
    }
    return dist;
}

// Perform crossover between two parent routes
void crossover(Chemin *parent1, Chemin *parent2, Chemin *offspring, int size) {
    int start = rand() % size;
    int end = rand() % size;
    if (start > end) { int temp = start; start = end; end = temp; }

    for (int i = start; i <= end; i++) {
        offspring->points[i] = parent1->points[i]; // Copy segment from parent1
    }

    int index = 0;
    for (int i = 0; i < size; i++) {
        Point city = parent2->points[i];
        int found = 0;
        for (int j = start; j <= end; j++) {
            if (city.x == offspring->points[j].x && city.y == offspring->points[j].y) {
                found = 1;
                break;
            }
        }
        if (!found) {
            if (index == start) index = end + 1;
            offspring->points[index++] = city; // Fill missing cities from parent2
        }
    }
}

// Compare distances for sorting
int compareDistances(const void *a, const void *b) {
    Chemin *routeA = (Chemin *)a;
    Chemin *routeB = (Chemin *)b;
    return (routeA->distance > routeB->distance) - (routeA->distance < routeB->distance);
}

// Display route on screen
void affichage(SDL_Surface *ecran, Chemin *solution, int size) {
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 51, 51, 102));
    // Additional code to draw the route could go here
}

// Load points from a file
int Points_load(const char *path, Point *points, int *size) {
    FILE *file = fopen(path, "r");
    if (!file) return -1;

    int x, y;
    *size = 0;
    while (fscanf(file, "%d %d", &x, &y) != EOF) {
        points[*size].x = x;
        points[*size].y = y;
        (*size)++;
    }

    fclose(file);
    return 0;
}

// Add a point from user input
void addInput(Point *points, int x, int y, int *size) {
    points[*size].x = x;
    points[*size].y = y;
    (*size)++;
}
