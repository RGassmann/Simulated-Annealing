#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<sys/types.h>
#include <time.h>
#include <math.h>

#if defined(_POSIX_TIMERS) && _POSIX_TIMERS > 0
#include<time.h>
#else
#include<sys/time.h>
#endif


int gen_rand(void)
/* returns random number in range of 0 to 99 */
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
double fkt(double x1, double x2){
	return 500 -20*x1-26*x2-4*x1*x2+4*x1*x1+3*x2*x2;
}
void SimAnn();

typedef struct{
	double x;
	double y;
	double res;
	}dPoint;

void pfkt(dPoint *p){
	p->res = fkt(p->x,p->y);
}

int main()
{
int n =2, vicinity = 6;
double c = 0.5, temp;

dPoint p1;
p1.x=2; p1.y=0; p1.res = fkt(p1.x,p1.y);

dPoint p2;
p2.x=5; p2.y=10; p2.res = fkt(p2.x,p2.y);

dPoint p3;
p3.x=8; p3.y=5; p3.res = fkt(p3.x,p3.y);

dPoint p4;
p4.x=10; p4.y=10; p4.res = fkt(p4.x,p4.y);

temp = (p1.res + p2.res + p3.res + p4.res)/4;

printf("Starttemperatur = %lf\n",temp);

SimAnn();
/*
for(n =0; n < 100; n++){
printf("Z = %lf\n",gen_rand()/1000000.00);
}*/

return 0;
}


void SimAnn(){

FILE *file;
file = fopen("file.txt","a+");
	dPoint *designPoints;
	dPoint test;
	int n =100, i=0, vicinity = 10, index =0;
	double c = 0.6, temp, temp_old, delta = 0, ecriterion = 5;

	dPoint p1;
	p1.x=2; p1.y=0; p1.res = fkt(p1.x,p1.y);

	dPoint p2;
	p2.x=5; p2.y=10; p2.res = fkt(p2.x,p2.y);

	dPoint p3;
	p3.x=8; p3.y=5; p3.res = fkt(p3.x,p3.y);

	dPoint p4;
	p4.x=10; p4.y=10; p4.res = fkt(p4.x,p4.y);

	temp = 1500;//(p1.res + p2.res + p3.res + p4.res)/4;
	enum{SAinit, SAnewDPoint, SAMetropolisCrit, SAReduceTemp, SAStop}state;

	state = SAinit;
	
	
	while(state != SAStop)
	{
		switch(state){
			case SAinit:
				designPoints = (dPoint *) malloc(4096*sizeof(test));
				if(designPoints == NULL){
					state = SAStop;
					printf("Error");
					break;
				}
				designPoints[index].x = -150;
				designPoints[index].y = 54;
				pfkt(&designPoints[index]);
				printf("Starttemperatur = %lf\n",temp);
				printf("DPoint 1 = %lf\n",  designPoints[index].res);
				state = SAnewDPoint;
				index+=1;
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



