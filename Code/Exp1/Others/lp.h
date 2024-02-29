#ifndef LP_H
#define LP_H

#include <glpk.h>
#include "../structure/data_struct.h"
#include "../structure/data_utility.h"
#include "operation.h"
#include <vector>

// solve LP using GLPK

// Use LP to check whehter a point pt is a conical combination of the vectors in ExRays
bool insideCone(std::vector<point_t*> ExRays, point_t* pt);

// solve the LP in frame computation
void solveLP(std::vector<point_t*> B, point_t* b, double& theta, point_t* & pi);

#endif
