#include "Baseline.h"

/**
 * @brief Find all the combinations of the half-spaces
 * @param pSet          The point set
 * @param q             The query point
 * @param k             Parameter k
 * @param epsilon       Parameter epsilon
 * @param sideList      The list for recording the half-spaces are positive or negative
 * @param position      The current position of the scanning
 * @param poSide        The current number of half-spaces
 */
void buildIntersection(point_set *pSet, point_t *q, hyperplane_set *R, int k, double epsilon, double *sideList, int position, int poSide)
{
    if(poSide == k)
    {
        for(int i = position + 1; i < pSet->points.size(); ++i)
            sideList[i] = 0;

        hyperplane_set *newR = new hyperplane_set();
        for(int i = 0; i < R->hyperplanes.size(); ++i)
            newR->hyperplanes.push_back(new hyperplane(R->hyperplanes[i]));
        for(int i = 0; i < pSet->points.size(); ++i)
        {
            hyperplane *h = new hyperplane(pSet->points[i], q, epsilon);
            if(sideList[i] == 1)
            {
                for(int j = 0; j < q->dim - 1; ++j)
                    h->norm[j] = - h->norm[j];
                h->offset = - h->offset;
            }
            newR->hyperplanes.push_back(h);
        }

        //if(R->find_feasible() != NULL)
        if(newR->setconvexhull() != false)
        {
            cout << "Partition: \n";
            newR->printExtreme();
        }
        delete newR;
    }
    else if (poSide < k)
    {
        ++position;
        if(position < pSet->points.size())
        {
            sideList[position] = 1;
            buildIntersection(pSet, q, R, k, epsilon, sideList, position, poSide + 1);
            sideList[position] = 0;
            buildIntersection(pSet, q, R, k, epsilon, sideList, position, poSide);
        }
    }

}

/**
 * @brief Baseline algorithms
 * @param pSet
 * @param q
 * @param k
 * @param epsilon
 * @param dis
 * @param type
 * @param mem_baseline
 */
void baseline(point_set *pSet, point_t *q, hyperplane_set *R, int k, double epsilon)
{
    std::ofstream out_cp("../../result.txt");
    int num = pSet->points.size();
    double *sideList = new double[num];

    for(int i = 0; i < k; ++i)
        buildIntersection(pSet, q, R, i, epsilon, sideList, -1, 0);


}
