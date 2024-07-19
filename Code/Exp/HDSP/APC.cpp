#include "APC.h"
#include "HDSP/HDSP.h"
#include <sys/time.h>

void APC(point_set *pSet, point_t *q, hyperplane_set *R, int k, double epsilon)
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
                //cout << "Accuracy:" << 100 << "\n";
                //std::ofstream out_cp("../../result.txt");
                //out_cp << 100;
                //out_cp.close();
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
        //cout << "Accuracy:" << 100 << "\n";
        //std::ofstream out_cp("../../result.txt");
        //out_cp << 100;
        //out_cp.close();
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

    std::vector<point_set*> ListPartitionSet;
    R->setconvexhull();
    R->set_bounding_with_extremePoints();


    double numSample;
    if(pps->points[0]->dim <= 5)
        numSample = pow(10, pps->points[0]->dim - 1);
    else
        numSample = 10000;

    for(int i = 0; i < numSample; i++)
    {
        point_t * u = R->sampling();
        //u->attr[0]=0.22; u->attr[1]=0.78;
        //u->print();
        point_set *ps = pps->findTopK(u, k);
        double vl = q->dot_product(u);

        if((1-epsilon) * ps->points[ps->points.size() - 1]->dot_product(u) <= vl)//regret requirement
        {
            while (ps->points.size() > 0 && (1-epsilon) * ps->points[ps->points.size() - 1]->dot_product(u) <= vl)
                ps->points.pop_back();

            bool Exist = false;
            for (int j = 0; j < ListPartitionSet.size(); ++j)
            {
                if (ListPartitionSet[j]->points.size() < ps->points.size())
                {
                    if(ps->cover(ListPartitionSet[j]))
                    {
                        ListPartitionSet.erase(ListPartitionSet.begin() + j);
                        ListPartitionSet.push_back(ps);
                        Exist = true;
                        break;
                    }
                }
                else
                {
                    if(ListPartitionSet[j]->cover(ps))
                    {
                        Exist = true;
                        break;
                    }
                }
            }
            if(!Exist)
                ListPartitionSet.push_back(ps);
        }
    }

    //build partition
    for(int i = 0; i < ListPartitionSet.size(); ++i)
    {
        for(int j = 0; j < pps->points.size(); ++j)
        {
            bool exist = false;
            for(int l = 0; l < ListPartitionSet[i]->points.size(); ++l)
            {
                if(pps->points[j]->id == ListPartitionSet[i]->points[l]->id)
                {
                    exist = true;
                    break;
                }
            }
            if(!exist)
            {
                R->hyperplanes.push_back(new hyperplane(pps->points[j], q, epsilon));
            }
        }
        R->setconvexhull();
        //R->print();
    }



    /*check the accuracy
    double accuracy = 0;
    for(int i = 0; i < 10000; i++)
    {
        point_t * u = R->sampling();
        //u->attr[0]=0.22; u->attr[1]=0.78;
        //u->print();
        point_set *ps = pps->findTopK(u, k);
        double vl = q->dot_product(u);

        if((1-epsilon) * ps->points[ps->points.size() - 1]->dot_product(u) <= vl)//regret requirement
        {
            while (ps->points.size() > 0 && (1-epsilon) * ps->points[ps->points.size() - 1]->dot_product(u) <= vl)
                ps->points.pop_back();

            bool Exist = false;
            for (int j = 0; j < ListPartitionSet.size(); ++j)
            {
                if (ListPartitionSet[j]->points.size() > ps->points.size())
                {
                    if(ListPartitionSet[j]->cover(ps))
                    {
                        Exist = true;
                        break;
                    }
                }
            }
            if(!Exist)
                accuracy++;
        }
    }


    accuracy /= 10000;
    cout << "Accuracy:" << 100 <<"\n";
    std::ofstream out_cp("../../result.txt");
    out_cp << accuracy;
    out_cp.close();
    */





}


void APC_Accuracy(point_set *pSet, point_t *q, hyperplane_set *R, int k, double epsilon, double Samplesize)
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
                cout << "Accuracy:" << 1.0 << "\n";
                std::ofstream out_cp("../../result.txt");
                out_cp << 1.0;
                out_cp.close();
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
        cout << "Accuracy:" << 1.0 << "\n";
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
                        if (pps->points[j]->dominated.size() > k - 2)
                        {
                            pps->points[j]->value = -1;
                            R->hyperplanes.push_back(new hyperplane(pps->points[j], q, epsilon));
                        }
                    }
                    else if (relation == -1)
                    {

                        pps->points[j]->dominating.push_back(pps->points[i]);
                        pps->points[i]->dominated.push_back(pps->points[j]);
                        if (pps->points[i]->dominated.size() > k - 2)
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

    std::vector<point_set*> ListPartitionSet;
    R->setconvexhull();
    R->set_bounding_with_extremePoints();

    for(int i = 0; i < Samplesize; i++) //pow(10, pps->points[0]->dim - 1); i++)
    {
        point_t * u = R->sampling();
        //u->attr[0]=0.22; u->attr[1]=0.78;
        //u->print();
        point_set *ps = pps->findTopK(u, k);
        double vl = q->dot_product(u);

        if((1-epsilon) * ps->points[ps->points.size() - 1]->dot_product(u) <= vl)//regret requirement
        {
            while (ps->points.size() > 0 && (1-epsilon) * ps->points[ps->points.size() - 1]->dot_product(u) <= vl)
                ps->points.pop_back();

            bool Exist = false;
            for (int j = 0; j < ListPartitionSet.size(); ++j)
            {
                if (ListPartitionSet[j]->points.size() < ps->points.size())
                {
                    if(ps->cover(ListPartitionSet[j]))
                    {
                        ListPartitionSet.erase(ListPartitionSet.begin() + j);
                        ListPartitionSet.push_back(ps);
                        Exist = true;
                        break;
                    }
                }
                else
                {
                    if(ListPartitionSet[j]->cover(ps))
                    {
                        Exist = true;
                        break;
                    }
                }
            }
            if(!Exist)
                ListPartitionSet.push_back(ps);
        }
    }

    //build partition
    for(int i = 0; i < ListPartitionSet.size(); ++i)
    {
        for(int j = 0; j < pps->points.size(); ++j)
        {
            bool exist = false;
            for(int l = 0; l < ListPartitionSet[i]->points.size(); ++l)
            {
                if(pps->points[j]->id == ListPartitionSet[i]->points[l]->id)
                {
                    exist = true;
                    break;
                }
            }
            if(!exist)
            {
                R->hyperplanes.push_back(new hyperplane(pps->points[j], q, epsilon));
            }
        }
        R->setconvexhull();
        //R->print();
    }




    //check the accuracy
    double accuracy = 0.0;
    for(int i = 0; i < 10000; i++)
    {
        point_t * u = R->sampling();
        //u->attr[0]=0.22; u->attr[1]=0.78;
        point_set *ps = pps->findTopK(u, k);
        double vl = q->dot_product(u);

        if((1-epsilon) * ps->points[ps->points.size() - 1]->dot_product(u) <= vl)//regret requirement
        {
            while (ps->points.size() > 0 && (1-epsilon) * ps->points[ps->points.size() - 1]->dot_product(u) <= vl)
                ps->points.pop_back();

            bool Exist = false;
            for (int j = 0; j < ListPartitionSet.size(); ++j)
            {
                if (ListPartitionSet[j]->points.size() > ps->points.size())
                {
                    if(ListPartitionSet[j]->cover(ps))
                    {
                        Exist = true;
                        break;
                    }
                }
            }
            if(!Exist)
                accuracy++;
        }
    }


    accuracy /= 10000;
    accuracy = 1.0 - accuracy;
    cout << "Accuracy:" << accuracy <<"\n";

}

