#ifndef HYPERPLANE_SET_H
#define HYPERPLANE_SET_H

#include "point_t.h"
#include "point_set.h"
#include "hyperplane.h"
#include "libqhull_r/qhull_ra.h"

class hyperplane_set
{
public:
    qhT qh_qh;
    qhT *qh= &qh_qh;  /* Alternatively -- qhT *qh= (qhT *)malloc(sizeof(qhT)) */
    int lengthArray;
    double *array; //used to store the initial information of hyper-planes for computing convex hull
    std::vector<hyperplane*> hyperplanes;
    std::vector<point_t*> ext_pts;
    point_t *internal;
    double inRadius, outRadius;
    bool updateWithAdd, qhCanUse;

    hyperplane_set();
    explicit hyperplane_set(int dim);
    explicit hyperplane_set(hyperplane_set *R);
    ~hyperplane_set();

    //Prepare the file for computing the convex hull (the utility range R) via halfspace interaction
    void write(point_t* feasible_pt, char* filename);
    void write(point_set* pset, char* filename);
    void print();//print the information of the hyperplane set
    void printExtreme();
    bool setconvexhull();
    bool setconvexhull(point_t *fspt);
    bool set_bounding_with_extremePoints();
    point_t* find_feasible();
    point_t* find_feasible2();
    double find_interval();
    point_t* detect_feasible(hyperplane *h, point_t *inp);
    double LLP(double *obj, int minmax);
    bool add_halfspace(hyperplane *h, point_t *fspt);
    bool check_point_inside(point_t *p, double dis);

    bool R_dominate(point_t *p1, point_t *p2);
    void buildRelationBetweenPoint(point_set *pSet);
    void Rkskyband(point_set *pSet, int k);
    int check_relation(hyperplane *h);
    int check_relation_fast(hyperplane *h);
    point_t* average_point();

    void swap(int position1, int position2);
    void bubble(int start, int end);
    void bubbleSort(int start, int end);
    hyperplane* comparableSelect(int start, int end, int k);
    int findPosition(hyperplane *h);
    void samplingUtility(int dimension, int occupy, double segment, double *utility, std::vector<point_t*> &SampledV);
    point_t* sampling();
    bool divide(hyperplane *h, hyperplane_set *ptSet, hyperplane_set *ngSet);
    bool divide2(hyperplane *h, hyperplane_set *ptSet, hyperplane_set *ngSet);
};


#endif //U_2_HYPERPLANE_SET_H
