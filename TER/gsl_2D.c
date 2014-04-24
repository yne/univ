#define HAVE_INLINE 1
//#define GSL_RANGE_CHECK 0

#include <stdio.h>
#include <time.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include "in_wav.c"

void gsl_matrix_complex_invert(gsl_matrix_complex * fm,unsigned n){
	unsigned s,x,y;
	gsl_matrix_complex * m = gsl_matrix_complex_alloc (n, n);
	for(x=0;x<n;x++)for(y=0;y<n;y++)gsl_matrix_complex_set(m,x,y,gsl_matrix_complex_get(fm,x,y));
	gsl_matrix_complex * i = gsl_matrix_complex_alloc (n, n);
	gsl_permutation * perm = gsl_permutation_alloc (n);
	gsl_linalg_complex_LU_decomp (m, perm, &s);
	gsl_linalg_complex_LU_invert (m, perm, i);
	for(x=0;x<n;x++)for(y=0;y<n;y++)gsl_matrix_complex_set(fm,x,y,gsl_matrix_complex_get(i,x,y));
}
gsl_matrix_complex* getPhy(gsl_matrix_complex * y,unsigned rows,unsigned np){
	gsl_matrix_complex* phy=gsl_matrix_complex_alloc(rows-np,np);
	unsigned i,j;
	for(i=0;i<rows-np;i++)
		for(j=0;j<np;j++)
			gsl_matrix_complex_set(phy,i,j,gsl_matrix_complex_get(y,i+j,0));
	return phy;
}
gsl_matrix_complex* getTheta(gsl_matrix_complex * phy,gsl_matrix_complex * y,unsigned rows,unsigned np){
	gsl_matrix_complex* phy_phy=gsl_matrix_complex_alloc(np,np);
	gsl_blas_zgemm(CblasTrans, CblasNoTrans, GSL_COMPLEX_ONE, phy, phy, GSL_COMPLEX_ZERO, phy_phy);
	gsl_matrix_complex_invert(phy_phy,np);
	gsl_matrix_complex* phy_phy_phy=gsl_matrix_complex_alloc(rows-np,np);if(!phy_phy_phy || !phy_phy_phy->data || !phy_phy_phy->block )printf("can't malloc phy_phy_phy %i x %i",rows-np,np);
	gsl_blas_zgemm(CblasNoTrans, CblasNoTrans, GSL_COMPLEX_ONE, phy,phy_phy, GSL_COMPLEX_ZERO, phy_phy_phy);
	gsl_matrix_complex_free(phy_phy);
	
	gsl_matrix_complex y_view=*y;//create a np shifted view
	y_view.size1-=np;
	y_view.data+=np;
	
	gsl_matrix_complex* theta_estime=gsl_matrix_complex_alloc(np,1);
	gsl_blas_zgemm(CblasTrans, CblasNoTrans, GSL_COMPLEX_ONE, phy_phy_phy,&y_view, GSL_COMPLEX_ZERO, theta_estime);
	gsl_matrix_complex_free(phy_phy_phy);
	return theta_estime;
}
gsl_matrix_complex* applyCoeff(gsl_matrix_complex * e,unsigned rows,unsigned cols,gsl_complex*coeff,unsigned np){
	gsl_matrix_complex * y=gsl_matrix_complex_alloc(rows,cols);
	unsigned i,j,k;
	for(i=0;i<rows;i++){
		for(j=0;j<cols;j++){
			gsl_complex new_val=gsl_matrix_complex_get(e,i,j);
			//printf("%g %g\n",e->data[2*(i*cols + j)],e->data[1+2*(i*cols + j)]);
			//for(k=0;k<np;k++)new_val+=coeff[k]*gsl_matrix_complex_get(y,i-1-k,j);
			gsl_matrix_complex_set(y,i,j,new_val);
		}
	}
	return y;
}
double drand(){
	double ret;
	while((ret=(double)rand()-(double)RAND_MAX/2)==0);
	return ret;
}
gsl_matrix_complex* randomMatrix(unsigned rows,unsigned cols){
	gsl_matrix_complex* m=gsl_matrix_complex_alloc(rows,cols);
	gsl_complex cel;
	srand(time(0));
	unsigned i,j;
	for(j=0;j<rows;j++){
		for(i=0;i<cols;i++){
			GSL_SET_COMPLEX(&cel,drand(),drand());
			gsl_matrix_complex_set(m,i,j,cel);
		}
	}
	return m;
}

gsl_matrix_complex* linearize(gsl_matrix_complex*plan,unsigned rows,unsigned cols){
	gsl_matrix_complex* lin=gsl_matrix_complex_alloc(rows*cols,1);
	unsigned x,y,i=0;
	for(y=0;y<rows;y++)
		for(x=0;x<rows;i++,x++)
			gsl_matrix_complex_set(lin,i,0,gsl_matrix_complex_get(plan,x,y));
	gsl_matrix_complex_free(plan);
	return lin;
}

int main (int argc,char**argv){
//	gsl_set_error_handler_off();
	gsl_complex P[] = {
     { 1.0000 , +0.0000},
     { 0.0000 , +0.5000},
     {-0.0300 , +0.1000},
     { 0.0960 , +0.0050},
     {-0.2548 , +0.0490},
     { 0.0470 , -0.1176},
     {-0.8000 , -1.1000},
     { 0.5500 , -0.4000},
     { 0.1340 , -0.0470},
     {-0.0713 , -0.1096},
     { 0.2577 , +0.2411},
     {-0.1670 , +0.0423},
     {-0.1500 , +0.4500},
     {-0.2250 , -0.0750},
     {-0.0405 , -0.0285},
     {-0.0166 , +0.0424},
     { 0.0162 , -0.1220},
     { 0.0459 , +0.0388},
	};
	unsigned np=7;
	unsigned rows=32,cols=32,debug=1,i;
	gsl_matrix_complex* e,*y,*phy,*theta_estime;
	
	clock_t start_ms = clock();
	
	e = randomMatrix(rows,cols);
	if(debug)printf("Random Matrix (%i x %i) generated <%lims>\n",rows,cols,clock()-start_ms);
	
	y = applyCoeff(e,rows,cols,P,np);
	gsl_matrix_complex_free(e);
	
	if(debug)for(i=0,printf("coeff applied <%lims>:\n",clock()-start_ms);i<np;i++)printf("%+f %+f\n",P[i].dat[0],P[i].dat[1]);
	
	y=linearize(y,rows,cols);
	
	phy = getPhy(y,rows*cols,np);
	//gsl_matrix_complex_fprintf(stdout,phy,"%g");
	theta_estime = getTheta(phy,y,rows*cols,np);
	gsl_matrix_complex_free(phy);
	
	printf("\ntheta estime <%lims>:\n",clock()-start_ms);
	//gsl_matrix_complex_fprintf(stdout,theta_estime,"%g");
	gsl_matrix_complex_free(theta_estime);
	
	//dumpWavMatrix("out.wav",ctx,y);
	gsl_matrix_complex_free(y);
	return 0;
}