#ifndef POINT_SET_H
#define POINT_SET_H

#include "point_t.h"
#include <string>

class point_set
{
public:
    std::vector<point_t*> points;

    point_set();
    explicit point_set(point_set *p_set);
    explicit point_set(const char* input);
    ~point_set();


    void print();
    void random(double RandRate);
    void buildRelation();
    void refineBasedonRelation(int k);
    point_set* sort(point_t *u);



    void skyline(point_set *SL);
    void BBS_skyline(point_set *SL, point_set *SLNP);
    int refind_with_queryPt(point_t *q, int k, double epsilon);
    void buildrelation(point_set *SL, std::vector<point_set*> &DG);
    point_set* findTopK(point_t* u, int k);
    int findMinDominted();
    bool findCluster();
    void printForCluster();
    void setNormalizedHyper(point_t *q, double epsilon);
    bool dominate(point_t* p);
    void add(point_set *pSet);
    void minus(point_set *pSet);
    double calculate_segment(point_t *q, double epsilon, double error);

    bool cover(point_set *ps);
    void write(std::string fileName);
    void prunePt(point_t* p);
    void printResult(std::ofstream &out_cp, char *name, int Qcount, timeval t1, double preTime, long mem_baseline,
                                double Pcize, int type);

};


#endif //U_2_POINT_SET_H
