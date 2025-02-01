/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 125.
 */

#include "../include/Component.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <dlfcn.h>

static int LastComponentId = 0;

Component * Component_alloc(ComponentType type, Stats stats, 
  int width, int height, Position position) {
  
  Component * component = NULL;
  assert(component = (Component *)malloc(sizeof(Component)));
  component->type = type;
  component->stats = stats;
  component->width = width;
  component->height = height;
  component->componentId = ++LastComponentId;
  component->position = position;
  component->action = NULL;
  component->draw = NULL;
  component->userData = NULL;
  component->dlptr = NULL;
  return component;
}

void Component_free(Component * component) {
  if(component == NULL) {
    return;
  }
  if(component->dlptr) {
    dlclose(component->dlptr);
  }
  free(component->userData);
  free(component);
}

Component * Component_load(const char * path, Position position) {
  void * dlptr = NULL;
  if((dlptr = dlopen(path, RTLD_NOW)) == NULL) {
    fprintf(stderr, "Erreur d'ouverture du composant \"%s\"\n%s\n", path, dlerror());
    exit(EXIT_FAILURE);
  }
  Component * (*instantiate)(Position) = NULL;
  if((instantiate = (Component * (*)(Position))dlsym(dlptr, "Component_instantiate")) == NULL) {
    fprintf(stderr, "Erreur de chargement du composant \"%s\"\n%s\n", path, dlerror());
    exit(EXIT_FAILURE);
  }
  Component * component = (*instantiate)(position);
  component->dlptr = dlptr;
  return component;
}