/*
 * roman.c -- Roman's function for testing 
 *
 * (c) 2013 Roman Gassmann, HSR
 */
#include <optim.h>
#include <math.h>

static double  min[2] = { -2.5, -2.5 };
static double  max[2] = { 2.5, 2.5 };

static inline double	sqr(double x) {
	return x * x;
}

static double	roman_function(optim_t *optim, double *x) {
	return 10-(sqr(x[0])+2.5*sqr(x[1])-x[1])*exp(1-(sqr(x[0])+sqr(x[1])));
}

optim_t	roman = {
	.n = 2,
	.min = min,
	.max = max,
	.f = roman_function,
	.needs_deallocation = 0,
};
