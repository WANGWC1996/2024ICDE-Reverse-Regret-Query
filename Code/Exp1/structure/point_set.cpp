#include "point_set.h"


/**
 * @brief Constructor
 */
point_set::point_set(){}

/**
 * @brief Constructor
 *        Create a point set the same as p_set, all the points are re-created
 * @param p_set     Point set
 */
point_set::point_set(point_set *p_set)
{
    int dim = p_set->points[0]->dim, num = p_set->points.size();
    point_t *p;
    for (int i = 0; i < num; i++)
    {
        p = new point_t(dim, p_set->points[i]->id);
        for (int j = 0; j < dim; j++)
            p->attr[j] = p_set->points[i]->attr[j];
        p->hyperID = p_set->points[i]->hyperID;
        points.push_back(p);
    }

}

/**
 * @brief Constructor
 *        Record all the points in the input file to the point set
 * @param input     Name of the data file.
 */
point_set::point_set(const char* input)
{
    FILE* c_fp;
    char filename[MAX_FILENAME_LENG];
    sprintf(filename, "../data/%s", input);
    printf("%s\n", filename);
    if ((c_fp = fopen(filename, "r")) == NULL)
    {
        fprintf(stderr, "Cannot open the data file %s.\n", filename);
        exit(0);
    }

    int num, dim;
    point_t* p;
    fscanf(c_fp, "%i%i", &num, &dim);

    // read points line by line
    for (int i = 0; i < num; i++)
    {
        p = new point_t(dim, i);
        for (int j = 0; j < dim; j++)
            fscanf(c_fp, "%lf", &p->attr[j]);
        points.push_back(p);
    }
    fclose(c_fp);
}

/**
 *@brief  Destructor
 *        Delete the points in the array
 */
point_set::~point_set()
{
    int i = points.size();
    point_t *p;
    while(i>0)
    {
        p = points[i-1];
        points.pop_back();
        delete p;
        i--;
    }
    points.clear();
}

/*
 *	For debug purpose, print all the points in the set
 */
void point_set::print()
{
    for (int i = 0; i < points.size(); i++)
        points[i]->print();
    printf("\n");
}

/**
 * @brief           Reload the points Randomly
 *                  Define "RandRate" to control how many point reinserted
 * @param p_set     The returned dataset where the points are inserted randomly
 */
void point_set::random(double RandRate)
{
    int size = points.size();
    //reinsert
    for (int i = 0; i < size * RandRate; i++)
    {
        int n = ((int) rand()) % size;
        point_t *p = points[n];
        points.erase(points.begin() + n);
        points.push_back(p);
    }
}

/**
 * @brief       Sort points based on their distance to e
 * @param e     The expected point
 * @return      The point set which contains all the point in order
 */
point_set* point_set::sort(point_t *e)
{
    int size = points.size();
    if(size <=0)
        return NULL;
    point_set *return_set = new point_set();
    return_set->points.push_back(points[0]);
    for (int i = 1; i < size; i++)
    {
        double v0 = points[i]->distance(e);
        int left = 0, right = return_set->points.size() - 1;
        //find the place for p_set[i] in return_point and record the place index in "left"
        while (left <= right)
        {
            int middle = (left + right) / 2;
            double v = return_set->points[middle]->distance(e);
            if (v0 < v)
            {
                right = middle - 1;
            }
            else
            {
                left = middle + 1;
            }
        }
        return_set->points.insert(return_set->points.begin() + left, points[i]);
    }
    /*
    for(int i=0; i<return_set->points.size();i++)
    {
        return_set->points[i]->print();
    }
    */
    return return_set;
}


/**
 * @brief   Write the dataset to the txt file
 * @param   fileName  The name of the txt file
 */
void point_set::write(std::string fileName)
{
    std::ofstream wPtr;
    wPtr.open(fileName, std::ios::out);
    wPtr.setf(std::ios::fixed, std::ios::floatfield);  // set as fixed model
    wPtr.precision(6);  // set precision to 6


    int size = points.size(), dim = points[0]->dim;
    // write the points
    wPtr << size << "   " << dim << " \n";//record the offset as one dimension
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            wPtr << points[i]->attr[j] <<" ";
        }
        wPtr <<"\n";
    }
    wPtr.close();
}

/**
 * @param Delete point p in the point set
 * @param p The point
 */
void point_set::prunePt(point_t *p)
{
    for(int i = 0; i < points.size(); ++i)
    {
        if(points[i]->id == p->id)
        {
            points.erase(points.begin() + i);
            return;
        }
    }
}


/**
 * @brief Find the nearest k points w.r.t. e
 * @param e  The expected point
 * @param k  Parameter k
 * @return   The nearest k points
 */
point_set *point_set::findTopK(point_t *u, int k)
{
    point_set *topSet = new point_set();
    std::vector<double> valueSet;
    //set the initial k points
    topSet->points.push_back(points[0]);
    valueSet.push_back(points[0]->dot_product(u));
    for (int i = 1; i < k; i++)
    {
        double value = points[i]->dot_product(u);
        int j = 0;
        while (j < valueSet.size() && value < valueSet[j])
            j++;
        topSet->points.insert(topSet->points.begin() + j, points[i]);
        valueSet.insert(valueSet.begin() + j, value);
    }

    //insert the rest points
    for (int i = k; i < points.size(); i++)
    {
        double value = points[i]->dot_product(u);
        for (int j = 0; j < k; ++j)
        {
            if (value > valueSet[j])
            {
                topSet->points.insert(topSet->points.begin() + j, points[i]);
                valueSet.insert(valueSet.begin() + j, value);
                topSet->points.pop_back();
                valueSet.pop_back();
                break;
            }
        }
    }
    return topSet;
}





void point_set::printResult(std::ofstream &out_cp, char *name, int Qcount, timeval t1, double preTime, long mem_baseline,
                          double Pcize, int type)
{
    timeval t2; gettimeofday(&t2, 0);
    double time_cost = (double) t2.tv_sec + (double) t2.tv_usec / 1000000 - (double) t1.tv_sec - (double) t1.tv_usec / 1000000;
    std::cout << "--------------------------------------------------------------------------------------------------\n";
    printf("|%15s |%15d |%15lf |%15lf |%10d |%15lf |\n", name, Qcount, preTime, time_cost - preTime, points[0]->id, Pcize);// get_mem_usage() - mem_baseline);
    for(int i = 1; i < points.size(); ++i)
        printf("|%15s |%15s |%15s |%15s |%10d |%15s |\n", "-", "-", "-", "-", points[i]->id, "-");// get_mem_usage() - mem_baseline);
    std::cout << "--------------------------------------------------------------------------------------------------\n";
    if(type == 2)
        out_cp << Qcount << "       " << preTime << "       " << time_cost - preTime << "      " <<
               Pcize << "\n"; //"    " << get_mem_usage() - mem_baseline << "\n";
}





/**
 * @brief Build the domination relation between each pair of points
 */
void point_set::buildRelation()
{
    for(int i = 0; i < points.size() - 1; ++i)
    {
        for(int j = i + 1; j < points.size(); ++j)
        {
            if(points[i]->dominate(points[j]))
            {
                points[i]->dominating.push_back(points[j]);
                points[j]->dominated.push_back(points[i]);
            }
            else if (points[j]->dominate(points[i]))
            {
                points[j]->dominating.push_back(points[i]);
                points[i]->dominated.push_back(points[j]);
            }
        }
    }
}


/**
 * @brief Delete the points which are dominated by >=k points
 */
void point_set::refineBasedonRelation(int k)
{
    int num = points.size(), index = 0;
    for(int i = 0; i < num; ++i)
    {
        if(points[index]->dominated.size() >= k)
            points.erase(points.begin() + index);
        else
        {
            points[index]->dominating.clear();
            points[index]->dominated.clear();
            ++index;
        }
    }
}


/**
 * @brief Find the points which is q_dominated by the fewest points
 * @return
 */
int point_set::findMinDominted()
{
    int mindominated = 999999, maxpostiveSampleU = -1;
    int pindex =0;
    for(int i = 0; i < points.size(); ++i)
    {
        if(points[i]->value == -1)
        {
            points.erase(points.begin() + i);
            --i;
        }
        else //(points[i]->value == 0)
        {
            int mm = points[i]->dominated.size();
            if(mm < mindominated)
            {
                mindominated = points[i]->dominated.size();
                //maxpostiveSampleU = points[i]->postiveSampleU;
                pindex = i;
            }
        }
    }
    return  pindex;
}




/**
 * @brief Build the cluster for the sampled utility vector
 *        The nearby utility vector are combined together
 * @return Do not cluster the points together
 */
bool point_set::findCluster()
{
    if(points.size() <= 0)
        return false;
    int dim = points[0]->dim;
    for(int i = 0; i < points.size(); ++i)
        points[i]->clusterID = i;

    for(int d = 0; d < dim; ++d)
    {
        for(int i = 0; i < points.size(); ++i)
        {
            for(int j = 0; j < points.size(); ++j)
            {
                if(points[i]->clusterID != points[j]->clusterID &&
                   (points[i]->attr[d] - points[j]->attr[d] == -100
                    || points[i]->attr[d] - points[j]->attr[d] == 100))
                {
                    if(points[i]->clusterID < points[j]->clusterID)
                    {
                        points[j]->clusterID = points[i]->clusterID;
                        for(int s = 0; s < points.size(); ++s)
                        {
                            if(points[s]->clusterID == points[j]->clusterID)
                                points[s]->clusterID = points[i]->clusterID;
                        }
                    }
                    else if (points[j]->clusterID < points[i]->clusterID)
                    {
                        points[i]->clusterID = points[j]->clusterID;
                        for(int s = 0; s < points.size(); ++s)
                        {
                            if(points[s]->clusterID == points[i]->clusterID)
                                points[s]->clusterID = points[j]->clusterID;
                        }
                    }
                }
            }
        }
    }
}



/**
 * @brief Print the information related to the clusters
 */
void point_set::printForCluster()
{
    std::cout << points.size() << "\n";
    for(int i = 0; i < points.size(); ++i)
    {
        points[i]->print();
        std::cout << "Positve: " << points[i]->positiveHalf.size() <<
                  "   Negative: " << points[i]->negativeHalf.size() <<
                  "   Both: " << points[i]->bothHalf.size() <<
                  "   ClusterID: " << points[i]->clusterID << "\n";
    }
}

/**
 * @brief Set the normalized norm of the hyper-plane
 * @param q
 * @param epsilon
 */
void point_set::setNormalizedHyper(point_t *q, double epsilon)
{
    for(int i = 0; i < points.size(); ++i)
        points[i]->setNormalizedHyper(q, epsilon);
}





/**
 * @brief find the skyline point
 * @param SL
 */
void point_set::skyline(point_set *SL)
{
    for(int i = 0; i < points.size(); ++i)
    {
        bool isdominated = false;
        for(int j = 0 ; j < SL->points.size(); ++j)
        {
            if(SL->points[j]->dominate(points[i]))
            {
                isdominated = true;
                break;
            }
        }
        if(!isdominated)
        {
            for(int j = 0; j < SL->points.size(); ++j)
            {
                if(points[i]->dominate(SL->points[j]))
                {
                    SL->points.erase(SL->points.begin() + j);
                    --j;
                }
            }
            SL->points.push_back(points[i]);
        }
    }
}

/**
 * @brief Find all the points which dominated the points in SL
 * @param SL
 */
void point_set::buildrelation(point_set *SL, std::vector<point_set*> &DG)
{
    for(int i = 0; i < SL->points.size(); ++i)
    {
        DG.push_back(new point_set());
        for(int j = 0; j < points.size(); ++j)
        {
            if(points[j]->id != SL->points[i]->id && points[j]->dominate(SL->points[i]))
                DG[i]->points.push_back(points[j]);
        }
    }
}


/**
 * @brief Check whether there exists a point which dominate p
 * @param p     The point
 * @return      1 There exists a point dominating p
 *             -1 There do not exist a point which dominate p
 */
bool point_set::dominate(point_t *p)
{
    for(int i = 0; i < points.size(); ++i)
    {
        if(points[i]->dominate(p))
            return true;
    }
    return false;
}


/**
 * @brief The union of two point sets
 * @param pSet  The point set
 */
void point_set::add(point_set *pSet)
{
    for(int i = 0; i < pSet->points.size(); ++i)
    {
        bool exists = false;
        for(int j = 0; j < points.size(); ++j)
        {
            if(pSet->points[i]->id == points[j]->id)
            {
                exists = true;
                break;
            }
        }
        if(!exists)
            points.push_back(pSet->points[i]);
    }
}

/**
 * @brief The point set which contains the points in A but not in B
 * @param pSet      The point set B
 */
void point_set::minus(point_set *pSet)
{
    for(int i = 0; i < points.size(); ++i)
    {
        bool exists = false;
        for(int j = 0; j < pSet->points.size(); ++j)
        {
            if(points[i]->id == pSet->points[j]->id)
            {
                exists = true;
                break;
            }
        }
        if(exists)
        {
            points.erase(points.begin() + i);
            --i;
        }
    }
}





/**
 * @brief Refine the dataset by deleting the points which dominate q or are dominated by q
 * @param q             The query point
 * @param epsilon       The regret bound
 */
int point_set::refind_with_queryPt(point_t *q, int k, double epsilon)
{
    for(int i = 0; i < points.size(); ++i)
    {
        if(q->epsilonDominatelatter(points[i], epsilon)) //check q is dominated by the p
        {
            points[i]->value = -1;
            points.erase(points.begin() + i);
            i--;
        }
        else if(points[i]->epsilonDominateformer(q, epsilon)) //check q dominates p
        {
            points[i]->value = -1;
            points.erase(points.begin() + i);
            i--; k--;
            if(k <= 0) //There are k points which epsilon-dominate q
            {
                std:: cout << "The query point does not satisfy the regret requirement for any utility function.\n";
                return k;
            }
        }
    }
}


/**
 * @brief Calculate the interval of the sampled utility vector.
 * @param q             The query point
 * @param epsilon       The regret bound
 * @param error         The error
 * @return
 */
double point_set::calculate_segment(point_t *q, double epsilon, double error)
{
    double interval = 0;
    for(int i = 0; i < points.size(); ++i)
    {



    }


    return 0;
}



/**
 * @brief Check if the point set covers the ps
 * @param ps The other point set
 * @return
 */
bool point_set::cover(point_set *ps)
{
    for(int i = 0; i < ps->points.size(); ++i)
    {
        bool exist = false;
        for(int j= 0; j < points.size(); ++j)
        {
            if(ps->points[i]->id == points[j]->id)
            {
                exist = true;
                break;
            }
        }
        if(!exist)
            return false;
    }
    return true;
}





















