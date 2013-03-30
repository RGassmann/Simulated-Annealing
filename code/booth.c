/*
 * booth.c -- Booth's function for testing minima is at f(1,3) = 0 for -10 <= x,y <= 10 
 *
 * (c) 2013 Roman Gassmann, HSR
 */
#include <optim.h>
#include <math.h>

static double  min[2] = { -10.0, -10.0 };
static double	max[2] = { 10.0, 10.0 };

static inline double	sqr(double x) {
	return x * x;
}

static double	booth_function(optim_t *optim, double *x) {
	return ( sqr( x[0] + 2*x[1] - 7 ) + sqr( 2*x[0] + x[1] - 5 ) );
}

optim_t	booth = {
	.n = 2,
	.min = min,
	.max = max,
	.f = booth_function,
	.needs_deallocation = 0,
};
