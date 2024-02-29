//#include "stdAfx.h"
#include "lp.h"

#include <vector>

//#define DEBUG_LP

// Takes an array of points s (of size N) and  a point pt and returns
// the direction in which pt has the worst regret ratio (in array v)
// as well as this regret ratio itself. 

/* We solve the following LP with col variables v[0], v[1], ..., v[D], x 
   and row variables q_1 ... q_{K-1}, r1, r_2
   
   Max x
   s.t. - (pt.a[0]-s[0].a[0])v[0] - (pt.a[1]-s[0].a[1])v[1] - ... - (pt.a[D-1]-s[0].a[D-1])v[D-1] + x = q_1
        - (pt.a[0]-s[1].a[0])v[0] - (pt.a[1]-s[1].a[1])v[1] - ... - (pt.a[D-1]-s[1].a[D-1])v[D-1] + x = q_2
        ...
        - (pt.a[0]-s[K-1].a[0])v[0] - (pt.a[1]-s[K-1].a[1])v[1] - ... - (pt.a[D-1]-s[K-1].a[D]-1)v[D-1] + x= q_K
           pt.a[0]v[0] + pt.a[1]v[1]  ....  + pt.a[D-1]v[D-1] = r1
          -pt.a[0]v[0] - pt.a[1]v[1]  ....  - pt.a[D-1]v[D-1] = r2
   variables have the following bounds
       0 <= v[j] < infty
       0 <= x < infty
       -infty < q_i  <=0
       -infty < r1 <= 1
       -infty < r2 <= -1
*/


// Use LP to check whether a point pt is a conical combination of the vectors in ExRays
bool insideCone(std::vector<point_t*> ExRays, point_t* pt)
{
	int M = ExRays.size();
	int D = pt->dim;

	int* ia = new int[1 + D * M];  //TODO: delete
	int* ja = new int[1 + D * M];  //TODO: delete
	double* ar = new double[1 + D * M];   //TODO: delete
	int i, j;
	double epsilon = 0.0000000000001;


	glp_prob *lp;
	lp = glp_create_prob();
	glp_set_prob_name(lp, "inside_cone");
	glp_set_obj_dir(lp, GLP_MAX);


	glp_add_rows(lp, D);  // add D rows: q_1...q_D
							  // Add rows q_1 ... q_D
	for (i = 1; i <= D; i++) {
		char buf[10];
		sprintf(buf, "q%d", i);
		glp_set_row_name(lp, i, buf);
		glp_set_row_bnds(lp, i, GLP_FX, pt->attr[i - 1], pt->attr[i-1]); // qi = pt->coord[i-1]
	}
	

	glp_add_cols(lp, M);    // add D columns: v[1] ... v[D]
								// Add col v[1] ... v[D]
	for (i = 1; i <= M; i++) {
		char buf[10];
		sprintf(buf, "v%d", i);

		glp_set_col_name(lp, i, buf);
		glp_set_col_bnds(lp, i, GLP_LO, 0.0, 0.0); // 0 <= v[i] < infty
		glp_set_obj_coef(lp, i, 0.0);  // objective: 0
	}

	int counter = 1;
	// set value on row q1 ... qD
	for (i = 1; i <= D; i++) {
		for (j = 1; j <= M; j++) {

			ia[counter] = i; ja[counter] = j;
			ar[counter++] = ExRays[j-1]->attr[i-1];
		}
	}



	// loading data  
	glp_load_matrix(lp, counter - 1, ia, ja, ar);



										  // running simplex
	glp_smcp parm;
	glp_init_smcp(&parm);
	parm.msg_lev = GLP_MSG_OFF; // turn off all message by glp_simplex 

	glp_simplex(lp, &parm);

	bool isOutside = glp_get_status(lp) == GLP_NOFEAS;

	//printf("solution is optimal: %d\n", GLP_OPT);
	//printf("no feasible solution: %d\n", GLP_NOFEAS);


	//printf("return: %d\n", result);
	//for (i = 0; i < M; i++)
	//{
	//	double v = glp_get_col_prim(lp, i + 1);
	//	printf("w%d = %lf\n", i + 1, v);
	//}

	glp_delete_prob(lp); // clean up
	delete[]ia;
	delete[]ja;
	delete[]ar;

	return !isOutside;
}


// solve the LP in frame computation
void solveLP(std::vector<point_t*> B, point_t* b, double& theta, point_t* & pi)
{
	int M = B.size()+1;
	int D = b->dim;

	point_t *mean = new point_t(D);
	for(int i = 0; i < D; i++)
		mean->attr[i] = 0;
	for(int i = 0; i < B.size(); i++)
	{
		for(int j = 0; j < D; j++)
			mean->attr[j] += B[i]->attr[j];
	}
	for(int i = 0; i < D; i++)
		mean->attr[i] /= B.size();

	int* ia = new int[1 + D * M];  //TODO: delete
	int* ja = new int[1 + D * M];  //TODO: delete
	double* ar = new double[1 + D * M];   //TODO: delete
	int i, j;
	double epsilon = 0.0000000000001;


	glp_prob *lp;
	lp = glp_create_prob();
	glp_set_prob_name(lp, "sloveLP");
	glp_set_obj_dir(lp, GLP_MIN);


	glp_add_rows(lp, D);  // add D rows: q_1...q_D
							  // Add rows q_1 ... q_D
	for (i = 1; i <= D; i++) {
		char buf[10];
		sprintf(buf, "q%d", i);
		glp_set_row_name(lp, i, buf);
		glp_set_row_bnds(lp, i, GLP_FX, b->attr[i - 1], b->attr[i-1]); // qi = pt->coord[i-1]
	}
	

	glp_add_cols(lp, M);    // add D columns: v[1] ... v[D]
								// Add col v[1] ... v[D]
	for (i = 1; i <= M; i++) {
		char buf[10];
		sprintf(buf, "v%d", i);

		glp_set_col_name(lp, i, buf);
		glp_set_col_bnds(lp, i, GLP_LO, 0.0, 0.0); // 0 <= v[i] < infty

		if(i == 1)
			glp_set_obj_coef(lp, i, 1); 
		else
			glp_set_obj_coef(lp, i, 0.0); 
	}

	int counter = 1;
	// set value on row q1 ... qD
	for (i = 1; i <= D; i++) {
		for (j = 1; j <= M; j++) {

			if(j == 1)
			{
				ia[counter] = i; ja[counter] = j;
				ar[counter++] = -mean->attr[i-1];
			}
			else
			{
				ia[counter] = i; ja[counter] = j;
				ar[counter++] = B[j-2]->attr[i-1];
			}
		}
	}



	// loading data  
	glp_load_matrix(lp, counter - 1, ia, ja, ar);

										  // running simplex
	glp_smcp parm;
	glp_init_smcp(&parm);
	parm.msg_lev = GLP_MSG_OFF; // turn off all message by glp_simplex 
	
	glp_simplex(lp, &parm);


	//printf("solution is optimal: %d\n", GLP_OPT);
	//printf("no feasible solution: %d\n", GLP_NOFEAS);
	bool feasible = glp_get_status(lp) == GLP_NOFEAS;

	theta = glp_get_obj_val(lp);
	for(int i = 0; i < D; i++)
	{
		pi->attr[i] = glp_get_row_dual(lp, i + 1);
	}
	//printf("return primal: %lf\n", glp_get_obj_val(lp));
	//for (i = 0; i < M; i++)
	//{
	//	double v = glp_get_col_prim(lp, i + 1);
	//	printf("p%d = %lf\n", i + 1, v);
	//}

	//printf("return dual: \n");
	//double dot_v = 0;
	//for (i = 0; i < D; i++)
	//{
	//	double v = glp_get_row_dual(lp, i + 1);
	//	dot_v += v * b->coord[i];
	//	printf("d%d = %lf\n", i + 1, v);
	//}
	//printf("dual objective: %lf\n", dot_v);

	glp_delete_prob(lp); // clean up
	delete[]ia;
	delete[]ja;
	delete[]ar;

	//printf("LP-verify:\n");
	//if(theta > 0 && insideCone(B, b) || isZero(theta) && !insideCone(B, b))
	//	printf("In-out error.\n");
	//if(!isZero(dot_prod(pi, b) - theta))
	//	printf("Objective value error.\n");
	//for(int i = 0; i < B.size(); i++)
	//{
	//	double v = dot_prod(B[i], pi);
	//	if(v >0 && !isZero(v))
	//		printf("Hyperplane error.\n");
	//}
	//double v = dot_prod(mean,pi);
	//if(v > -1 && !isZero(v+1))
	//	printf("Mean vector error.\n");

	delete mean;
}