/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 88.
 */

#ifndef DEF_HEADER_PROFILE
#define DEF_HEADER_PROFILE

#include <stdio.h>

#define log(...) fprintf(stderr, __VA_ARGS__);

#ifdef DO_PROFILE

#define exit(V) log("> Exit in function %s at line %d with value %s\n", __FUNCTION__, __LINE__, #V); exit(V);
#define START_FUNCTION(type, name, ...) type name(__VA_ARGS__) { \
	log("# Definition of %s function %s(%s) in file \"%s\" at line %d\n", #type, #name, #__VA_ARGS__, __FILE__,__LINE__); \
	log("< Starting function %s :\n", __FUNCTION__);
#define END_FUNCTION(V) log("> Ending function %s with return %s\n", __FUNCTION__, #V); return V; }

#else

#define START_FUNCTION(type, name, ...) type name(__VA_ARGS__) {
#define END_FUNCTION(V) return V; }

#endif

#endif