#include "halfspace_tree.h"




/**
 * @brief Constructor
 */
hp_node::hp_node()
{
    numPHalfspace = 0;
    set = new hyperplane_set();
    pt = NULL;
    ng = NULL;
}


/**
 * @brief Constructor
 */
hp_node::hp_node(hp_node *org)
{
    numPHalfspace = 0;
    set = new hyperplane_set();
    origin = org;
    pt = NULL;
    ng = NULL;
}

/**
 * @brief Constructor
 */
hp_node::hp_node(int dim)
{
    numPHalfspace = 0;
    set = new hyperplane_set(dim);
    origin = NULL;
    pt = NULL;
    ng = NULL;
}


/**
 * @brief Constructor
 */
hp_node::hp_node(hyperplane_set *hset)
{
    numPHalfspace = 0;
    set = hset;
    pt = NULL;
    ng = NULL;
}


/**
 * @brief Insert a hyper-plane into a node with Lazy computation
 * @param h
 */
void hp_node::insertLazy(hyperplane *h, int k)
{
    int relation = set->check_relation_fast(h);
    if (relation == 1)
    {
        ++numPHalfspace;
        if(numPHalfspace < k)
        {
            if (pt == NULL && ng == NULL)
            {
                if (numPHalfspace + unprocessedHyper.size() >= k)
                {
                    h = unprocessedHyper[unprocessedHyper.size() - 1];
                    unprocessedHyper.pop_back();
                    insertLazy(h, k);
                }
            }
            else
            {
                if (pt->numPHalfspace < k)
                    pt->increase_numPHalfspace(k);
                if (ng->numPHalfspace < k)
                    ng->increase_numPHalfspace(k);
            }
        }
        else
        {
            if(pt != NULL)
            {
                delete pt;
                pt = NULL;
            }
            if(ng != NULL)
            {
                delete ng;
                ng = NULL;
            }
            if(origin != NULL && origin->origin != NULL)
            {
                if (origin->origin->pt == origin)
                {
                    if (origin->pt == this)
                        origin->origin->pt = origin->ng;
                    else
                        origin->origin->pt = origin->pt;
                } else if (origin->origin->ng == origin)
                {
                    if (origin->pt == this)
                        origin->origin->ng = origin->ng;
                    else
                        origin->origin->ng = origin->pt;
                }
            }
            updateThreshold(k);
        }
    }
    else if (relation == 0)
    {
        if (pt == NULL && ng == NULL)
        {
            unprocessedHyper.push_back(h);
            if(numPHalfspace + unprocessedHyper.size() >= k)
            {
                /*
                bool needSplit = true;
                int rrr = set->check_relation_fast(unprocessedHyper[0]);
                while (rrr != 0 && needSplit)
                {
                    unprocessedHyper.erase(unprocessedHyper.begin());
                    if (rrr == 1)
                    {
                        ++numPHalfspace;
                        rrr = set->check_relation_fast(unprocessedHyper[0]);
                    }
                    else if (rrr == -1)
                        needSplit = false;

                }
                 */
                bool needSplit = true;
                for(int i = 0; i < unprocessedHyper.size(); ++i)
                {
                    int rrr = set->check_relation_fast(unprocessedHyper[i]);
                    if (rrr != 0)
                    {
                        unprocessedHyper.erase(unprocessedHyper.begin() + i);
                        --i;
                        if (rrr == 1)
                            ++numPHalfspace;
                        else if (rrr == -1)
                            needSplit = false;
                    }
                }

                if(needSplit)
                {
                    pt = new hp_node(this);
                    pt->numPHalfspace = numPHalfspace + 1;
                    pt->ID = 2 * ID;
                    ng = new hp_node(this);
                    ng->numPHalfspace = numPHalfspace;
                    ng->ID = 2 * ID + 1;
                    set->divide(unprocessedHyper[0], pt->set, ng->set);
                    dividePt = unprocessedHyper[0]->p_1;
                    for (int i = 1; i < unprocessedHyper.size(); ++i)
                    {
                        pt->unprocessedHyper.push_back(unprocessedHyper[i]);
                        ng->unprocessedHyper.push_back(unprocessedHyper[i]);
                    }
                    unprocessedHyper.clear();
                    if (pt->numPHalfspace < k && pt->numPHalfspace + pt->unprocessedHyper.size() >= k)
                    {
                        h = pt->unprocessedHyper[pt->unprocessedHyper.size() - 1];
                        pt->unprocessedHyper.pop_back();
                        pt->insertLazy(h, k);
                    }
                }
            }

        }
        else
        {
            //dividePt->normlizedHyper->print();
            //h->p_1->normlizedHyper->print();
            if (dividePt->q_dominate(h->p_1) == 1)
            {
                if (pt->numPHalfspace < k)
                    pt->insertLazy(h, k);
            }
            else
            {
                if (pt->numPHalfspace < k)
                    pt->insertLazy(h, k);
                if (ng->numPHalfspace < k)
                    ng->insertLazy(h, k);
            }
        }
    }
}



/**
 * @brief Insert a hyper-plane into a node
 * @param h
 */
void hp_node::insert(hyperplane *h, int k)
{
    int relation = set->check_relation(h);
    if (relation == 1)
    {
        ++numPHalfspace;
        if(numPHalfspace < k)
        {
            if (pt != NULL && pt->numPHalfspace < k)
                pt->increase_numPHalfspace(k);
            if (ng != NULL && ng->numPHalfspace < k)
                ng->increase_numPHalfspace(k);
        }
        else
        {
            if(origin != NULL && origin->origin != NULL)
            {
                if (origin->origin->pt == origin)
                {
                    if (origin->pt == this)
                        origin->origin->pt = origin->ng;
                    else
                        origin->origin->pt = origin->pt;
                }
                else if (origin->origin->ng == origin)
                {
                    if (origin->pt == this)
                        origin->origin->ng = origin->ng;
                    else
                        origin->origin->ng = origin->pt;
                }
            }
            updateThreshold(k);
        }
    }
    else if (relation == 0)
    {
        if (pt == NULL && ng == NULL)
        {
            pt = new hp_node();
            pt->numPHalfspace = numPHalfspace + 1;
            ng = new hp_node();
            ng->numPHalfspace = numPHalfspace;
            set->divide(h, pt->set, ng->set);
            dividePt = h->p_1;
            //pt->set->print();
            //ng->set->print();
        }
        else
        {
            if (pt->numPHalfspace < k)
                pt->insert(h, k);
            if (ng->numPHalfspace < k)
                ng->insert(h, k);
        }
    }
}


/**
 * @brief Insert a hyper-plane into a node
 * @param h
 */
void hp_node::insert_fast(hyperplane *h, int k)
{
    int relation = set->check_relation_fast(h);
    if (relation == 1)
    {
        ++numPHalfspace;
        if(numPHalfspace < k)
        {
            if (pt != NULL && pt->numPHalfspace < k)
                pt->increase_numPHalfspace(k);
            if (ng != NULL && ng->numPHalfspace < k)
                ng->increase_numPHalfspace(k);
        }
    }
    else if (relation == 0)
    {
        if (pt == NULL && ng == NULL)
        {
            pt = new hp_node();
            pt->numPHalfspace = numPHalfspace + 1;
            ng = new hp_node();
            ng->numPHalfspace = numPHalfspace;
            set->divide(h, pt->set, ng->set);
            dividePt = h->p_1;
            //pt->set->print();
            //ng->set->print();
        }
        else
        {
            if (pt->numPHalfspace < k)
                pt->insert_fast(h, k);
            if (ng->numPHalfspace < k)
                ng->insert_fast(h, k);
        }
    }
}




/**
 * @brief Print the partitions that fulfill the requirements
 * @param k     Parameter k
 */
void hp_node::print_useful_partition(int k)
{
    if(pt == NULL && ng == NULL)
    {
        std::cout << "Partition " << numPHalfspace << "   " << unprocessedHyper.size() << "\n";
        set->print();
    }
    else
    {
        if (pt != NULL && pt->numPHalfspace < k)
            pt->print_useful_partition(k);
        if (ng != NULL && ng->numPHalfspace < k)
            ng->print_useful_partition(k);
    }
}

/**
 * @brief Incresae the numPHalfspace for the whole sub-tree
 */
void hp_node::increase_numPHalfspace(int k)
{
    ++numPHalfspace;
    if (numPHalfspace < k)
    {
        if (pt == NULL && ng == NULL)
        {
            if (numPHalfspace + unprocessedHyper.size() >= k)
            {
                hyperplane *h = unprocessedHyper[unprocessedHyper.size() - 1];
                unprocessedHyper.pop_back();
                insertLazy(h, k);
            }
        }
        else
        {
            if (pt->numPHalfspace < k)
                pt->increase_numPHalfspace(k);
            if (ng->numPHalfspace < k)
                ng->increase_numPHalfspace(k);
        }
    }
    else
    {
        if(pt != NULL)
        {
            delete pt;
            pt = NULL;
        }
        if(ng != NULL)
        {
            delete ng;
            ng = NULL;
        }
        updateThreshold(k);
    }

}


/**
 * @brief Print the information of the node
 */
void hp_node::print()
{
    std::cout << "Node: " << ID <<"   ";
    if(pt == NULL && ng == NULL)
        std::cout << "Leave \n";
    else
        std::cout << "Internal Node\n";
    std::cout << numPHalfspace << "   " << unprocessedHyper.size() << "   " << sampledU.size() << "\n";
    set->print();
}

/**
 * @brief If both children has >k positive half-space, then the father node also has >k positive half-spaces
 */
void hp_node::updateThreshold(int k)
{
    if(origin != NULL && origin->pt->numPHalfspace >= k && origin->ng->numPHalfspace >= k)
    {
        origin->numPHalfspace = k;
        origin->updateThreshold(k);
    }
}


/**
 * @brief Destructor
 */
hp_node::~hp_node()
{
    if(pt != NULL)
        delete pt;
    if(ng != NULL)
        delete ng;
}


/**
 * @Constrcutor
 */
halfspace_tree::halfspace_tree(int dim)
{
    root = new hp_node(dim);
    root->ID = 1;
    root->set->setconvexhull();
}


/**
 * @Constrcutor
 */
halfspace_tree::halfspace_tree(hyperplane_set *hset)
{
    root = new hp_node(hset);
    root->ID = 1;
    root->origin = NULL;
}


/**
 * @brief Constructor
 * @param pps
 * @param q
 * @param epsilon
 * @param k
 * @param totalSampledV
 */
halfspace_tree::halfspace_tree(point_set* pps, point_t *q, double epsilon, int k, point_set* totalSampledV, std::vector<hp_node*> &processedNode)
{
    int pindex = pps->findMinDominted(), count = pps->points.size();
    hp_node *currentHN;
    root = new hp_node();
    root->ID = 1;
    root->sure = true;
    root->sampledU = totalSampledV->points;
    processedNode.push_back(root);
    int NNN;

    for(int i = 0; i < count; ++i)
    {
        if(processedNode.size() == NNN)
            break;
        NNN = processedNode.size();
        std::cout << i << "   " << NNN << "\n";
        hyperplane *h = new hyperplane(pps->points[pindex], q, epsilon);

        for(int j = 0; j < NNN; ++j)
        {
            currentHN = processedNode.front();
            processedNode.erase(processedNode.begin());
            if(currentHN->numPHalfspace < k)
            {
                if(currentHN->sure)
                {
                    currentHN->pt = new hp_node();
                    currentHN->pt->numPHalfspace = currentHN->numPHalfspace + 1;
                    currentHN->pt->ID = 2 * currentHN->ID;
                    currentHN->ng = new hp_node();
                    currentHN->ng->numPHalfspace = currentHN->numPHalfspace;
                    currentHN->ng->ID = 2 * currentHN->ID + 1;
                    currentHN->dividePt = pps->points[pindex];
                    for (int s = 1; s < currentHN->involvedHyper.size(); ++s)
                    {
                        currentHN->pt->involvedHyper.push_back(currentHN->involvedHyper[s]);
                        currentHN->ng->involvedHyper.push_back(currentHN->involvedHyper[s]);
                    }
                    currentHN->pt->involvedHyper.push_back(new hyperplane(h, -1));
                    currentHN->ng->involvedHyper.push_back(h);


                    for (int s = 0; s < currentHN->sampledU.size(); ++s)
                    {
                        double dis = h->check_distance_withSign(currentHN->sampledU[s]);
                        if (dis < 0)
                            currentHN->ng->sampledU.push_back(currentHN->sampledU[s]);
                        else
                            currentHN->pt->sampledU.push_back(currentHN->sampledU[s]);
                    }
                    if (currentHN->pt->sampledU.size() > 0 && currentHN->ng->sampledU.size() > 0)
                    {
                        currentHN->pt->sure = true;
                        currentHN->ng->sure = true;
                    }
                    else
                    {
                        currentHN->pt->sure = false;
                        currentHN->ng->sure = false;
                    }
                    processedNode.push_back(currentHN->pt);
                    processedNode.push_back(currentHN->ng);
                }
                else
                {
                    currentHN->unprocessedHyper.push_back(h);
                    processedNode.push_back(currentHN);
                }
            }

        }
        pps->points[pindex]->value = -1;
        pindex = pps->findMinDominted();
        //print();

    }

}





/**
 * @brief Insert a hyper-plane into the tree
 * @param h
 */
void halfspace_tree::insert(hyperplane *h, int k)
{
    if(root->numPHalfspace < k)
        root->insert(h, k);
}



/**
 * @brief Insert a hyper-plane into the tree
 * @param h
 */
void halfspace_tree::insert_fast(hyperplane *h, int k)
{
    if(root->numPHalfspace < k)
        root->insert_fast(h, k);
}


/**
 * @brief Insert a hyper-plane into the tree
 * @param h
 */
void halfspace_tree::insertLazy(hyperplane *h, int k)
{
    if(root->numPHalfspace < k)
        root->insertLazy(h, k);
}


/**
 * @brief Print the partitions that fulfill the requirements
 * @param k     Parameter k
 */
void halfspace_tree::print_useful_partition(int k)
{
    if(root->numPHalfspace <= k)
        root->print_useful_partition(k);
}

/**
 * @brief Print the tree
 */
void halfspace_tree::print()
{
    std::cout << "TREE: " << "\n";
    std::vector<hp_node*> L;
    L.push_back(root);
    while(L.size() > 0)
    {
        L[0]->print();
        if(L[0]->pt != NULL && L[0]->ng != NULL)
        {
            L.push_back(L[0]->pt);
            L.push_back(L[0]->ng);
        }
        L.erase(L.begin());
    }
}





