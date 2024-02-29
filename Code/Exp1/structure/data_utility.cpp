#include "data_utility.h"


/*
 * @brief Generate a random point in dim-dimensional space
 * @param dim   The number of dimension
 * @return      The generated point
 */
point_t *rand_point(int dim)
{
    point_t *point_v = new point_t(dim);

    for (int i = 0; i < dim; i++)
        point_v->attr[i] = rand() * 1.0 / RAND_MAX;

    //print_point(point_v);

    return point_v;
}

/**
 * @brief Calculate the time cost from t1 to now
 * @param t1
 * @return
 */
double timeCost(timeval t1)
{
    timeval t2; gettimeofday(&t2, 0);
    double time_cost = (double) t2.tv_sec + (double) t2.tv_usec / 1000000 - (double) t1.tv_sec - (double) t1.tv_usec / 1000000;
    //std::cout << "Preprocessing Cost: "<< time_cost << "\n";
    return  time_cost;
}
