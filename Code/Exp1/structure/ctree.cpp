#include "ctree.h"



/**
 * @brief Constructor
 */
ccell::ccell()
{
    coverSet = new hyperplane_set();
    left = NULL; right = NULL; parent = NULL;
    internal = NULL;
    splitHyper = NULL;
    ISeleminate = false;
}


/**
 * @brief Check the relation between a convex hull and a hyper-plane
 * @param h     The hyper-plane
 * @return
 */
void ccell::optInsert(hyperplane *h, point_set* dominated, int k)
{
    if(ISeleminate)
        return;

    hyperplane_set *hs = new hyperplane_set(h->dim);
    searchBound(hs);

    if(rank(hs) > k || (left != NULL && right != NULL && left->ISeleminate && right->ISeleminate))
    {
        ISeleminate = true;
        passEleminate();
        return;
    }

    if(isdomiated(h, dominated))
        coverSet->hyperplanes.push_back(h);
    else
    {
        point_t *p1 = hs->detect_feasible(h, internal);
        if (p1 == NULL)
        {
            coverSet->hyperplanes.push_back(new hyperplane(h, -1));
        }
        else
        {
            point_t *p2 = hs->detect_feasible(new hyperplane(h, -1), internal);
            if (p2 == NULL)
                coverSet->hyperplanes.push_back(h);
            else
            {
                if (left == NULL && right == NULL) //leaf
                {
                    left = new ccell();
                    left->splitHyper = h;
                    left->parent = this;
                    left->internal = p1;
                    right = new ccell();
                    right->splitHyper = new hyperplane(h, -1);
                    right->parent = this;
                    right->internal = p2;
                }
                else //internal node
                {
                    left->optInsert(h, dominated, k);
                    right->optInsert(h, dominated, k);
                }
            }
        }
    }
}

/**
 * @brief Check if there exists a point whose hyper-plane (1). is in the set from the root to the node
 *                                                        (2). its negative halfspace covers that of h
 * @param h             The hyper-plane
 * @param dominated     The points which dominate the point of h
 * @return
 */
bool ccell::isdomiated(hyperplane *h, point_set *dominated)
{
    for(int i = 0; i < coverSet->hyperplanes.size(); ++i)
    {
        if (coverSet->hyperplanes[i]->direction == -1)
        {
            for (int j = 0; j < dominated->points.size(); ++j)
            {
                if (coverSet->hyperplanes[i]->p_1->id == dominated->points[j]->id)
                    return true;
            }
        }
    }

    if (splitHyper!= NULL && splitHyper->direction == -1)
    {
        for (int j = 0; j < dominated->points.size(); ++j)
        {
            if (splitHyper->p_1->id == dominated->points[j]->id)
                return true;
        }
    }

    if(parent != NULL)
        return parent->isdomiated(h, dominated);
    else
        return false;
}



/**
 * @brief Count the number of positive half-spaces
 * @param hSet
 * @return
 */
int ccell::rank(hyperplane_set *hSet)
{
    int pnum = 0;
    for(int i = 0; i < hSet->hyperplanes.size(); ++i)
    {
        if(hSet->hyperplanes[i]->direction == 1)
            ++pnum;
    }

    //consider all the cover hyper-planes
    ccell *currentCell = this;
    while(currentCell != NULL)
    {
        for (int i = 0; i < currentCell->coverSet->hyperplanes.size(); ++i)
        {
            if (currentCell->coverSet->hyperplanes[i]->direction == 1)
                ++pnum;
        }
        currentCell = currentCell->parent;
    }
    return  pnum + 1;
}


/**
 * @brief Find all the leaf node in the tree, where the current node is the root of the tree
 * @param leaf      All the node
 */
void ccell::findLeaf(std::vector<ccell *> &leaf, int dim, int k)
{
    if(!ISeleminate)
    {
        if (left == NULL && right == NULL)
        {
            hyperplane_set *hs = new hyperplane_set();
            searchBound(hs);
            if (rank(hs) <= k)
            {
                leaf.push_back(this);
            }
            else
            {
                ISeleminate = true;
                passEleminate();
            }
            delete hs;
        }
        else
        {
            left->findLeaf(leaf, dim, k);
            right->findLeaf(leaf, dim, k);
        }
    }
}




/**
 * @brief Find the non pivot
 * @param hSet
 */
void ccell::find_pivot_nonpivot(point_set *NPc, point_set *Pc)
{
    ccell *cur = this;
    while (cur != NULL)
    {
        for (int i = 0; i < cur->coverSet->hyperplanes.size(); ++i)
        {
            if (cur->coverSet->hyperplanes[i]->direction == 1)
                NPc->points.push_back(cur->coverSet->hyperplanes[i]->p_1);
            else if (cur->coverSet->hyperplanes[i]->direction == -1)
                Pc->points.push_back(cur->coverSet->hyperplanes[i]->p_1);
        }

        if(cur->splitHyper != NULL)
        {
            if (cur->splitHyper->direction == 1)
                NPc->points.push_back(cur->splitHyper->p_1);
            else if (cur->splitHyper->direction == -1)
                Pc->points.push_back(cur->splitHyper->p_1);
        }
        cur = cur->parent;
    }
}


/**
 * @brief Find all the possible boundary hyper-plane
 * @param hs    The hyper-plane set
 */
void ccell::searchBound(hyperplane_set *hs)
{
    ccell *cur  = this;
    while (cur != NULL)
    {
        if(cur->splitHyper != NULL)
            hs->hyperplanes.push_back(cur->splitHyper);
        cur = cur->parent;
    }
}





/**
 * @brief Print the partitions in the leaves which are not eliminated.
 * @param k
 */
void ccell::print(int dim, int k)
{
    if(!ISeleminate)
    {
        if(left != NULL && right != NULL)
        {
            left->print(dim, k);
            right->print(dim, k);
        }
        else
        {
            hyperplane_set *hs = new hyperplane_set(dim);
            searchBound(hs);
            if(rank(hs) <= k)
            {
                hs->setconvexhull();
                hs->print();
            }
        }
    }
}


/**
 * @brief Check if we can eleminate the parent node
 */
void ccell::passEleminate()
{
    ccell *cur = this->parent;
    if(cur != NULL)
    {
        if(cur->left->ISeleminate == true && cur->right->ISeleminate == true)
        {
            cur->ISeleminate = 1;
            cur->passEleminate();
        }
    }
}



point_t *ccell::find_vector(int minmax, int dim)
{
    hyperplane_set *hs = new hyperplane_set(dim);
    searchBound(hs);
    point_t *result = new point_t(dim + 1);
    double *obj = new double[dim];
    for(int i = 0; i < dim; ++i)
    {
        for(int j = 0; j < dim; ++j)
        {
            if(j == i)
                obj[j] = 1;
            else
                obj[j] = 0;
        }
        result->attr[i] = hs->LLP(obj, minmax);
    }

    for(int j = 0; j < dim; ++j)
        obj[j] = -1;
    result->attr[dim] = U_RANGE + hs->LLP(obj, minmax);
    delete obj;

    return result;
}


/**
 * @brief Find the score of the point w.r.t the utility vector in the partition
 * @param p
 * @return
 */
double ccell::boundforPt(point_t *p, int minmax)
{
    int dim = p->dim - 1;
    hyperplane_set *hs = new hyperplane_set(dim);
    searchBound(hs);
    double *obj = new double[dim];
    for(int i = 0; i < dim; ++i)
        obj[i] = p->attr[i] - p->attr[dim];

    double result = hs->LLP(obj, minmax);
    delete hs;
    return p->attr[dim] * U_RANGE + result;
}



void ccell::updateRankbound(node_type *n, int M, int dim, int k, point_t *wlow, point_t *wup, double SpcLow,
                            double SpcUp, int &rankLow, int &rankUp)
{
    if(n->attribute != LEAF) //internal node
    {
        double SfastLow = wlow->dot_product(n->a), SfastUp = wup->dot_product(n->b);
        if (SfastLow > SpcUp)
        {
            rankLow += n->num;
            rankUp += n->num;
        }
        else if (SpcLow <= SfastLow && SfastUp <= SpcUp)
            rankUp += n->num;
        else if (SfastUp < SpcLow)
            return;
        else
        {
            double SGlow = boundforPt(new point_t(dim, n->a), -1);
            double SGup = boundforPt(new point_t(dim, n->b), 1);
            if (SGlow > SpcUp)
            {
                rankLow += n->num;
                rankUp += n->num;
            }
            else if (SpcLow <= SGlow && SGup <= SpcUp)
                rankUp += n->num;
            else if (SGup < SpcLow)
                return;
            else
            {
                for (int i = 0; i < M - n->vacancy; i++)
                {
                    this->updateRankbound(n->ptr[i], M, dim, k, wlow, wup, SpcLow, SpcUp, rankLow, rankUp);
                    if(rankLow > k)
                        break;
                }
            }
        }

    }
    else //leaf
    {
        double SfastLow = wlow->dot_product(n->a), SfastUp = wup->dot_product(n->b);
        if (SfastLow > SpcUp)
        {
            rankLow += n->num;
            rankUp += n->num;
        }
        else if (SpcLow <= SfastLow && SfastUp <= SpcUp)
            rankUp += n->num;
        else if (SfastUp < SpcLow)
            return;
        else
        {
            double SGlow = boundforPt(new point_t(dim, n->a), -1);
            double SGup = boundforPt(new point_t(dim, n->b), 1);
            if (SGlow > SpcUp)
            {
                rankLow += n->num;
                rankUp += n->num;
            }
            else if (SGup < SpcLow)
                return;
            else
                rankUp += n->num;
        }
    }
}











