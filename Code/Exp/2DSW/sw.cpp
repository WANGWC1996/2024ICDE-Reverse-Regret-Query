#include "sw.h"



/**
 * @brief Algorithm 2DSW
 * @param pSet          The point set
 * @param q             The query point
 * @param k             Parameter k
 * @param epsilon       Parameter
 */
void twodsw2(point_set *pSet, point_t *q, int k, double epsilon)
{
    std::ofstream out_cp("../../result.txt");
    int num = pSet->points.size();

    //build the hyper-planes
    hyperplane_set *upHyper = new hyperplane_set(), *downHyper = new hyperplane_set();
    vector<int> dominatePoints;
    for(int i = 0; i < num; ++i)
    {
        if((1 - epsilon) * pSet->points[i]->attr[0] > q->attr[0] &&
            (1 - epsilon) * pSet->points[i]->attr[1] > q->attr[1]) //dominate
        {
            --k;
            dominatePoints.push_back(i);
        }
        else if((1 - epsilon) * pSet->points[i]->attr[0] > q->attr[0] &&
                (1 - epsilon) * pSet->points[i]->attr[1] < q->attr[1])
        {
            hyperplane *h = new hyperplane(pSet->points[i], q, epsilon);
            h->xaxis = h->norm[1] / (- h->norm[0] + h->norm[1]);
            h->type = 0; //down
            downHyper->hyperplanes.push_back(h);
        }
        else if((1 - epsilon) * pSet->points[i]->attr[0] < q->attr[0] &&
                (1 - epsilon) * pSet->points[i]->attr[1] > q->attr[1])
        {
            hyperplane *h = new hyperplane(pSet->points[i], q, epsilon);
            h->xaxis = h->norm[0] / (h->norm[0] - h->norm[1]);
            h->type = 1; //up
            upHyper->hyperplanes.push_back(h);
        }
    }

    if(k > 0) //if k < 0, q is not a k-regret point
    {
        hyperplane_set *kHyper = new hyperplane_set();
        int covered;
        //insert the top-k hyper-planes in downHyper
        if (downHyper->hyperplanes.size() > k)
        {
            //find the smallest k
            hyperplane *downH = downHyper->comparableSelect(0, downHyper->hyperplanes.size() - 1, k);
            //find top-k
            for (int i = 0; i < downHyper->hyperplanes.size(); ++i)
            {
                //cout << downHyper->hyperplanes[i]->xaxis <<"\n";
                if (downH->xaxis >= downHyper->hyperplanes[i]->xaxis)
                {
                    //downHyper2->hyperplanes.push_back(downHyper->hyperplanes[i]);
                    int pp = kHyper->findPosition(downHyper->hyperplanes[i]);
                    kHyper->hyperplanes.insert(kHyper->hyperplanes.begin() + pp, downHyper->hyperplanes[i]);
                }
            }
        }
        else
        {
            for (int i = 0; i < downHyper->hyperplanes.size(); ++i)
            {
                int pp = kHyper->findPosition(downHyper->hyperplanes[i]);
                kHyper->hyperplanes.insert(kHyper->hyperplanes.begin() + pp, downHyper->hyperplanes[i]);
            }
        }

        //insert the top-k hyper-planes in upHyper
        if (upHyper->hyperplanes.size() >= k)
        {
            hyperplane *upH = upHyper->comparableSelect(0, upHyper->hyperplanes.size() - 1, k);
            for (int i = 0; i < upHyper->hyperplanes.size(); ++i)
            {
                if (upH->xaxis >= upHyper->hyperplanes[i]->xaxis)
                {
                    //upHyper2->hyperplanes.push_back(upHyper->hyperplanes[i]);
                    upHyper->hyperplanes[i]->xaxis = 1 - upHyper->hyperplanes[i]->xaxis;
                    int pp = kHyper->findPosition(upHyper->hyperplanes[i]);
                    kHyper->hyperplanes.insert(kHyper->hyperplanes.begin() + pp, upHyper->hyperplanes[i]);
                }
            }
            covered = k;
        }
        else
        {
            for (int i = 0; i < upHyper->hyperplanes.size(); ++i)
            {
                int pp = kHyper->findPosition(upHyper->hyperplanes[i]);
                kHyper->hyperplanes.insert(kHyper->hyperplanes.begin() + pp, upHyper->hyperplanes[i]);
            }
            covered = upHyper->hyperplanes.size();
        }


        /*for(int i = 0; i < k; ++i)
            upHyper->hyperplanes[i]->xaxis = 1 - upHyper->hyperplanes[i]->xaxis;


        for(int i = 0; i < k; ++i)
        {
            int pp = kHyper->findPosition(upHyper2->hyperplanes[i]);
            kHyper->hyperplanes.insert(kHyper->hyperplanes.begin() + pp, upHyper2->hyperplanes[i]);
            pp = kHyper->findPosition(downHyper2->hyperplanes[i]);
            kHyper->hyperplanes.insert(kHyper->hyperplanes.begin() + pp, downHyper2->hyperplanes[i]);
        }
        */

        //sweeping
        int leftexist = 0;
        if (covered < k)
        {
            cout << "(0, 1) -- ";
            leftexist = 1;
        }
        for (int i = 0; i < kHyper->hyperplanes.size(); ++i)
        {
            if (kHyper->hyperplanes[i]->type == 0)
            {
                ++covered;
                if (covered == k)
                {
                    cout << "(" << kHyper->hyperplanes[i]->xaxis << ", " << 1 - kHyper->hyperplanes[i]->xaxis << ")\n";
                    leftexist = 0;
                }
            }
            else
            {
                --covered;
                if (covered == k - 1)
                {
                    cout << "(" << kHyper->hyperplanes[i]->xaxis << ", " << 1 - kHyper->hyperplanes[i]->xaxis
                         << ") -- ";
                    leftexist = 1;
                }
            }
        }

        if (leftexist == 1)
            cout << "(1, 0)\n";
    }

}


/**
 * @brief Algorithm 2DSW
 * @param pSet          The point set
 * @param q             The query point
 * @param k             Parameter k
 * @param epsilon       Parameter
 */
void twodsw2(point_set *pSet, point_t *q, hyperplane_set *R, int k, double epsilon)
{
    std::ofstream out_cp("../../result.txt");
    int num = pSet->points.size();

    //build the hyper-planes
    hyperplane_set *leftHyper = new hyperplane_set(), *rightHyper = new hyperplane_set();
    vector<int> dominatePoints;
    for(int i = 0; i < num; ++i)
    {
        if((1 - epsilon) * pSet->points[i]->attr[0] > q->attr[0] &&
           (1 - epsilon) * pSet->points[i]->attr[1] > q->attr[1]) //epl_dominate the query point
        {
            --k;
            dominatePoints.push_back(i);
        }
        else if((1 - epsilon) * pSet->points[i]->attr[0] > q->attr[0] &&
                (1 - epsilon) * pSet->points[i]->attr[1] < q->attr[1])
        {
            hyperplane *h = new hyperplane(pSet->points[i], q, epsilon);
            h->xaxis = -h->offset / h->norm[0];
            h->type = 0; //right
            rightHyper->hyperplanes.push_back(h);
        }
        else if((1 - epsilon) * pSet->points[i]->attr[0] < q->attr[0] &&
                (1 - epsilon) * pSet->points[i]->attr[1] > q->attr[1])
        {
            hyperplane *h = new hyperplane(pSet->points[i], q, epsilon);
            h->xaxis = U_RANGE + h->offset / h->norm[0]; //for ranking use
            h->type = 1; //left
            leftHyper->hyperplanes.push_back(h);
        }
    }

    if(k > 0) //if k < 0, q is not a k-regret point
    {
        hyperplane_set *kHyper = new hyperplane_set();
        int covered;
        //insert the top-k hyper-planes in downHyper
        if (rightHyper->hyperplanes.size() > k) // If there are more than k hyper-planes
        {
            //find the smallest k
            hyperplane *downH = rightHyper->comparableSelect(0, rightHyper->hyperplanes.size() - 1, k);
            //find the top-k
            for (int i = 0; i < rightHyper->hyperplanes.size(); ++i)
            {
                //cout << rightHyper->hyperplanes[i]->xaxis <<"\n";
                if (downH->xaxis >= rightHyper->hyperplanes[i]->xaxis)
                {
                    int pp = kHyper->findPosition(rightHyper->hyperplanes[i]);
                    kHyper->hyperplanes.insert(kHyper->hyperplanes.begin() + pp, rightHyper->hyperplanes[i]);
                }
            }
        }
        else // If there are <=k hyper-planes, we need to insert all the hyper-planes
        {
            for (int i = 0; i < rightHyper->hyperplanes.size(); ++i)
            {
                int pp = kHyper->findPosition(rightHyper->hyperplanes[i]);
                kHyper->hyperplanes.insert(kHyper->hyperplanes.begin() + pp, rightHyper->hyperplanes[i]);
            }
        }

        //insert the top-k hyper-planes in upHyper
        if (leftHyper->hyperplanes.size() > k)
        {
            hyperplane *upH = leftHyper->comparableSelect(0, leftHyper->hyperplanes.size() - 1, k);
            for (int i = 0; i < leftHyper->hyperplanes.size(); ++i)
            {
                if (upH->xaxis >= leftHyper->hyperplanes[i]->xaxis)
                {
                    //upHyper2->hyperplanes.push_back(upHyper->hyperplanes[i]);
                    leftHyper->hyperplanes[i]->xaxis = U_RANGE - leftHyper->hyperplanes[i]->xaxis;
                    int pp = kHyper->findPosition(leftHyper->hyperplanes[i]);
                    kHyper->hyperplanes.insert(kHyper->hyperplanes.begin() + pp, leftHyper->hyperplanes[i]);
                }
            }
            covered = k;
        }
        else
        {
            for (int i = 0; i < leftHyper->hyperplanes.size(); ++i)
            {
                leftHyper->hyperplanes[i]->xaxis = U_RANGE - leftHyper->hyperplanes[i]->xaxis;
                int pp = kHyper->findPosition(leftHyper->hyperplanes[i]);
                kHyper->hyperplanes.insert(kHyper->hyperplanes.begin() + pp, leftHyper->hyperplanes[i]);
            }
            covered = leftHyper->hyperplanes.size();
        }


        /*for(int i = 0; i < k; ++i)
            upHyper->hyperplanes[i]->xaxis = 1 - upHyper->hyperplanes[i]->xaxis;


        for(int i = 0; i < k; ++i)
        {
            int pp = kHyper->findPosition(upHyper2->hyperplanes[i]);
            kHyper->hyperplanes.insert(kHyper->hyperplanes.begin() + pp, upHyper2->hyperplanes[i]);
            pp = kHyper->findPosition(downHyper2->hyperplanes[i]);
            kHyper->hyperplanes.insert(kHyper->hyperplanes.begin() + pp, downHyper2->hyperplanes[i]);
        }
        */

        //sweeping
        int leftexist = 0;
        if (covered < k)
        {
            cout << "(0, "<< U_RANGE << ") -- ";
            leftexist = 1;
        }
        for (int i = 0; i < kHyper->hyperplanes.size(); ++i)
        {
            if (kHyper->hyperplanes[i]->type == 0)
            {
                ++covered;
                if (covered == k)
                {
                    cout << "(" << kHyper->hyperplanes[i]->xaxis << ", " << U_RANGE - kHyper->hyperplanes[i]->xaxis << ")\n";
                    leftexist = 0;
                }
            }
            else
            {
                --covered;
                if (covered == k - 1)
                {
                    cout << "(" << kHyper->hyperplanes[i]->xaxis << ", " << U_RANGE - kHyper->hyperplanes[i]->xaxis
                         << ") -- ";
                    leftexist = 1;
                }
            }
        }

        if (leftexist == 1)
            cout << "(" << U_RANGE << ", 0)\n";
    }
    else
    {
        cout << "The query point does not satisfy the regret requirement for any utility function.\n";
    }

}



/**
 * @brief Algorithm 2DSW
 * @param pSet          The point set
 * @param q             The query point
 * @param k             Parameter k
 * @param epsilon       Parameter
 */
void twodsw(point_set *pSet, point_t *q, hyperplane_set *R, int k, double epsilon)
{
    int num = pSet->points.size();

    //build the hyper-planes
    hyperplane_set *leftHyper = new hyperplane_set(), *rightHyper = new hyperplane_set();
    vector<int> dominatePoints;
    for(int i = 0; i < num; ++i)
    {
        hyperplane *h = new hyperplane(pSet->points[i], q, epsilon);
        int rel = R->check_relation(h);
        if(rel == 1) //epl_dominate the query point
        {
            --k;
            dominatePoints.push_back(i);
        }
        else if(rel == 0 && h->norm[0] > 0)
        {
            h->xaxis = -h->offset / h->norm[0];
            h->type = 0; //right
            rightHyper->hyperplanes.push_back(h);
        }
        else if(rel == 0 && h->norm[0] < 0)
        {
            h->xaxis = U_RANGE + h->offset / h->norm[0]; //for ranking use
            h->type = 1; //left
            leftHyper->hyperplanes.push_back(h);
        }
    }

    if(k > 0) //if k < 0, q is not a k-regret point
    {
        hyperplane_set *kHyper = new hyperplane_set();
        int covered;
        //insert the top-k hyper-planes in downHyper
        if (rightHyper->hyperplanes.size() > k) // If there are more than k hyper-planes
        {
            //find the smallest k
            hyperplane *downH = rightHyper->comparableSelect(0, rightHyper->hyperplanes.size() - 1, k);
            //find the top-k
            for (int i = 0; i < rightHyper->hyperplanes.size(); ++i)
            {
                //cout << rightHyper->hyperplanes[i]->xaxis <<"\n";
                if (downH->xaxis >= rightHyper->hyperplanes[i]->xaxis)
                {
                    int pp = kHyper->findPosition(rightHyper->hyperplanes[i]);
                    kHyper->hyperplanes.insert(kHyper->hyperplanes.begin() + pp, rightHyper->hyperplanes[i]);
                }
            }
        }
        else // If there are <=k hyper-planes, we need to insert all the hyper-planes
        {
            for (int i = 0; i < rightHyper->hyperplanes.size(); ++i)
            {
                int pp = kHyper->findPosition(rightHyper->hyperplanes[i]);
                kHyper->hyperplanes.insert(kHyper->hyperplanes.begin() + pp, rightHyper->hyperplanes[i]);
            }
        }

        //insert the top-k hyper-planes in upHyper
        if (leftHyper->hyperplanes.size() > k)
        {
            hyperplane *upH = leftHyper->comparableSelect(0, leftHyper->hyperplanes.size() - 1, k);
            for (int i = 0; i < leftHyper->hyperplanes.size(); ++i)
            {
                if (upH->xaxis >= leftHyper->hyperplanes[i]->xaxis)
                {
                    //upHyper2->hyperplanes.push_back(upHyper->hyperplanes[i]);
                    leftHyper->hyperplanes[i]->xaxis = U_RANGE - leftHyper->hyperplanes[i]->xaxis;
                    int pp = kHyper->findPosition(leftHyper->hyperplanes[i]);
                    kHyper->hyperplanes.insert(kHyper->hyperplanes.begin() + pp, leftHyper->hyperplanes[i]);
                }
            }
            covered = k;
        }
        else
        {
            for (int i = 0; i < leftHyper->hyperplanes.size(); ++i)
            {
                leftHyper->hyperplanes[i]->xaxis = U_RANGE - leftHyper->hyperplanes[i]->xaxis;
                int pp = kHyper->findPosition(leftHyper->hyperplanes[i]);
                kHyper->hyperplanes.insert(kHyper->hyperplanes.begin() + pp, leftHyper->hyperplanes[i]);
            }
            covered = leftHyper->hyperplanes.size();
        }




        //for(int i = 0; i < kHyper->hyperplanes.size(); ++i)
        //    std::cout << kHyper->hyperplanes[i]->xaxis << "  " << kHyper->hyperplanes[i]->type << "\n";


        //sweeping
        int leftexist = 0;
        if (covered < k)
        {
            cout << "("<< R->ext_pts[0]->attr[0] << ") -- ";
            leftexist = 1;
        }
        for (int i = 0; i < kHyper->hyperplanes.size(); ++i)
        {
            if (kHyper->hyperplanes[i]->type == 0)
            {
                ++covered;
                if (covered == k)
                {
                    cout << "(" << kHyper->hyperplanes[i]->xaxis << ")\n";
                    leftexist = 0;
                }
            }
            else
            {
                --covered;
                if (covered == k - 1)
                {
                    cout << "(" << kHyper->hyperplanes[i]->xaxis << ") -- ";
                    leftexist = 1;
                }
            }
        }

        if (leftexist == 1)
            cout << "(" << R->ext_pts[1]->attr[0] << ")\n";
    }
    else
    {
        cout << "The query point does not satisfy the regret requirement for any utility function.\n";
    }

}