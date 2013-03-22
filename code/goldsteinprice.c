/*
 * goldsteinprice.c -- rosenbrock function for testing minima is at f(0,-1) = 0 for -2 <= x,y <= 2 
 *
 * (c) 2013 Roman Gassmann, HSR
 */
#include <optim.h>
#include <math.h>

static double  min[2] = { -2.0, -2.0 };
static double	max[2] = { 2.0, 2.0 };

static inline double	sqr(double x) {
	return x * x;
}

static double	goldsteinprice_function(optim_t *optim, double *x) {
	return ( 1 + sqr( x[0]+x[1]+1 ) * ( 19 - 14*x[0] + 3*sqr(x[0]) - 14*x[1] + 6*x[0]*x[1] + 3*sqr(x[1]) ) ) *
		( 30 + sqr( 2*x[0] - 3*x[1] )*( 18 - 32*x[0] + 12*sqr(x[0]) + 48x[1] - 36*x[0]*x[1]+ 27*sqr(x[1]) ) );
}

optim_t	prob3 = {
	.n = 2,
	.min = min,
	.max = max,
	.f = goldsteinprice_function,
	.needs_deallocation = 0,
};
