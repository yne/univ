#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define np 2
#define L 1000000

//stocké en .bss car pas assez de place en stack
float e[L]/*={
 -0.3454,
 -0.1115,
	0.1604,
	0.3008,
	0.1839,
 -0.1114,
	0.0697,
 -0.2177,
	0.1201,
	0.0826,
}*/;
float y[L];
float phi[L-np][np];
float pp[np][np];//=phi*phi'
float ipp[np][np];//=inv(phi*phi')
float ppc[L-np][np];//=inv(phi*phi')
float theta[1][np];//=inv(phi*phi')

int main(int argc,char**argv){
	unsigned i,j,k;
	
	clock_t start_ms = clock();
	
	srand(time(0));
	for(i=0;i<L;i++)e[i]=(float)rand()-(float)RAND_MAX/2;
//	printf("=== e ===\n");for(i=0;i<L;i++)printf("%+f\n",e[i]);
	
	memcpy(y,e,sizeof(e));
	for(i=np;i<L;i++)
		y[i]= -1.5*y[i-1] -0.5*y[i-2] + e[i];
//	printf("=== y ===\n");for(i=0;i<L;i++)printf("%+f\n",y[i]);
	
	for(j=0;j<np;j++)
		for(i=0;i<L-np;i++)
			phi[i][j]=y[i+j];
//	printf("== phi ==\n");for(i=0;i<L-np;i++)printf("%+f %+f\n",phi[i][0],phi[i][1]);
	
	for(i=0;i<np;i++)
		for(j=0;j<np;j++,pp[i][j]=0)
			for(k=0;k<L-np;k++)//printf("%i %i = %f\t%i %i = %f\n",k,i,phi[k][i],k,j,phi[k][j]);
				pp[i][j]+=phi[k][i]*phi[k][j];//printf("\n");
//	printf("======= p*p'=======\n");for(i=0;i<np;i++,printf("\n"))for(j=0;j<np;j++)printf("%+f ",pp[i][j]);

	float det=1/(pp[0][0]*pp[1][1] - pp[0][1]*pp[0][1]);//1.6179
	ipp[0][0]= pp[1][1]*det;
	ipp[0][1]=-pp[0][1]*det;
	ipp[1][0]=-pp[1][0]*det;
	ipp[1][1]= pp[0][0]*det;
//	printf("==== inv(p*p') ====\n");for(i=0;i<np;i++,printf("\n"))for(j=0;j<np;j++)printf("%+f ",ipp[i][j]);
	
	for(i=0;i<L-np;i++)
		for(j=0;j<np;j++)
			for(k=0,ppc[i][j]=0;k<np;k++)
				ppc[i][j]+=phi[i][k]*ipp[k][j];
//	printf("== phi*inv(p*p') ==\n");for(i=0;i<L-np;i++,printf("\n"))for(j=0;j<np;j++)printf("%+f ",ppc[i][j]);
	
	for(i=0;i<1;i++)
		for(j=0;j<np;j++)
			for(k=0,theta[i][j]=0;k<L-np;k++)
				theta[i][j]+=y[np+k]*ppc[k][j];
	printf("====== theta ======\n");for(i=0;i<1;i++,printf("\n"))for(j=0;j<np;j++)printf("%+f ",theta[i][j]);
	
	printf("%li\n",(clock()-start_ms));
	
	return 0;
}