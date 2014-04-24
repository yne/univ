#include <stdio.h>
#include <time.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include "in_wav.c"
/*
void gsl_matrix_invert(gsl_matrix * fm,unsigned n){
	unsigned s,x,y;
	gsl_matrix * m = gsl_matrix_alloc (n, n);
	for(x=0;x<n;x++)for(y=0;y<n;y++)gsl_matrix_set(m,x,y,gsl_matrix_get(fm,x,y));
	gsl_matrix * i = gsl_matrix_alloc (n, n);
	gsl_permutation * perm = gsl_permutation_alloc (n);
	gsl_linalg_LU_decomp (m, perm, &s);
	gsl_linalg_LU_invert (m, perm, i);
	for(x=0;x<n;x++)for(y=0;y<n;y++)gsl_matrix_set(fm,x,y,gsl_matrix_get(i,x,y));
}
gsl_matrix* getPhy(gsl_matrix * y,unsigned rows,unsigned np){
	gsl_matrix* phy=gsl_matrix_alloc(rows-np,np);
	unsigned i,j;
	for(i=0;i<rows-np;i++)
		for(j=0;j<np;j++)
			gsl_matrix_set(phy,i,j,gsl_matrix_get(y,i+j,0));
	return phy;
}
gsl_matrix* getTheta(gsl_matrix * phy,gsl_matrix * y,unsigned rows,unsigned np){
	gsl_matrix* phy_phy=gsl_matrix_alloc(np,np);
	gsl_blas_dgemm(CblasTrans, CblasNoTrans, 1.0, phy, phy, 0.0, phy_phy);
	gsl_matrix_invert(phy_phy,np);
	gsl_matrix* phy_phy_phy=gsl_matrix_alloc(rows-np,np);
	gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, phy,phy_phy, 0.0, phy_phy_phy);
	gsl_matrix_free(phy_phy);
	
	gsl_matrix y_view=*y;//create a np shifted view
	y_view.size1-=np;
	y_view.data+=np;
	
	gsl_matrix* theta_estime=gsl_matrix_alloc(np,1);
	gsl_blas_dgemm(CblasTrans, CblasNoTrans, 1.0, phy_phy_phy,&y_view, 0.0, theta_estime);
	gsl_matrix_free(phy_phy_phy);
	return theta_estime;
}
gsl_matrix* applyCoeff(gsl_matrix * e,unsigned rows,unsigned cols,double*coeff,unsigned np){
	gsl_matrix * y=gsl_matrix_alloc(rows,cols);
	//gsl_matrix_memcpy(y,e);
	unsigned i,j,k;
	for(i=np;i<rows;i++){
		for(j=0;j<cols;j++){
			double new_val=0;
			for(k=0;k<np+1;k++)
				new_val+=(k?coeff[k-1]:1)*gsl_matrix_get(e,i-k,j);
			gsl_matrix_set(y,i,j,new_val);
		}
	}
	return y;
}
*/
double drand(){
	return (double)rand()-(double)RAND_MAX/2;
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

int main (int argc,char**argv){
//	gsl_set_error_handler_off();
	double coeff[] = {-0.0,-0.0};
	unsigned rows=64,cols=64,np=sizeof(coeff)/sizeof(coeff[0]);
	gsl_matrix_complex* e,*y,*phy,*theta_estime;
	
	void * ctx;
	e = randomMatrix(rows,cols);
	/*
	clock_t start_ms = clock();
	
	y = applyCoeff(e,rows,cols,coeff,np);
	gsl_matrix_free(e);
	
	//gsl_matrix_fprintf(stdout,y,"%g");
	
	phy = getPhy(y,rows,np);
	theta_estime = getTheta(phy,y,rows,np);
	gsl_matrix_free(phy);
	
	printf("%lims\n",(clock()-start_ms));
	
	gsl_matrix_fprintf(stdout,theta_estime,"%g");
	gsl_matrix_free(theta_estime);
	dumpWavMatrix("out.wav",ctx,y);
	gsl_matrix_complex_free(y);
	*/
	return 0;
}