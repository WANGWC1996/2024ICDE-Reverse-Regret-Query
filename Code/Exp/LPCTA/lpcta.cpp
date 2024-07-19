#include "lpcta.h"




void LPcta(point_set *pSet, point_t *q, hyperplane_set *R, int k, double epsilon)
{
    int dim = q->dim - 1; //the dimension of the utility space
    for(int i = 0; i < pSet->points.size(); ++i)
    {
        if(q->epsilonDominatelatter(pSet->points[i], epsilon)) //check q is dominated by the p
        {
            pSet->points.erase(pSet->points.begin() + i);
            i--;
        }
        else if(pSet->points[i]->epsilonDominateformer(q, epsilon)) //check q dominates p
        {
            pSet->points.erase(pSet->points.begin() + i);
            i--; k--;
            if(k <= 0) //There are k points which epsilon-dominate q
            {
                std::cout << "The query point does not satisfy the regret requirement for any utility function.\n";
                return;
            }
        }
    }
    if(pSet->points.size() <= 0)
    {
        std::cout << "The query point satisfies the regret requirement for any utility function.\n";
        return;
    }

    //build R-tree for data points
    R_TYPE **data;
    int no_data;
    node_type *dataroot;
    rtree_info *aInfo;
    aInfo = (rtree_info *) malloc(sizeof(rtree_info));
    memset(aInfo, 0, sizeof(rtree_info));
    aInfo->m = 18;
    aInfo->M = 36;
    aInfo->dim = pSet->points[0]->dim;
    aInfo->reinsert_p = 27;
    aInfo->no_histogram = pSet->points.size();
    no_data = aInfo->no_histogram; //number of point
    data = (R_TYPE **) malloc(sizeof(R_TYPE *) * no_data);
    for (int i = 0; i < no_data; i++)
    {
        data[i] = (R_TYPE *) malloc(sizeof(R_TYPE) * aInfo->dim);
        for (int j = 0; j < aInfo->dim; j++)
        {
            data[i][j] = pSet->points[i]->attr[j];
        }
    }
    build_tree(&dataroot, data, no_data, aInfo);

    point_set *PR = new point_set(), *SL;
    std::vector<point_set*> DG;
    SL = BBSskyline(pSet);
    PR->buildrelation(SL, DG);
    point_set *S = new point_set(SL);
    ccell *root = new ccell();
    hyperplane_set *rootHyS = new hyperplane_set(dim);
    root->internal = rootHyS->find_feasible();

    while(1)
    {
        for (int i = 0; i < S->points.size(); ++i)
        {
            hyperplane *h = new hyperplane(S->points[i], q, epsilon);
            root->optInsert(h, DG[i], k);
            if (root->ISeleminate)
            {
                return;
            }
        }

        //root->print(dim, k);
        //update PR and pSet(D-PR)
        for(int i = 0; i < S->points.size(); ++i)
            S->points[i]->processed = 1;
        PR->add(S); // currently, processed points
        pSet->minus(S); //currently, unprocessed points
        //initialize non-pivots
        point_set *NP = new point_set();
        std::vector<ccell*> leaf;
        root->findLeaf(leaf, dim, k);
        for(int i = 0; i < leaf.size(); ++i)
        {
            point_set *NPc = new point_set(), *Pc = new point_set();
            leaf[i]->find_pivot_nonpivot(NPc, Pc);
            bool existss = false;
            for(int j = 0; j < pSet->points.size(); ++j)
            {
                if (!Pc->dominate(pSet->points[j]) && NPc->dominate(pSet->points[j]))
                {
                    existss = true;
                    break;
                }
            }
            if(existss)
            {
                int rankLow = 1, rankUp = 1;
                point_t *wlow = leaf[i]->find_vector(-1, dim);
                point_t *wup = leaf[i]->find_vector(1, dim);
                double SpcLow = leaf[i]->boundforPt(q, -1);
                double SpcUp = leaf[i]->boundforPt(q, 1);
                leaf[i]->updateRankbound(dataroot, aInfo->M, aInfo->dim, k, wlow, wup, SpcLow, SpcUp, rankLow, rankUp);
                if (rankLow > k)
                {
                    leaf[i]->ISeleminate = 1;
                    leaf[i]->passEleminate();
                }
                else if (rankUp <= k)
                {
                    hyperplane_set *cpartition = new hyperplane_set(dim);
                    leaf[i]->searchBound(cpartition);
                    cpartition->setconvexhull();
                    //cpartition->print();
                    leaf[i]->ISeleminate = 1;
                    leaf[i]->passEleminate();
                }
                else
                    NP->add(NPc);
            }
            else
            {
                hyperplane_set *cpartition = new hyperplane_set(dim);
                leaf[i]->searchBound(cpartition);
                cpartition->setconvexhull();
                //cpartition->print();
                leaf[i]->ISeleminate = 1;
                leaf[i]->passEleminate();
            }
        }

        leaf.clear();
        if (root->ISeleminate)
            return;
        SL->minus(NP);
        SL->add(pSet);
        SL = BBSskyline(SL);
        S->points.clear();
        for(int i = 0; i < SL->points.size(); ++i)
        {
            if(!SL->points[i]->processed)
                S->points.push_back(SL->points[i]);
        }
        DG.clear();
        PR->buildrelation(S, DG);
    }


}