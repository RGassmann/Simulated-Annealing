#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#if defined(_POSIX_TIMERS) && _POSIX_TIMERS > 0
#include<time.h>
#else
#include<sys/time.h>
#endif


int gen_rand(void)
/* returns random number in range of 0 to 999999 */
{
 struct timespec ts;
#if defined(_POSIX_TIMERS) && _POSIX_TIMERS > 0
clock_gettime(CLOCK_REALTIME, &ts);
#else
struct timeval tv;
gettimeofday(&tv, NULL);
ts.tv_sec = tv.tv_sec;
ts.tv_nsec = tv.tv_usec * 1000;
#endif
	srandom(ts.tv_nsec);	
   return(random()%1000000);
}


typedef struct{
	double *x;
	double temp;
	}DesignPoint_t;

typedef struct{
	int iterations; 	/* Number of Iterations per Temp-Cycle */
	int vicinity;		/* The Vicinity a next design point might be in */
	double tempCoeff;	/* The Temperature Coefficient Typically between 0.4-0.9 */
	double temp;		/* Temperature */
	DesignPoint_t	dP;	/* Design Point */
	optim_t *optim;	/* The Optimization Problem to solve*/
}Simulated_Annealing_Param_t;

int main()
{
SimAnn();

return 0;
}

void fillRandom(int n /*dimension*/, double *min, double *max, double *x){
	int i =0;
	for(i=0; i < n /*dimension*/;i++){
		domainwidth = max[i]-min[i];
		x[i] =min[i] + domainwidth * gen_rand()/100000;
	}
}

double generateInitialTemp(int amount, Simulated_Annealing_Param_t *param){
	int i =0;
	double *x;
	double temp;
	temp = (double*) calloc( amount , sizeof(double);
	for(i =0; i< amount; i++){
		x = (double*) calloc( param->optim->n , sizeof(double);
		fillRandom( param->optim->n , param->optim->min , param->optim->max , x );
		temp += param->optim->f(param->optim,x);
		free(x);
	}
	temp/=amount;
	return temp;
}


void SimAnn(Simulated_Annealing_Param_t *param){

	FILE *file;
	file = fopen("file.txt","a+");

	int n =100, i=0, vicinity = 10, index =0;
	double c = 0.6, temp, temp_old, delta = 0, ecriterion = 5;


	if(param->temp == 0) param->temp = generateInitialTemp(10, param);	

	enum{SAinit, SAnewDPoint, SAMetropolisCrit, SAReduceTemp, SAStop}state;

	state = SAinit;
	
	
	while(state != SAStop)
	{
		switch(state){
			case SAinit:
				param->dP->x = (double *) calloc(param->n, sizeof(double));
				
				if(param->dP->x == NULL){
					state = SAStop;
					printf("Error: Could not allocate Memory!");
					break;
				}
				
				fillRandom( param->optim->n , param->optim->min , param->optim->max , param->dP->x );
				param->dP->temp = param->optim->f( param->optim , param->dP->x );

				printf("Starttemperatur = %lf\n", param->temp);
				state = SAnewDPoint;
				i=1;
			break;
			case SAnewDPoint:
				designPoints[index].x = designPoints[index-1].x+(gen_rand()/1000000.00*2*vicinity)-vicinity;
				designPoints[index].y = designPoints[index-1].y+(gen_rand()/1000000.00*2*vicinity)-vicinity;
				pfkt(&designPoints[index]);
				//printf("DPoint[%d] = x%lf y%lf res%lf\n", index, designPoints[index].x, designPoints[index].y,  designPoints[index].res);
				delta = designPoints[index].res- designPoints[index-1].res;
				if(delta >0){
					if(pow(2.71828182845,-delta/temp)>gen_rand()/1000000.00){
						index+=1;
						state = SAnewDPoint;
					}else{
						state = SAnewDPoint;
						break;
					}		
				}else{
					index+=1;
					state = SAnewDPoint;
				}
				fprintf(file,"%lf %lf %lf\n",designPoints[index-1].x, designPoints[index-1].y, designPoints[index-1].res);
				printf("%lf %lf %lf\n", designPoints[index-1].x, designPoints[index-1].y, designPoints[index-1].res);
				i++;
				if(i>n) state = SAReduceTemp;
			break;
			case SAReduceTemp:
				temp_old = temp;
				temp *= c;
				if(abs(temp_old-temp) < ecriterion){
					printf("Stoptemperatur = %lf\n",temp);
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
	free(designPoints);
}



