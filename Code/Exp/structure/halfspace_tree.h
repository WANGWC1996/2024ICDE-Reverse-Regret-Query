#ifndef RUN_HALFSPACE_TREE_H
#define RUN_HALFSPACE_TREE_H
#include "hyperplane_set.h"




class hp_node
{
public:
    int ID;
    hyperplane_set *set;
    point_t *dividePt;
    std::vector<hyperplane*> unprocessedHyper;
    int numPHalfspace;
    hp_node *pt, *ng, *origin;
    bool sure;
    std::vector<hyperplane*> involvedHyper;
    std::vector<point_t*> sampledU;

    hp_node();
    hp_node(hp_node *org);
    hp_node(int dim);
    hp_node(hyperplane_set *hset);
    ~hp_node();
    void insert(hyperplane *h, int k);
    void insert_fast(hyperplane *h, int k);
    void insertLazy(hyperplane *h, int k);
    void updateThreshold(int k);

    void print();
    void print_useful_partition(int k);
    void increase_numPHalfspace(int k);
};


class halfspace_tree
{
public:
    hp_node *root;

    halfspace_tree(int dim);
    halfspace_tree(hyperplane_set *hset);
    halfspace_tree(point_set* pps, point_t *q, double epsilon, int k, point_set* totalSampledV, std::vector<hp_node*> &processedNode);

    void insert(hyperplane *h, int k);
    void insert_fast(hyperplane *h, int k);
    void insertLazy(hyperplane *h, int k);
    void print_useful_partition(int k);
    void print();
};


#endif //RUN_HALFSPACE_TREE_H
