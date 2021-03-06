/*
 * sa.h -- Simulated Annealing
 *
 * (c) 2013 Roman Gassmann, HSR
 */
#ifndef _sa_h
#define _sa_h

#include "optim.h"

typedef struct{
	double *x;
	double temp;
	}DesignPoint_t;

typedef struct{
	int iterations; 	/* Number of Iterations per Temp-Cycle */
	double vicinity;	/* The Vicinity a next design point might be in */
	double tempCoeff;	/* The Temperature Coefficient Typically between 0.4-0.9 */
	double temp;		/* Temperature */
	double stopTemp;
	DesignPoint_t	dP[2];	/* Design Point1 */
	optim_t *optim;	/* The Optimization Problem to solve*/
}Simulated_Annealing_Param_t;

extern void SimAnn(Simulated_Annealing_Param_t *param, const char *filename);

#endif /* _sa_h */
