#ifndef HYPERPLANE_H
#define HYPERPLANE_H

#include "point_t.h"
#include "point_set.h"

class hyperplane
{
public:
    int dim;        //dimension
    double* norm;   //parameter of the norm vector
    double offset;
    double normLength; //the length of the norm
    point_t* p_1;
    point_t* p_2;
    int direction;
    double xaxis, type; //for two 2dsw only

    hyperplane();
    explicit hyperplane(int dim);
    explicit hyperplane(hyperplane* h);
    hyperplane(hyperplane *h, int direction);
    hyperplane(int dim, double *n, double off);
    hyperplane(point_t *p1, point_t *p2, double epsilon);
    hyperplane(int d, double* p1, double* p2, double epsilon);
    ~hyperplane();
    void print();

    void set_normLength();
    bool is_same(hyperplane *h);
    int check_position(point_t *p);
    int check_positive(point_t *p);
    int check_negative(point_t *p);
    double check_distance(point_t *p);
    double check_distance_withSign(point_t *p);
};


#endif //U_2_HYPERPLANE_H
