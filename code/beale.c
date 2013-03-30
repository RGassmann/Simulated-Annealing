/*
 * beale.c -- Beale's function for testing. Minima is at f(3,0.5) = 0 for -4.5 <= x,y <= 4.5 
 *
 * (c) 2013 Roman Gassmann, HSR
 */
#include <optim.h>
#include <math.h>

static double  min[2] = { -4.5, -4.5 };
static double	max[2] = { 4.5, 4.5 };

static inline double	sqr(double x) {
	return x * x;
}

static double	beale_function(optim_t *optim, double *x) {
	return sqr( 1.5 - x[0] + x[0]*x[1] ) + sqr( 2.25 - x[0] + x[0]*sqr( x[1] ) ) + sqr( 2.625 - x[0] + x[0]*pow( x[1] , 3 ) ) ;
}

optim_t	beale = {
	.n = 2,
	.min = min,
	.max = max,
	.f = beale_function,
	.needs_deallocation = 0,
};
