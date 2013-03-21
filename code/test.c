/*
 * test.c -- auxiliary program to test optimization function framework
 *
 * (c) 2013 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <optim.h>
#include <sa.h>

int	main(int argc, char *argv[]) {
	int	c;
	char	*libraryname = NULL;
	char	*symbolname = NULL;
	char	*filename = NULL;

	/* parse command line */
	while (EOF != (c = getopt(argc, argv, "l:s:o:")))
		switch (c) {
		case 'l':
			libraryname = optarg;
			break;
		case 's':
			symbolname = optarg;
			break;
		case 'o':
			filename = optarg;
			break;
		}

	/* verify that we have library and symbol name */
	if (NULL == libraryname) {
		fprintf(stderr, "no library specified, use -l flag\n");
		exit(EXIT_FAILURE);
	}
	if (NULL == symbolname) {
		fprintf(stderr, "no symbol name specified, use -s flag\n");
		exit(EXIT_FAILURE);
	}
	if (NULL == filename) {
		fprintf(stderr, "no file name specified, use -o flag\n");
		exit(EXIT_FAILURE);
	}
	/* open the library */
	optim_t	*o = optim_open(libraryname, symbolname);
	if (NULL == o) {
		fprintf(stderr, "cannot get symbol %s in library %s\n",
			symbolname, libraryname);
		exit(EXIT_FAILURE);
	}
	printf("opened library %s, symbol %s @ %p\n", libraryname,
		symbolname, o);


	/* make Simulated Annealing */

	Simulated_Annealing_Param_t sap;
	printf("Bitte anzahl Iterationen [ca. 50-100] angeben:\n");
	scanf("%d",&sap.iterations);
	//sap.iterations = 50;
	printf("Bitte Nähere Umgebung [z.B. 6.0] angeben:\n");
	scanf("%lf",&sap.vicinity);
	//sap.vicinity = 0.25;
	printf("Bitte Temperaturkoeffizient [ca. 0.6-0.9] angeben:\n");
	scanf("%lf",&sap.tempCoeff);
	//sap.tempCoeff = 0.9;
	printf("Bitte End-Temperatur [z.B. 0.5] angeben:\n");
	scanf("%lf",&sap.stopTemp);
	sap.temp = 0;
	sap.optim = o;
	
	SimAnn(&sap, filename);

	/* that's it */
	exit(EXIT_SUCCESS);
}
