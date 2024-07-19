//#include "stdafx.h"

#include <fstream>
#include "operation.h"

// is x equal to 0 ?
int isZero(double x)
{
	return x > -EQN_EPS && x < EQN_EPS;
}

/*
 *	Calculate the dot product between two points
 */
double dot_prod(double* v1, double* v2, int dim)
{
	double result = 0;
	int i;
	for (i = 0; i < dim; i++)
	{
		result += v1[i] * v2[i];
	}
	return result;
}

// compute the rank of the guass matrix (used for computing frames)
int guassRank(vector< point_t* > P)
{
	int dim = P[0]->dim;

	std::vector<vector<double> > A;
	for(int i = 0; i < P.size(); i++)
	{
		vector<double> v;
		for(int j = 0; j < dim; j++)
		{
			v.push_back(P[i]->attr[j]);
		}
		A.push_back(v);
	}
	while(A.size() < dim)
	{
		vector<double> v;
		for(int j = 0; j < dim; j++)
		{
			v.push_back(0);
		}
		A.push_back(v);

	}
	
	int n = A.size();
	int d = A[0].size();

	//for (int i = 0; i < n; i++)
	//{
	//	for (int j = 0; j < d; j++)
	//		printf("%lf ", A[i][j]);
	//	printf("\n");
	//}
	//printf("\n");

	for (int i = 0; i< d; i++) {
		// Search for maximum in this column
		double maxEl = abs(A[i][i]);
		int maxRow = i;
		for (int k = i + 1; k<n; k++) {
			if (abs(A[k][i]) > maxEl) {
				maxEl = abs(A[k][i]);
				maxRow = k;
			}
		}

		// Swap maximum row with current row (column by column)
		for (int k = i; k<d; k++) {
			double tmp = A[maxRow][k];
			A[maxRow][k] = A[i][k];
			A[i][k] = tmp;
		}

		// Make all rows below this one 0 in current column
		for (int k = i + 1; k<n; k++) {
			double c = -A[k][i] / A[i][i];
			for (int j = i; j<d; j++) {
				if (i == j) {
					A[k][j] = 0;
				}
				else {
					A[k][j] += c * A[i][j];
				}
			}
		}
	}

	int count = 0;
	for (int i = 0; i < n; i++)
	{
		bool allZero = true;
		for (int j = 0; j < d; j++)
		{
			if (!isZero(A[i][j]))
			{
				allZero = false;
				break;
			}
		}

		if (!allZero)
			count++;
	}
	return count;
}

// check if two vectors are linearly independent (used for computing frames)
bool linearInd(point_t* p, point_t* q)
{
	int dim = p->dim;

	bool pZero = true, qZero = true;
	double ratio;
	for(int i = 0; i < dim; i++)
	{
		if(!isZero(q->attr[i]))
		{
			qZero = false;
			ratio = p->attr[i] / q->attr[i];
		}
		if(!isZero(p->attr[i]))
			pZero = false;
	}

	if(pZero || qZero)
		return true;

	for(int i = 0; i < dim; i++)
	{
		if(!isZero(ratio - p->attr[i] / q->attr[i]))
			return true;
	}

	return false;
}



// get the pointer of point in P
point_t* getPoint(point_set* p, double* point)
{
	int dim = p->points[0]->dim;

	for(int i = 0; i < p->points.size(); i++)
	{
		bool match = true;
		for(int j = 0; j < dim; j++)
		{
			if(!isZero(p->points[i]->attr[j] - point[j]))
			{
				match = false;
				break;
			
			}
		}
		if(match)
			return p->points[i];
	}
	return NULL;
}

void print(double *a, int d)
{
    for(int i = 0; i < d; i++)
    {
        std::cout<<a[i]<<" ";
    }
    std::cout<<"\n";
}

/**
 * @brief Check whether p1 R-dominates p2
 * @param p1 The first point
 * @param p2 The second point
 * @param R  The numerical utility range
 * @return   1 R-dominates
 *          -1 Does not R-dominate
 */
bool R_cover(double *p1, double *p2, std::vector<point_t *> &R)
{
    int size = R.size(), d = R[0]->dim;
    double *v = new double[d];//set difference as a vector
    double dot = 0;
    for(int i = 0; i < d; i++)
    {
        v[i] = p1[i] - p2[i];
        if(-EQN3 < v[i] && v[i] < EQN3)
            dot++;
    }
    if(dot==d)
        return true;
    for (int i = 0; i < size; i++)
    {
        dot = R[i]->dot_product(v);
        if (dot < -EQN2)
            return false;
    }
    return true;
}

/**
 * @brief Check whether p1 and p2 are the same
 * @param p1    The first vector
 * @param p2    The second vector
 * @param dim   The number of dimensions of vectors
 * @return      1 The are the same
 *              0 The are not the same
 */
bool is_same_array(double *p1, double *p2, int dim)
{
    double minus = p1[0] / p2[0];
    for(int i = 1; i < dim; i++)
    {
        if(p1[i] / p2[i] - minus < -EQN4 || p1[i] / p2[i] - minus > -EQN4)
            return false;
    }
    return true;
}

/**
 * @brief Get the memeory usage
 * @return
 */
long get_mem_usage()
{
    struct rusage myusage;
    getrusage(RUSAGE_SELF, &myusage);
    //cout << myusage.ru_stime.tv_usec <<"\n";
    return myusage.ru_maxrss;
}

/**
 * @brief Print the execution time from t1 to current
 * @param t1        The start time
 * @param preTime   The preprocessing time
 * @param csize     The size of the candidate set
 */
void printMiddleResult(ofstream &out_cp, timeval t1, double preTime, int Qcount, double csize, double reducesize, long mem_baseline, int type)
{

    timeval t2;
    gettimeofday(&t2, 0);
    double time_cost =
            (double) t2.tv_sec + (double) t2.tv_usec / 1000000 - (double) t1.tv_sec - (double) t1.tv_usec / 1000000;
    std::cout << Qcount << "    " << csize << "    " << reducesize << "    " << time_cost - preTime << "\n";
    if (type == 1)
    {
        out_cp << Qcount << "    " << csize << "    " << reducesize << "    " << time_cost - preTime << "\n";
    }
}



























