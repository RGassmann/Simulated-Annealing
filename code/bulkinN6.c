/*
 * bulkinN6.c -- Bulkin function N.6 for testing. Minima is at f(-10,1) = 0 for -15 <= x <= -5 , -3 <= y <= 3
 *
 * (c) 2013 Roman Gassmann, HSR
 */
#include <optim.h>
#include <math.h>

static double  min[2] = { -15, -3 };
static double	max[2] = { -5, 3 };

static inline double	sqr(double x) {
	return x * x;
}

static double	bulkinN6_function(optim_t *optim, double *x) {
	return 100*sqrt( abs( x[1] - 0.01 * sqr( x[0] ) ) ) + 0.01 * abs( x[0] + 10 );
}

optim_t	bulkinN6 = {
	.n = 2,
	.min = min,
	.max = max,
	.f = bulkinN6_function,
	.needs_deallocation = 0,
};
