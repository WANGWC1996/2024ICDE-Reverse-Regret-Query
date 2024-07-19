#ifndef QHULL_CTREE_H
#define QHULL_CTREE_H
#include "hyperplane_set.h"
#include "rtree.h"

class ccell
{
public:

    ccell *left, *right, *parent;
    hyperplane_set *coverSet;
    point_t *internal;
    hyperplane *splitHyper;
    bool ISeleminate;

    ccell();
    void optInsert(hyperplane *h, point_set* dominated, int k);
    int rank(hyperplane_set *hSet);
    bool isdomiated(hyperplane *h, point_set* dominated);
    void findLeaf(std::vector<ccell*> &leaf, int dim, int k);
    void find_pivot_nonpivot(point_set *NPc, point_set *Pc);
    void print(int dim, int k);
    void searchBound(hyperplane_set *hs);
    void passEleminate();
    point_t* find_vector(int minmax, int dim);
    double boundforPt(point_t *p, int minmax);
    void updateRankbound(node_type *n, int M, int dim, int k, point_t *wlow, point_t *wup, double SpcLow,
                            double SpcUp, int &rankLow, int &rankUp);
};


class ctree
{
public:








};


#endif //QHULL_CTREE_H
