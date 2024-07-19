#ifndef RUN_HDSP_H
#define RUN_HDSP_H
#include "point_set.h"
#include "hyperplane_set.h"
#include "data_utility.h"
#include "Others/operation.h"
#include "halfspace_tree.h"





void HDSW(point_set *pSet, point_t *q, hyperplane_set *R, int k, double epsilon, double dis, int type);

void HDSWFast(point_set *pSet, point_t *q, hyperplane_set *R, int k, double epsilon, double segment);

void HDSWLazy(point_set *pSet, point_t *q, hyperplane_set *R, int k, double epsilon);

void HDSW_Sampling1(point_set *pSet, point_t *q, hyperplane_set *R, int k, double epsilon, double segment);

#endif //RUN_HDSP_H
