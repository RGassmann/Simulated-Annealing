/*
 * prob3.c -- mock function for testing
 *
 * (c) 2013 Roman Gassmann, HSR
 */
#include <optim.h>
#include <math.h>

static double	min[2] = { -50.0, -50.0 };
static double	max[2] = { 50.0, 50.0 };

static inline double	sqr(double x) {
	return x * x;
}

static double	prob3_function(optim_t *optim, double *x) {
	return 500 - 20*x[0] - 26*x[1] -4*x[0]*x[1] +4*sqr(x[0]) + 3*sqr(x[1]);
}

optim_t	prob3 = {
	.n = 2,
	.min = min,
	.max = max,
	.f = prob3_function,
	.needs_deallocation = 0,
};
