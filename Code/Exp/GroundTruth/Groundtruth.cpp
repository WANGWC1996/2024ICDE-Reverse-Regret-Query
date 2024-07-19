#include "Groundtruth.h"

/**
 * @brief Find the nearest point of e
 * @param p_skyline The point set
 * @param e         The expected point
 */
void ground_truth(point_set *pset, point_t *e, int k)
{
    point_set *ps = pset->findNearestK(e, k);
    std::cout << "--------------------------------------------------------------------------------------------------\n";
    printf("|%15s |%15s |%15s |%15s |%10d |%15s |\n", "Ground Truth", "-", "-", "-", ps->points[0]->id, "-");
    for(int i = 1; i < ps->points.size(); ++i)
        printf("|%15s |%15s |%15s |%15s |%10d |%15s |\n", "-", "-", "-", "-", ps->points[i]->id, "-");
    std::cout << "--------------------------------------------------------------------------------------------------\n";
}
