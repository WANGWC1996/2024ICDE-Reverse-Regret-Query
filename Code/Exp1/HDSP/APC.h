#ifndef QHULL_APC_H
#define QHULL_APC_H
#include "hyperplane_set.h"
#include "data_utility.h"
#include "Others/operation.h"


void APC(point_set *pSet, point_t *q, hyperplane_set *R, int k, double epsilon);

void APC_Accuracy(point_set *pSet, point_t *q, hyperplane_set *R, int k, double epsilon, double Samplesize);




#endif //QHULL_APC_H
