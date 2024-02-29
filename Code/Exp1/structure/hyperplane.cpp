#include <iomanip>
#include "hyperplane.h"

/**
 * @brief Constructor
 */
hyperplane::hyperplane()
{
    p_1 = NULL;
    p_2 = NULL;
}

/**
 * @brief       Constructor
 * @param dim   The number of dimensions of the hyperplane
 */
hyperplane::hyperplane(int dim)
{
    this->dim = dim;
    this->norm = new double[dim];
    this->offset = 0;
    p_1 = NULL;
    p_2 = NULL;
    type = -1;
}


/**
 * @brief Constructor
 * @param h The hyperplane
 */
hyperplane::hyperplane(hyperplane *h)
{
    dim = h->dim;
    norm = new double[dim];
    for (int j = 0; j < dim; j++)
        norm[j] = h->norm[j];
    offset = h->offset;
    normLength = h->normLength;
    p_1 = h->p_1;
    p_2 = h->p_2;
    direction = h->direction;
    type = -1;
}

/**
 * @brief Constructor
 * @param h The hyperplane
 */
hyperplane::hyperplane(hyperplane *h, int dir)
{
    dim = h->dim;
    norm = new double[dim];
    if(dir == 1)
    {
        for (int j = 0; j < dim; j++)
            norm[j] = h->norm[j];
        offset = h->offset;
        direction = dir;
    }
    else if (dir == -1)
    {
        for (int j = 0; j < dim; j++)
            norm[j] = -h->norm[j];
        offset = -h->offset;
        direction = -dir;
    }
    normLength = h->normLength;
    p_1 = h->p_1;
    p_2 = h->p_2;
    type = 1;
}

/**
 * @brief Constructor
 *        Guarantee that n has at least one element
 * @param n         The norm vector
 * @param offset    The offset
 */
hyperplane::hyperplane(int dim, double *n, double offset)
{
    this->dim = dim;
    norm = new double[dim];
    for (int j = 0; j < dim; j++)
        norm[j] = n[j];
    this->offset = offset;
    normLength = 0;
    for(int i = 0; i < dim; ++i)
        normLength += norm[i] * norm[i];
    normLength = sqrt(normLength);
    p_1 = NULL;
    p_2 = NULL;
}


/**
 * @brief Constructor
 * @param p1    The first point
 * @param p2    The second point
 * @param epsilon   Control the first point
 * @param off   The offset
 */
hyperplane::hyperplane(point_t *p1, point_t *p2, double epsilon)
{
    //note that the dimension of the hyper-plane is 1 dimension smaller than that of the point
    this->dim = p1->dim - 1;
    norm = new double[dim];
    for (int j = 0; j < dim; j++)
        norm[j] = (1 - epsilon) * (p1->attr[j] - p1->attr[dim]) - (p2->attr[j] - p2->attr[dim]);
    this->offset = U_RANGE * ((1 - epsilon) * p1->attr[dim] - p2->attr[dim]);
    normLength = 0; //the length of the norm
    for(int i = 0; i < dim; ++i)
        normLength += norm[i] * norm[i];
    normLength = sqrt(normLength);
    p_1 = p1;
    p_2 = p2;
    direction = -1;
    type = -1;
}




/**
 * @brief Constructor
 * @param d     The number of dimensionality
 * @param p1    The first point
 * @param p2    The second point
 * @param epsilon   Control the first point
 * @param off   The offset
 */
hyperplane::hyperplane(int d, double *p1, double *p2, double epsilon)
{
    this->dim = d;
    norm = new double[dim];
    for (int j = 0; j < dim; j++)
        norm[j] = (1 - epsilon) * (p1[j] - p1[dim]) - (p2[j] - p2[dim]);
    this->offset = U_RANGE * ((1 - epsilon) * p1[dim] - p2[dim]);
    normLength = 0;//the length of the norm
    for(int i = 0; i < dim; ++i)
        normLength += norm[i] * norm[i];
    normLength = sqrt(normLength);
    p_1 = NULL;
    p_2 = NULL;
    direction = -1;
    type = -1;
}



/**
 * @brief Destructor
 *        Delete the array of norm
 */
hyperplane::~hyperplane()
{
    delete []norm;
}

/**
 * @brief  Print the information of the hyperplane
 */
void hyperplane::print()
{
    for (int i = 0; i < dim; i++)
    {
        std::cout << std::setprecision(10) << norm[i] << " ";
    }
    std::cout << offset << "\n";

}

/**
 * @brief Check the position of the point w.r.t. the hyperplane
 * @param p The point
 * @return   1 The point is in h+
 *          -1 The point is in h-
 */
int hyperplane::check_position(point_t *p)
{
    double sum = 0;
    for(int i = 0; i < dim; ++i)
        sum += p->attr[i] * norm[i];
    sum += offset;
    if (sum >= EQN2)
        return 1;
    else if (sum <= -EQN2)
        return -1;
    else
        return 0;
}

/**
 * @brief Check the position of the point w.r.t. the hyperplane
 * @param p The point
 * @return   1 The point is in h+
 *           0 The point is not in h+
 */
int hyperplane::check_positive(point_t *p)
{
    double sum = 0;
    for(int i = 0; i < dim; ++i)
        sum += p->attr[i] * norm[i];
    sum += offset;
    if(sum >= -EQN3)
        return 1;
    else
        return 0;
}


/**
 * @brief Constructor
 * @param p      The point
 * @return       1 The point is in h-
 *               0 The point is not in h-
 */
int hyperplane::check_negative(point_t *p)
{
    double sum = 0;
    for (int i = 0; i < dim; ++i)
        sum += p->attr[i] * norm[i];
    sum += offset;
    if (sum <= -EQN3)
        return 1;
    else
        return 0;
}


/**
 * @brief Calculate the distance from the point to the hyperplane
 * @param p     The point
 * @return      The distance
 */
double hyperplane::check_distance(point_t *p)
{
    double numerato = 0;
    for(int i = 0; i < dim; ++i)
        numerato += p->attr[i] * norm[i];
    numerato += offset;

    if(numerato >= 0)
        return numerato / normLength;
    else
        return -numerato / normLength;
}


/**
 * @brief Calculate the distance from the point to the hyperplane
 * @param p     The point
 * @return      The distance
 */
double hyperplane::check_distance_withSign(point_t *p)
{
    double numerato = 0;
    for(int i = 0; i < dim; ++i)
        numerato += p->attr[i] * norm[i];
    numerato += offset;
    return numerato / normLength;
}



/**
 * @brief Check whether the two hyperplanes are the same
 * @param h     The second hyper-plane
 * @return
 */
bool hyperplane::is_same(hyperplane *h)
{
    for(int i = 0; i < dim; ++i)
    {
        if(norm[i] != h->norm[i])
            return false;
    }
    if (offset != h->offset)
        return false;
    return true;
}



/**
 * @brief Set the length of the norm
 */
void hyperplane::set_normLength()
{
    normLength = 0;
    for(int i = 0; i < dim; ++i)
        normLength += norm[i] * norm[i];
    normLength = sqrt(normLength);
}












