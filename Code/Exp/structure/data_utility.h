#ifndef DATA_UTILITY_H
#define DATA_UTILITY_H
#include "data_struct.h"
#include "hyperplane.h"
#include "point_set.h"

// sort the 2d points clockwise
struct angleCmp
{
    bool operator()(const point_t* lhs, const point_t* rhs) const
    {
        double lhs_angle = lhs->attr[1] == 0 ? PI / 2 : atan(lhs->attr[0] / lhs->attr[1]);
        double rhs_angle = rhs->attr[1] == 0 ? PI / 2 : atan(rhs->attr[0] / rhs->attr[1]);
        return lhs_angle < rhs_angle;
    }
};

struct anglehyperCmp
{
    bool operator()(const hyperplane * lhs, const hyperplane* rhs) const
    {
        double lhs_angle = lhs->norm[1] == 0 ? PI / 2 : atan(lhs->norm[0] / lhs->norm[1]);
        double rhs_angle = rhs->norm[1] == 0 ? PI / 2 : atan(rhs->norm[0] / rhs->norm[1]);
        return lhs_angle < rhs_angle;
    }
};

struct valueCmp
{
    bool operator()(const point_t* lhs, const point_t* rhs) const
    {
        double lhs_value = lhs->value;
        double rhs_value = rhs->value;
        return lhs_value < rhs_value;
    }
};

// allocate/release memory for points/hyperplanes
point_t* rand_point(int dim);

double timeCost(timeval t1);

#endif