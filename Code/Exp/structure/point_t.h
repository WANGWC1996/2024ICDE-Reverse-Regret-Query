#ifndef POINT_T_H
#define POINT_T_H
#include "define.h"
#include <list>

class point_t
{
public:
    int	id; //point ID
    int dim; //point dimension
    double *attr; //the values of dimensions
    int hyperID; //the id of the corresponding hyper-plane
    double value;
    std::vector<point_t*> positiveHalf, negativeHalf, bothHalf; //
    std::vector<point_t*> ptList;
    point_t *normlizedHyper;
    std::vector<point_t*> dominating; //p dominates the points
    std::vector<point_t*> dominated; //the points dominate p
    int clusterID;
    int postiveSampleU;
    bool processed;


    explicit point_t(int dim);
    explicit point_t(int dim, double *p);
    explicit point_t(int dim, int id);
    explicit point_t(point_t *p);
    point_t(point_t *p1, point_t *p2);
    ~point_t();
    void print();
    void printCoordinates();

    bool is_same(point_t *p);
    bool is_zero();
    bool dominate(point_t *p);
    int q_dominate(point_t *p);

    bool epsilonDominateformer(point_t *p, double epsilon);
    bool epsilonDominatelatter(point_t *p, double epsilon);
    double dot_product(point_t* p);
    double dot_product(double *v);
    point_t* sub(point_t* p);
    point_t* add(point_t* p);
    point_t* scale(double c);
    double distance(point_t* p);
    double distance(double *p);
    bool existPositiveHalf(point_t *p);
    bool existNegativeHalf(point_t *p);
    void setNormalizedHyper(point_t *q, double epsilon);

    void printResult(char *name, int Qcount, timeval t1);
    void printResult(std::ofstream &out_cp, char *name, int Qcount, timeval t1, double preTime,
                     long mem_baseline, double Pcize, int type);


    bool same_cover(point_t *p);

};










#endif //U_2_POINT_T_H
