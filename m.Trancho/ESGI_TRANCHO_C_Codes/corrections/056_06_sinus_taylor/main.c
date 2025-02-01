/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 56.
 */

#include <stdio.h>
#include <stdlib.h>
#ifdef COMPARE
#include <math.h>
#endif
#include <time.h>

#define PI 3.14159265359
#define PIL 3.141592653589793l

double newton_sqrt(double target) {
	double x;
	x = target / 2.;
	int i;
	for(i = 0; i < 32; ++i) {
		x = (x * x + target) / (2 * x);
	}
	return x;
}

double taylor_sin_fast(double x) {
	int sign = 1;
	x -= PI * 2 * (int)(x / (PI * 2));
	if(x < 0) x += PI * 2;
	if(x > PI) x -= PI * 2;
	if(x < 0) {
		sign = -1;
		x *= -1;
	}
	if(x > PI / 2.) x = PI / 2. - (x - PI / 2.);
	double y = x * (1 + x * x * (-1. / 6. + x * x * (1. / 120. - x * x / 5040.)));
	return sign * y;
}

long double taylor_sin_precise(long double x) {
	int sign = 1;
	x -= PIL * 2 * (long)(x / (PIL * 2));
	if(x < 0) x += PIL * 2;
	if(x > PIL) x -= PIL * 2;
	if(x < 0) {
		sign = -1;
		x *= -1;
	}
	if(x > PIL / 2.) x = PIL / 2. - (x - PIL / 2.);
	long double y = x * (1 + x * x * (-1. / 6.l + x * x * (1. / 120.l + x * x * (-1. / 5040.l + x * x * (1. / 362880.l + x * x * (-1. / 39916800.l + x * x * (1. / 6227020800.l - x * x / 1307674368000.l)))))));
	return sign * y;
}

double taylor_sin_half(double x) {
	int sign = 1;
	x -= PI * 2 * (int)(x / (PI * 2));
	if(x < 0) x += PI * 2;
	if(x > PI) x -= PI * 2;
	if(x < 0) {
		sign = -1;
		x *= -1;
	}
	if(x > PI / 2.) x = PI / 2. - (x - PI / 2.);
	x -= PI / 4.;
	double y = 0.5 * newton_sqrt(2) * (1. + x * (1. + x * (-1. / 2. + x * (-1. / 6. + x * (1. / 24. + x * (1. / 120. + x * (-1. / 720. + x * (-1. / 5040. + x / 40320.))))))));
	return sign * y;
}

int main() {
	clock_t start, end;
	double x, y;
	long double ly;
	printf("Entrez un réel : ");
	scanf("%lf", &x);
	/*
	start = clock();
	y = taylor_sin_half(x);
	end = clock();
	printf("sin(%g) = %.16f (en %.6f s) (en 0.5)\n", x, y, (double)(end - start) / CLOCKS_PER_SEC);
	*/
	start = clock();
	y = taylor_sin_fast(x);
	end = clock();
	printf("sin(%g) = %.16f (en %.6f s) (rapide en 0)\n", x, y, (double)(end - start) / CLOCKS_PER_SEC);
#ifdef COMPARE
	start = clock();
	y = sin(x);
	end = clock();
	printf("sin(%g) = %.16f (en %.6f s) (d'après math)\n", x, y, (double)(end - start) / CLOCKS_PER_SEC);
#endif
	start = clock();
	ly = taylor_sin_precise(x);
	end = clock();
	printf("sinl(%g) = %.16Lf (en %.6f s) (développé en 0)\n", x, ly, (double)(end - start) / CLOCKS_PER_SEC);
#ifdef COMPARE
	start = clock();
	ly = sinl(x);
	end = clock();
	printf("sinl(%g) = %.16Lf (en %.6f s) (d'après math)\n", x, ly, (double)(end - start) / CLOCKS_PER_SEC);
#endif
	exit(EXIT_SUCCESS);
}