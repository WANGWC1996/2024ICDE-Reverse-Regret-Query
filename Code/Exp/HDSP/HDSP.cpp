#include "HDSP.h"

void HDSWLazy(point_set *pSet, point_t *q, hyperplane_set *R, int k, double epsilon)
{
    timeval t1; gettimeofday(&t1, 0);
    int num = pSet->points.size();

    //Check the points which dominate or are dominated by q
    vector<int> DominatingPoints;
    for(int i = 0; i < num; ++i)
    {
        if(q->epsilonDominatelatter(pSet->points[i], epsilon)) //check q is dominated by the p
        {
            pSet->points[i]->value = -1;
        }
        else if(pSet->points[i]->epsilonDominateformer(q, epsilon)) //check q dominates p
        {
            pSet->points[i]->value = -1;
            DominatingPoints.push_back(i);
            k--;
            if(k <= 0) //There are k points which epsilon-dominate q
            {
                cout << "The query point does not satisfy the regret requirement for any utility function.\n";
                return;
            }
        }
    }
    point_set *pps = new point_set();
    for(int i = 0; i < pSet->points.size(); ++i)
    {
        if (pSet->points[i]->value != -1)
        {
            pSet->points[i]->setNormalizedHyper(q, epsilon);
            pps->points.push_back(pSet->points[i]);
        }
    }

    if(pps->points.size() <= 0)
    {
        //R->print();
        std::cout << "The query point satisfies the regret requirement for any utility function.\n";
        return;
    }

    for(int i = 0; i < pps->points.size() - 1; ++i)
    {
        if(pps->points[i]->value != -1)
        {
            for (int j = i + 1; j < pps->points.size(); ++j)
            {
                if (pps->points[j]->value != -1)
                {
                    int relation = pps->points[i]->q_dominate(pps->points[j]);
                    if (relation == 1)
                    {
                        pps->points[i]->dominating.push_back(pps->points[j]);
                        pps->points[j]->dominated.push_back(pps->points[i]);
                        int ppsjdom = pps->points[j]->dominated.size();
                        if (ppsjdom > k - 2)
                        {
                            pps->points[j]->value = -1;
                            R->hyperplanes.push_back(new hyperplane(pps->points[j], q, epsilon));
                        }
                    }
                    else if (relation == -1)
                    {

                        pps->points[j]->dominating.push_back(pps->points[i]);
                        pps->points[i]->dominated.push_back(pps->points[j]);
                        int ppsidom = pps->points[j]->dominated.size();
                        if (ppsidom > k - 2)
                        {
                            pps->points[i]->value = -1;
                            R->hyperplanes.push_back(new hyperplane(pps->points[i], q, epsilon));
                            break;
                        }
                    }
                }
            }
        }
    }


    R->setconvexhull();
    R->set_bounding_with_extremePoints();
    int pindex = pps->findMinDominted(), count = pps->points.size();
    halfspace_tree *hTree = new halfspace_tree(R);
    for(int i = 0; i < count; ++i)
    {

        hyperplane *h = new hyperplane(pps->points[pindex], q, epsilon);
        if(i % 10 == 0)
            cout << i << "\n";
        hTree->insertLazy(h, k);
        pps->points[pindex]->value = -1;
        pindex = pps->findMinDominted();
        //hTree->print();

    }
    //hTree->print_useful_partition(k);
}























