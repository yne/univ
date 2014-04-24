#include <stdio.h>
#include <time.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include "in_wav.c"

void gsl_matrix_invert(gsl_matrix * fm,unsigned n){
	unsigned s,x,y;
	gsl_matrix * m = gsl_matrix_alloc (n, n);if(!m || !m->data || !m->block )printf("can't malloc m %i x %i",n,n);
	for(x=0;x<n;x++)for(y=0;y<n;y++)gsl_matrix_set(m,x,y,gsl_matrix_get(fm,x,y));
	gsl_matrix * i = gsl_matrix_alloc (n, n);if(!i || !i->data || !i->block )printf("can't malloc i %i x %i",n,n);
	gsl_permutation * perm = gsl_permutation_alloc (n);
	gsl_linalg_LU_decomp (m, perm, &s);
	gsl_linalg_LU_invert (m, perm, i);
	for(x=0;x<n;x++)for(y=0;y<n;y++)gsl_matrix_set(fm,x,y,gsl_matrix_get(i,x,y));
}
gsl_matrix* getPhy(gsl_matrix * y,unsigned rows,unsigned np){
	gsl_matrix* phy=gsl_matrix_alloc(rows-np,np);if(!phy || !phy->data || !phy->block )printf("can't malloc phy %i x %i",rows-np,np);
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
	gsl_matrix* phy_phy_phy=gsl_matrix_alloc(rows-np,np);if(!phy_phy_phy || !phy_phy_phy->data || !phy_phy_phy->block )printf("can't malloc phy_phy_phy %i x %i",rows-np,np);
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
	gsl_matrix * y=gsl_matrix_alloc(rows,cols);if(!y || !y->data || !y->block )printf("can't malloc y %i x %i",rows,cols);
	unsigned i,j,k;
	for(i=np;i<rows;i++){
		for (j=0;j<cols;j++){
			double new_val = gsl_matrix_get(e,i,j);
			for(k=0;k<np;k++)new_val+=coeff[k]*gsl_matrix_get(y,i-1-k,j);
			gsl_matrix_set(y,i,j,new_val);
		}
	}
	return y;
}
double drand(){
	double ret;
	while((ret=(double)rand()-(double)RAND_MAX/2)==0)printf("<re-roll>");
	return ret;
}
gsl_matrix* randomMatrix(unsigned rows,unsigned cols){
	srand(time(0));
	gsl_matrix* e=gsl_matrix_alloc(rows,cols);
	unsigned i;
	for(i=0;i<rows*cols;i++)e->data[i]=drand();
	return e;
}

int main (int argc,char**argv){
//	gsl_set_error_handler_off();
	double P[] = {-0.5,-1.5};
	unsigned np=sizeof(P)/sizeof(P[0]);
	unsigned rows=1000,cols=1,debug=1,i;
	gsl_matrix* e,*y,*phy,*theta_estime;
	
	clock_t start_ms = clock();
	
	//void * ctx;
	//e = wavMatrix("test.wav",&ctx,&rows,&cols);
	e = randomMatrix(rows,cols);
	if(debug)printf("Matrix (%i x %i) generated <%lims> \n",rows,cols,(clock()-start_ms));
	
	y = applyCoeff(e,rows,cols,P,np);
	gsl_matrix_free(e);
	
	if(debug)for(i=0,printf("coeff applied <%lims>:\n",(clock()-start_ms));i<np;i++)printf("%g\n",P[i]);
	
	phy = getPhy(y,rows,np);
	theta_estime = getTheta(phy,y,rows,np);
	gsl_matrix_free(phy);
	
	printf("\ntheta estime <%lims>:\n",(clock()-start_ms));
	gsl_matrix_fprintf(stdout,theta_estime,"%g");
	gsl_matrix_free(theta_estime);
	
	//dumpWavMatrix("out.wav",ctx,y);
	gsl_matrix_free(y);
	return 0;
}