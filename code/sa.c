#include "sa.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#if defined(_POSIX_TIMERS) && _POSIX_TIMERS > 0
#include<time.h>
#else
#include<sys/time.h>
#endif

#define MIN(x,y)  ((x<y) ? x : y)
#define MAX(x,y)  ((x>y) ? x : y)

typedef enum { false, true } bool;


int gen_rand(void)
/* returns random number in range of 0 to 999999 */
{
 struct timespec ts;
/*#if defined(_POSIX_TIMERS) && _POSIX_TIMERS > 0
clock_gettime(CLOCK_REALTIME, &ts);
#else*/
struct timeval tv;
gettimeofday(&tv, NULL);
ts.tv_sec = tv.tv_sec;
ts.tv_nsec = tv.tv_usec * 1000;
//#endif
	srandom(ts.tv_nsec);	
   return(random()%1000000);
}

void fillRandom(int n /*dimension*/, double *min, double *max, double *x){
	int i =0;
	for(i=0; i < n /*dimension*/;i++){
		x[i] =min[i] + (( max[i] - min[i] ) * ((double)gen_rand())/1000000.00); /* generating a random point in the domain */ 
	}
}

double generateInitialTemp(int amount, Simulated_Annealing_Param_t *param){
	int i =0;
	double *x;
	double temp;
	double temptemp;
	printf("Generated Temp\n"); 
	for(i =0; i< amount; i++){
		x = (double*) calloc( param->optim->n , sizeof(double));
		fillRandom( param->optim->n , param->optim->min , param->optim->max , x );
		temptemp = param->optim->f(param->optim,x);
		printf("Generated: %lf\n",temptemp);
		temp += temptemp;
		free(x);
	}
	temp/=amount;
	return temp;
}

double limit(double min, double max , double val){
	return MAX(min,MIN(max,val));
}


void SimAnn(Simulated_Annealing_Param_t *param, const char *filename){

	bool pingpong = 0;
	int i =0;
	int j =0;
	double delta =0;
	FILE *file;
	file = fopen(filename,"a+");
	if(file == NULL){
		fprintf(stderr, "Could not open File!\n");
		exit(EXIT_FAILURE);
	}

	for(j=0; j < param->optim->n;j++){
		printf("limit[%d]: %lf  --  %lf\n",j,param->optim->min[j] ,param->optim->max[j] );
	}

	if(param->temp == 0) param->temp = generateInitialTemp(10, param);	

	enum{SAinit, SAnewDPoint, SAMetropolisCrit, SAReduceTemp, SAStop}state;

	state = SAinit;
	
	
	while(state != SAStop)
	{
		switch(state){
			case SAinit:
				param->dP[pingpong].x = (double *) calloc(param->optim->n, sizeof(double));
				param->dP[!pingpong].x = (double *) calloc(param->optim->n, sizeof(double));
				if(param->dP[pingpong].x == NULL){
					state = SAStop;
					printf("Error: Could not allocate Memory!");
					break;
				}
				
				fillRandom( param->optim->n , param->optim->min , param->optim->max , param->dP[pingpong].x );
				param->dP[pingpong].temp = param->optim->f( param->optim , param->dP[pingpong].x );

				printf("Starttemperatur = %lf\n", param->temp);
				state = SAnewDPoint;
				i=1;
				pingpong = 1;
			break;
			case SAnewDPoint:
				
				for(j=0; j < param->optim->n;j++){
					param->dP[pingpong].x[j] = limit(param->optim->min[j], param->optim->max[j], 										param->dP[!pingpong].x[j]+(((double)gen_rand())/1000000.00*2.0*param->vicinity)-param->vicinity );

					if(param->dP[pingpong].x[j] > param->optim->max[j]) printf("Heep %lf\n", param->dP[pingpong].x[j]);

				}
				param->dP[pingpong].temp = param->optim->f(param->optim,param->dP[pingpong].x);

				delta = param->dP[pingpong].temp - param->dP[!pingpong].temp;
				
				
				if(delta > 0){ /* higher temp then before */
					if(pow(2.71828182845,-delta/param->temp) < ((double)gen_rand())/1000000.00)
						break;		
				}

				for (j=0;j<param->optim->n;j++) fprintf (file, "%lf, ",param->dP[pingpong].x[j]);

				fprintf(file,"%lf \n",param->dP[pingpong].temp);
				//printf("%lf %lf %lf\n", designPoints[index-1].x, designPoints[index-1].y, designPoints[index-1].res);
				pingpong =!pingpong; 
				i++;
				if( i > param->iterations ) state = SAReduceTemp;
			break;
			case SAReduceTemp:
				param->temp *= param->tempCoeff;
				if(param->temp < param->stopTemp){
					printf("Stoptemperatur = %lf\n",param->temp);
					state = SAStop;
					break;
				}
				i=1;
				state = SAnewDPoint;
			break;

			default:
			break;
		}
		

	}
	fclose(file);
	free(param->dP[pingpong].x);
	free(param->dP[!pingpong].x);
}



