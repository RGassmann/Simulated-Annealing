/*
 * matyas.c -- Matyas function for testing. minima is at f(0,0) = 0 for -10 <= x,y <= 10 
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

static double	matyas_function(optim_t *optim, double *x) {
	return ( 0.26*( sqr(x[0]) + sqr(x[1]) ) - 0.48*x[0]*x[1] );
}

optim_t	matyas = {
	.n = 2,
	.min = min,
	.max = max,
	.f = matyas_function,
	.needs_deallocation = 0,
};
