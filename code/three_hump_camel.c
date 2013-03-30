/*
 * three_hump_camel.c -- Three-hump camel function for testing. Minima is at f(0,0) = 0 for -5 <= x,y <= 5 
 *
 * (c) 2013 Roman Gassmann, HSR
 */
#include <optim.h>
#include <math.h>

static double  min[2] = { -5.0, -5.0 };
static double	max[2] = { 5.0, 5.0 };

static inline double	sqr(double x) {
	return x * x;
}

static double	three_hump_camel_function(optim_t *optim, double *x) {
	return ( 2*sqr(x[0]) - 1.05*pow( x[0] , 4 ) + pow( x[0] , 6 )/6 + x[0]*x[1] + sqr(x[1]) );
}

optim_t	three_hump_camel = {
	.n = 2,
	.min = min,
	.max = max,
	.f = three_hump_camel_function,
	.needs_deallocation = 0,
};
