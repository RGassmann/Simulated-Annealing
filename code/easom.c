/*
 * easom.c -- Easom function for testing. Minima is at f(Pi,Pi) = -1 for -100 <= x,y <= 100 
 *
 * (c) 2013 Roman Gassmann, HSR
 */
#include <optim.h>
#include <math.h>

#define EULER	2.718281828459045
#define PI	3.141592653589793

static double  min[2] = { -100, -100 };
static double	max[2] = { 100, 100 };

static inline double	sqr(double x) {
	return x * x;
}

static double	easom_function(optim_t *optim, double *x) {
	return - cos( x[0] )*cos( x[1] )*pow( EULER , -( sqr( x[0] - PI ) + sqr( x[1] - PI ) ) );
}

optim_t	easom = {
	.n = 2,
	.min = min,
	.max = max,
	.f = easom_function,
	.needs_deallocation = 0,
};
