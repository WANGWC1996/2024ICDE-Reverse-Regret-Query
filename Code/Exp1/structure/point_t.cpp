#include <operation.h>
#include "point_t.h"

/**
 * @brief Constructor
 * @param dim   The number of dimensions
 */
point_t::point_t(int d)
{
    this->id = -1;
    this->dim = d;
    this->attr = new double[d];
    this->hyperID = 0;
    this->value = 0;
}

point_t::point_t(int d, double *p)
{
    this->id = -1;
    this->dim = d;
    this->attr = new double[d];
    for(int i = 0; i < d; ++i)
        attr[i] = p[i];
    this->hyperID = 0;
    this->value = 0;
}

/**
 * @brief Constructor
 * @param dim   The number of dimensions
 * @param id    The point ID
 */
point_t::point_t(int d, int id)
{
    this->id = id;
    this->dim = d;
    this->attr = new double[d];
    this->hyperID = 0;
    this->value = 0;
}


/**
 * @brief Constructor
 * @param p   The point
 */
point_t::point_t(point_t *p)
{
    this->id = p->id;
    this->dim = p->dim;
    this->attr = new double[p->dim];
    for(int i = 0;i < dim; ++i)
        attr[i] = p->attr[i];
    this->hyperID = p->hyperID;
    this->value = p->value;
    this->postiveSampleU = p->postiveSampleU;
}


/*
 * @brief Constructor
 * @param p1   point
 */
point_t::point_t(point_t *p1, point_t *p2)
{
    this->id = -1;
    this->dim = p1->dim;
    this->attr = new double[dim];
    for(int i = 0; i < dim; ++i)
        attr[i] = p1->attr[i] - p2->attr[i];
    this->hyperID = 0;
    this->value = 0;
}


/*
 * @brief Destructor
 *        delete the memory of the array
 */
point_t::~point_t()
{
    delete []attr;
}


/*
 * @brief Print the ID and coordinates for a given point
 */
void point_t::print()
{
    std::cout<< id <<"  ";
    for (int i = 0; i < dim; i++)
        std::cout<< attr[i] << " ";
    std::cout << "\n";
}


/*
 * @brief Print the coordinates for a given point
 */
void point_t::printCoordinates()
{
    cout << "(";
    for (int i = 0; i < dim - 1; i++)
        std::cout<< attr[i] << ", ";
    std::cout << attr[dim - 1] << ")\n";
}

/**
 * @brief       Check whether the point is the same as p
 * @param p     Point
 * @return      1 same
 *              0 different
 */
bool point_t::is_same(point_t *p)
{
    if(dim != p->dim)
        return false;
    for (int i = 0; i < dim; ++i)
    {
        if (attr[i] - p->attr[i] < -EQN2 || attr[i] - p->attr[i] > EQN2)
            return false;
    }
    return true;
}


/**
 * @brief   Check whether all the attribute values are 0
 * @return  -true   all attributes values are 0
 *          -false  there exists attribute value which is not 0
 */
bool point_t::is_zero()
{
    for(int i = 0; i < dim; ++i)
    {
        if(attr[i] < -EQN2 || attr[i] > EQN2)
            return false;
    }
    return true;
}


/**
 * @brief	    Calculate the dot product between two points
 * @param p     One point
 */
double point_t::dot_product(point_t *p)
{
    double result = 0;
    for(int i = 0; i < dim; i++)
    {
        result += attr[i] * p->attr[i];
    }
    return result;
}


/**
 * @brief	    Calculate the dot product between two points
 * @param v     One array
 */
double point_t::dot_product(double *v)
{
    double result = 0;
    for(int i = 0; i < dim; i++)
    {
        result += attr[i] * v[i];
    }
    return result;
}


/**
 * @brief	Calculate the subtraction between two points.
 *          Remember to release the returned point to save memory.
 * @param p The subtractor
 * @return  The subtraction(new points)
 */
point_t *point_t::sub(point_t *p)
{
    point_t* result = new point_t(dim);
    for(int i = 0; i < dim; i++)
    {
        result->attr[i] = attr[i] - p->attr[i];
    }
    return result;
}


/**
 * @brief	Calculate the addition between two points.
 *          Remember to release the returned point to save memory.
 * @param p The point
 * @return  The addition(new points)
 */
point_t *point_t::add(point_t *p)
{
    point_t* result = new point_t(dim);
    for(int i = 0; i < dim; i++)
    {
        result->attr[i] = attr[i] + p->attr[i];
    }
    return result;
}


/**
 * @brief	Scale the point
 *          Remember to release the returned point to save memory.
 * @param c The scaled coefficient
 * @return  The scaled point
 */
point_t *point_t::scale(double c)
{
    point_t* result = new point_t(dim);
    for(int i = 0; i < dim; i++)
    {
        result->attr[i] = attr[i] * c;
    }
    return result;
}


/**
 * @brief       Calculate the distance between two points
 * @param p     The points
 * @return      The distance
 */
double point_t::distance(point_t *p)
{
    double diff = 0;
    for(int i = 0; i < dim; i++)
    {
        diff += (double) pow(attr[i]/100 - p->attr[i]/100, 2);
    }
    return 100 * sqrt(diff);
}

/**
 * @brief       Calculate the distance between a points and a vector
 * @param p     The vector
 * @return      The distance
 */
double point_t::distance(double *p)
{
    double diff = 0;
    for(int i = 0; i < dim; i++)
    {
        diff += (double) pow(attr[i] - p[i], 2);
    }
    return sqrt(diff);
}


/**
 * @brief Print the result of the algorithm
 * @param out_cp    The name of the output file
 * @param name      The name of the algorithm
 * @param Qcount    The number of question asked
 * @param t1        The start time
 */
void point_t::printResult(char *name, int Qcount, timeval t1)
{
    timeval t2;
    std::ofstream out_cp("../../result.txt");
    gettimeofday(&t2, 0);
    double time_cost = (double) t2.tv_sec + (double) t2.tv_usec / 1000000 - (double) t1.tv_sec - (double) t1.tv_usec / 1000000;
    std::cout << "-----------------------------------------------------------------\n";
    printf("|%15s |%15d |%15lf |%10d |\n", name, Qcount, time_cost, id);
    std::cout << "-----------------------------------------------------------------\n";
    out_cp << Qcount << "       " << time_cost << "\n";
    out_cp.close();
}


/**
 * @brief Print the result of the algorithm
 * @param out_cp    The name of the output file
 * @param name      The name of the algorithm
 * @param Qcount    The number of question asked
 * @param t1        The start time
 * @param preTime   The preprocessing time cost
 */
void point_t::printResult(std::ofstream &out_cp, char *name, int Qcount, timeval t1, double preTime, long mem_baseline,
                          double Pcize, int type)
{
    timeval t2; gettimeofday(&t2, 0);
    double time_cost = (double) t2.tv_sec + (double) t2.tv_usec / 1000000 - (double) t1.tv_sec - (double) t1.tv_usec / 1000000;
    std::cout << "--------------------------------------------------------------------------------------------------\n";
    printf("|%15s |%15d |%15lf |%15lf |%10d |%15lf |\n", name, Qcount, preTime, time_cost - preTime, id, Pcize);// get_mem_usage() - mem_baseline);
    std::cout << "--------------------------------------------------------------------------------------------------\n";
    if(type == 2)
        out_cp << Qcount << "       " << preTime << "       " << time_cost - preTime << "      " <<
        Pcize << "\n"; //"    " << get_mem_usage() - mem_baseline << "\n";
}

/**
 * @brief Check if the point dominates p
 * @param p     The point
 * @return      1: dominate
 *              0: not dominate
 */
bool point_t::dominate(point_t *p)
{
    for(int i = 0; i < dim; ++i)
    {
        if(attr[i] < p->attr[i])
            return false;
    }
    return true;
}


/**
 * @brief Check if the point*(1-epsilon) dominates p
 * @param p         The point
 * @param epsilon   The parameter
 * @return          1: dominate
 *                  0: not dominate
 */
bool point_t::epsilonDominateformer(point_t *p, double epsilon)
{
    for(int i = 0; i < dim; ++i)
    {
        if(attr[i] * (1 - epsilon) < p->attr[i])
            return false;
    }
    return true;
}


/**
 * @brief Check if the point is dominated by p*(1-epsilon)
 * @param p         The point
 * @param epsilon   The parameter
 * @return          1: is dominated
 *                  0: is not dominated
 */
bool point_t::epsilonDominatelatter(point_t *p, double epsilon)
{
    for(int i = 0; i < dim; ++i)
    {
        if(attr[i] < p->attr[i] * (1-epsilon))
            return false;
    }
    return true;
}


/**
 * @brief Check if the two points are covered by the same positive half-spaces
 * @param p     The point
 * @return      1 have the same positive half-spaces
 *              0 do not have the same positive half-spaces
 */
bool point_t::existPositiveHalf(point_t *p)
{
    int num1 = positiveHalf.size(), num2 = p->positiveHalf.size();

    for(int i = 0; i < num1; ++i)
    {
        bool exists = false;
        for(int j = 0; j < num2; ++j)
        {
            if(positiveHalf[i] == p->positiveHalf[j])
            {
                exists = true;
                break;
            }
        }
        if(!exists)
            return false;
    }

    return true;
}




/**
 * @brief Check if the two points are covered by the same positive half-spaces
 * @param p     The point
 * @return      1 have the same positive half-spaces
 *              0 do not have the same positive half-spaces
 */
bool point_t::existNegativeHalf(point_t *p)
{
    int num1 = negativeHalf.size(), num2 = p->negativeHalf.size();

    for(int i = 0; i < num1; ++i)
    {
        bool exists = false;
        for (int j = 0; j < num2; ++j)
        {
            if (negativeHalf[i] == p->negativeHalf[j])
            {
                exists = true;
                break;
            }
        }
        if (!exists)
            return false;
    }

    return true;
}








/**
 * @brief Compare the normalized hyper-plane of the points.
 * @param p     The other compared point
 * @return
 */
int point_t::q_dominate(point_t *p)
{
    int pppp = 0;
    while(normlizedHyper->attr[pppp] == p->normlizedHyper->attr[pppp])
        ++pppp;

    if(normlizedHyper->attr[pppp] > p->normlizedHyper->attr[pppp])
    {
        for(int i = pppp + 1; i < dim; ++i)
        {
            if(normlizedHyper->attr[i] < p->normlizedHyper->attr[i])
                return 0;
        }
        return 1;
    }
    else
    {
        for(int i = pppp + 1; i < dim; ++i)
        {
            if(normlizedHyper->attr[i] > p->normlizedHyper->attr[i])
                return 0;
        }
        return -1;
    }
}


/**
 * @brief Check the normalized hyper-plane, which is used for pruning points
 * @param q The query point
 */
void point_t::setNormalizedHyper(point_t *q, double epsilon)
{
    normlizedHyper = new point_t(dim);
    double sum = 0;
    for (int j = 0; j < dim; j++)
    {
        normlizedHyper->attr[j] = (1 - epsilon) * attr[j] - q->attr[j];
        sum += normlizedHyper->attr[j] * normlizedHyper->attr[j];
    }
    sum = sqrt(sum);
    for(int j = 0; j < dim; ++j)
        normlizedHyper->attr[j] /= sum;

    //print();
    //normlizedHyper->print();
}


/**
 * @brief Check if the two points are covered by the same hyper-plane
 * @param p
 * @return
 */
bool point_t::same_cover(point_t *p)
{
    if(positiveHalf.size() != p->positiveHalf.size())
        return false;

    for(int i = 0; i < positiveHalf.size(); ++i)
    {
        if(positiveHalf[i] != p->positiveHalf[i])
            return false;
    }

    return true;
}








