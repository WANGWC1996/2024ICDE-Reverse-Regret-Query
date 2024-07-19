#include "hyperplane_set.h"
#include "../Others/lp.h"
#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <algorithm>

/**
 * @brief Constructor
 */
hyperplane_set::hyperplane_set(){}

/**
 * @brief       Constructor: initial some hyperplanes so that min <= u[i] <= max
 * @param       The point set
 */
hyperplane_set::hyperplane_set(int dim)
{
    hyperplane *h;
    //constraints for each dimension
    for(int i = 0; i < dim; ++i)
    {
        h = new hyperplane(dim);
        for (int j = 0; j < dim; ++j)
        {
            if (i == j)
                h->norm[j] = -1;
            else
                h->norm[j] = 0;
        }
        h->offset = 0;
        h->direction = 0;
        h->normLength = 1;
        hyperplanes.push_back(h);
    }

    //constraints for all the dimensions together
    h = new hyperplane(dim);
    for (int i = 0; i < dim; i++)
        h->norm[i] = 1;
    h->offset = -U_RANGE;
    h->direction = 0;
    h->set_normLength();
    hyperplanes.push_back(h);
}



/**
 * @brief Destructor
 *        Delete the hyperplanes and extreme points
 */
hyperplane_set::~hyperplane_set()
{
    //delete the hyperplanes
    int i = hyperplanes.size();
    hyperplanes.clear();

    //delete the extreme points
    i = ext_pts.size();
    while(i > 0)
    {
        delete ext_pts[i-1];
        i--;
    }
    ext_pts.clear();

}


/**
    * @brief Prepare the file for computing the convex hull (the utility range R)
    *        via halfspace interaction
    * @param feasible_pt   A points inside R
    * @param filename      The name of the file written
    */
void hyperplane_set::write(point_t *feasible_pt, char *filename)
{
    //char filename[MAX_FILENAME_LENG];
    int dim = feasible_pt->dim, size = hyperplanes.size();
    ofstream wPtr;
    wPtr.open(filename, std::ios::out);
    wPtr.setf(ios::fixed, ios::floatfield);  // set as fixed model
    wPtr.precision(6);  // set precision to 6

    // write the feasible point
    wPtr << dim <<"\n" << 1 <<"\n";
    for(int i = 0; i < dim; i++)
        wPtr << feasible_pt->attr[i] << " ";
    wPtr << "\n";

    // write the hyperplane
    wPtr << dim + 1 <<"\n" << size << "\n";//record the offset as one dimension
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            wPtr << hyperplanes[i]->norm[j] <<" ";
        }
        wPtr << hyperplanes[i]->offset <<"\n";
    }
    wPtr.close();
}

/**
 * @brief   Print the information of the hyperplane set
 *          Including hyperplanes and extreme points of the intersection(convex hull)
 */
void hyperplane_set::print()
{
    //print hyperplanes
    for (int i = 0; i < hyperplanes.size(); i++)
    {
        printf("hyperplane: ");
        hyperplanes[i]->print();
    }
    //print extreme points
    for (int i = 0; i < ext_pts.size(); i++)
    {
        printf("extreme point: ");
        ext_pts[i]->printCoordinates();
    }
}



/**
 * @brief   Print the information of the hyperplane set
 *          Including hyperplanes and extreme points of the intersection(convex hull)
 */
void hyperplane_set::printExtreme()
{
    //print extreme points
    for (int i = 0; i < ext_pts.size(); i++)
    {
        printf("extreme point: ");
        ext_pts[i]->printCoordinates();
    }
}


/**
 * @brief   Find a point inside the convex hull
 * @return  The point inside the convex hull
 */
point_t *hyperplane_set::find_feasible()
{
    int M = hyperplanes.size();
    int D = hyperplanes[0]->dim;

    // D + 2variables: D for dim, 2 for additional var for feasible
    int* ia = new int[1 + (D + 2) * M];  //TODO: delete
    int* ja = new int[1 + (D + 2) * M];  //TODO: delete
    double* ar = new double[1 + (D + 2) * M];   //TODO: delete
    int i, j;

    glp_prob *lp;
    lp = glp_create_prob();
    glp_set_prob_name(lp, "find_feasible");
    glp_set_obj_dir(lp, GLP_MAX);


    glp_add_rows(lp, M);  // add D rows: q_1...q_D
    // Add rows q_1 ... q_D
    for (i = 1; i <= M; i++)
    {
        char buf[10];
        sprintf(buf, "q%d", i);
        glp_set_row_name(lp, i, buf);
        glp_set_row_bnds(lp, i, GLP_UP, 0, 0); // qi = 0
    }

    glp_add_cols(lp, D + 2);    // add D columns: v[1] ... v[D]
    // Add col v[1] ... v[D]
    for (i = 1; i <= D + 2; i++)
    {
        char buf[10];
        sprintf(buf, "v%d", i);

        glp_set_col_name(lp, i, buf);

        if(i <= D)
            glp_set_col_bnds(lp, i, GLP_FR, 0.0, 0.0); // -infty <= v[i] < infty
        else if (i == D + 1)
            glp_set_col_bnds(lp, i, GLP_LO, 0.0, 0.0); // 0 <= v[i] < infty
        else
            glp_set_col_bnds(lp, i, GLP_UP, 0.0, D+1);

        if(i == D + 2)
            glp_set_obj_coef(lp, i, 1);  // objective: 0
        else
            glp_set_obj_coef(lp, i, 0.0);  // objective: 0
    }


    int counter = 1;
    // set value on row q1 ... qD
    for (i = 1; i <= M; i++)
    {
        for (j = 1; j <= D + 2; j++)
        {
            ia[counter] = i; ja[counter] = j;

            if(j <= D)
            {
                ar[counter++] = hyperplanes[i-1]->norm[j-1];
                //printf("%lf ", hyperplane[i-1]->normal->coord[j-1]);
            }
            else if (j == D+1)
            {
                ar[counter++] = hyperplanes[i-1]->offset;
                //printf("%lf ", hyperplane[i-1]->offset);
            }
            else if (j == D+2)
            {
                ar[counter++] = 1;
                //printf("1.00000\n");
            }
        }
    }

    // loading data
    glp_load_matrix(lp, counter - 1, ia, ja, ar);

    // running simplex
    glp_smcp parm;
    glp_init_smcp(&parm);
    parm.msg_lev = GLP_MSG_OFF; // turn off all message by glp_simplex
    glp_simplex(lp, &parm);


    double w1, w2;
    w1 = glp_get_col_prim(lp, D+1);
    w2 = glp_get_col_prim(lp, D+2);
    point_t* feasible_pt = NULL;

    if(w1 < EQN3 || w2 < EQN3 || isZero(w1) || isZero(w2))
    {

    }
    else
    {
        feasible_pt = new point_t(D);
        for (i = 0; i < D; i++)
        {
            double v = glp_get_col_prim(lp, i + 1);
            feasible_pt->attr[i] = v / w1;
        }
    }


    glp_delete_prob(lp); // clean up
    delete[] ia;
    delete[] ja;
    delete[] ar;

    return feasible_pt;
}


/**
 * @brief   Find a point inside the convex hull
 *          Do not increase the dimension so that the point found is totally inside the convex hull
 * @return  The point inside the convex hull
 */
point_t *hyperplane_set::find_feasible2()
{
    int M = hyperplanes.size();
    int D = hyperplanes[0]->dim;

    // D + 2variables: D for dim, 2 for additional var for feasible
    int* ia = new int[1 + (D ) * M];  //TODO: delete
    int* ja = new int[1 + (D ) * M];  //TODO: delete
    double* ar = new double[1 + (D ) * M];   //TODO: delete
    int i, j;

    glp_prob *lp;
    lp = glp_create_prob();
    glp_set_prob_name(lp, "feasible");
    glp_set_obj_dir(lp, GLP_MAX);


    glp_add_rows(lp, M);  // add D rows: q_1...q_D
    // Add rows q_1 ... q_D
    for (i = 1; i <= M; i++)
    {
        char buf[10];
        sprintf(buf, "q%d", i);
        glp_set_row_name(lp, i, buf);
        glp_set_row_bnds(lp, i, GLP_UP, 0, - hyperplanes[i - 1]->offset); // qi = 0
    }

    glp_add_cols(lp, D);    // add D columns: v[1] ... v[D]
    // Add col v[1] ... v[D]
    for (i = 1; i <= D; i++)
    {
        char buf[10];
        sprintf(buf, "v%d", i);
        glp_set_col_name(lp, i, buf);
        glp_set_col_bnds(lp, i, GLP_LO, 0.0, 0.0); // 0 <= v[i] < infty

        glp_set_obj_coef(lp, i, 1);  // objective: 0
    }


    int counter = 1;
    // set value on row q1 ... qD
    for (i = 1; i <= M; i++)
    {
        for (j = 1; j <= D; j++)
        {
            ia[counter] = i; ja[counter] = j;
            ar[counter++] = hyperplanes[i - 1]->norm[j - 1];
            //printf("%lf ", hyperplane[i-1]->normal->coord[j-1]);
        }
    }

    // loading data
    glp_load_matrix(lp, counter - 1, ia, ja, ar);

    // running simplex
    glp_smcp parm;
    glp_init_smcp(&parm);
    parm.msg_lev = GLP_MSG_OFF; // turn off all message by glp_simplex
    glp_simplex(lp, &parm);

    int w = glp_get_status(lp);
    //double w = glp_get_obj_val(lp);
    point_t* feasible_pt = NULL;
    //std::cout << w << "  " << glp_get_col_prim(lp, 0 + 1) << "\n";
    if(w != GLP_INFEAS && w != GLP_NOFEAS)
    {
        feasible_pt = new point_t(D);
        for (i = 0; i < D; i++)
            feasible_pt->attr[i] = glp_get_col_prim(lp, i + 1);
    }


    glp_delete_prob(lp); // clean up
    delete[] ia;
    delete[] ja;
    delete[] ar;

    return feasible_pt;
}



/**
 * @brief   Find a point inside the convex hull
 * @return  The point inside the convex hull
 */
double hyperplane_set::LLP(double *obj, int minmax)
{
    int M = hyperplanes.size();
    int D = hyperplanes[0]->dim;

    // D + 2variables: D for dim, 2 for additional var for feasible
    int* ia = new int[1 + (D ) * M];  //TODO: delete
    int* ja = new int[1 + (D ) * M];  //TODO: delete
    double* ar = new double[1 + (D ) * M];   //TODO: delete
    int i, j;

    glp_prob *lp;
    lp = glp_create_prob();
    glp_set_prob_name(lp, "LLP");
    if(minmax == -1)
        glp_set_obj_dir(lp, GLP_MIN);
    else
        glp_set_obj_dir(lp, GLP_MAX);

    glp_add_rows(lp, M);  // add D rows: q_1...q_D
    // Add rows q_1 ... q_D
    for (i = 1; i <= M; i++)
    {
        char buf[10];
        sprintf(buf, "q%d", i);
        glp_set_row_name(lp, i, buf);
        glp_set_row_bnds(lp, i, GLP_UP, 0, - hyperplanes[i - 1]->offset); // qi = 0
    }

    glp_add_cols(lp, D);    // add D columns: v[1] ... v[D]
    // Add col v[1] ... v[D]
    for (i = 1; i <= D; i++)
    {
        //column
        char buf[10];
        sprintf(buf, "v%d", i);
        glp_set_col_name(lp, i, buf);
        glp_set_col_bnds(lp, i, GLP_LO, 0.0, 0.0); // 0 <= v[i] < infty

        //objection
        glp_set_obj_coef(lp, i, obj[i - 1]);  // objective
    }


    int counter = 1;
    // set value on row q1 ... qD
    for (i = 1; i <= M; i++)
    {
        for (j = 1; j <= D; j++)
        {
            ia[counter] = i; ja[counter] = j;
            ar[counter++] = hyperplanes[i - 1]->norm[j - 1];
            //printf("%lf ", hyperplane[i-1]->normal->coord[j-1]);
        }
    }

    // loading data
    glp_load_matrix(lp, counter - 1, ia, ja, ar);

    // running simplex
    glp_smcp parm;
    glp_init_smcp(&parm);
    parm.msg_lev = GLP_MSG_OFF; // turn off all message by glp_simplex
    glp_simplex(lp, &parm);


    double w = glp_get_obj_val(lp);
    glp_delete_prob(lp); // clean up
    delete[] ia;
    delete[] ja;
    delete[] ar;

    return w;
}



/*-------------------------------------------------
-print_summary(qh)
*/
void print_summary(qhT *qh) {
    facetT *facet;
    int k;

    printf("\n%d vertices and %d facets with normals:\n",
           qh->num_vertices, qh->num_facets);
    FORALLfacets {
        for (k=0; k < qh->hull_dim; k++)
            printf("%6.2g ", facet->normal[k]);
        printf("\n");
    }
}


/**
 * @brief   Find the extreme points of the convex hull & prune the useless points
 * @return
 */
bool hyperplane_set::setconvexhull()
{
    int dim = hyperplanes[0]->dim, size = hyperplanes.size();
    if(dim == 1)
    {
        hyperplane *leftHyper, *rightHyper;
        ext_pts.clear();
        ext_pts.push_back(new point_t(dim));//used for left bound
        ext_pts[0]->attr[0] = -10;
        ext_pts.push_back(new point_t(dim));//used for right bound
        ext_pts[1]->attr[0] = 999999;
        double value;
        for(int i = 0; i < size; ++i)
        {
            if(hyperplanes[i]->norm[0] > 0)//right bound
            {
                value = - hyperplanes[i]->offset / hyperplanes[i]->norm[0];
                if(value < ext_pts[1]->attr[0])
                {
                    ext_pts[1]->attr[0] = value;
                    rightHyper = hyperplanes[i];
                }
            }
            else //for left bound
            {
                value = - hyperplanes[i]->offset / hyperplanes[i]->norm[0];
                if(value > ext_pts[0]->attr[0])
                {
                    ext_pts[0]->attr[0] = value;
                    leftHyper = hyperplanes[i];
                }
            }

            if(ext_pts[0]->attr[0] >= ext_pts[1]->attr[0])
                return false;
        }
        hyperplanes.clear();
        hyperplanes.push_back(leftHyper);
        hyperplanes.push_back(rightHyper);

        return true;
    }
    else
    {
        int curlong, totlong, exitcode;  /* used if !qh_NOmem */
        char options[2000];
        //qhT qh_qh;
        //qhT *qh= &qh_qh;  /* Alternatively -- qhT *qh= (qhT *)malloc(sizeof(qhT)) */
        QHULL_LIB_CHECK

        qh_init_A(qh, stdin, stdout, stderr, 0, NULL);
        exitcode = setjmp(qh->errexit);
        if (!exitcode)
        {
            array = new coordT[size * (dim + 1)];
            pointT *points;

            qh->NOerrexit = False;
            strcat(qh->rbox_command, "user_eg2 halfspace example");
            sprintf(options, "qhull H0 s Tcv Fp Fx");
            qh_initflags(qh, options);
            //makehalf(array[0], SIZEcube, DIM);

            //the feasible point

            point_t *feasible_pt = find_feasible();


            if (feasible_pt == NULL)
                return false;
            internal = feasible_pt;

            //give the information of the convex hull to the qhull
            //qh_setfeasible(qh, DIM); /* from io_r.c, sets qh->feasible_point from 'Hn,n' */
            qh->feasible_point = (pointT *) qh_malloc((size_t) dim * sizeof(coordT));
            for (int i = 0; i < dim; ++i)
                qh->feasible_point[i] = feasible_pt->attr[i];
            /* you may malloc and set qh->feasible_point directly.  It is only used for
               option 'Fp' */

            //hyper-planes
            for (int i = 0; i < size; ++i)
            {
                for (int j = 0; j < dim; ++j)
                    array[i * (dim + 1) + j] = hyperplanes[i]->norm[j];
                array[i * (dim + 1) + dim] = hyperplanes[i]->offset;
            }

            //qh_printmatrix(qh, stdout, "input as halfspace coefficients + offsets", array, hyperplanes.size(), dim+1);
            //fflush(NULL);


            points = qh_sethalfspace_all(qh, dim + 1, size, array, qh->feasible_point);
            qh_init_B(qh, points, size, dim, True); /* qh_freeqhull frees points */
            qh_qhull(qh);
            fflush(NULL);
            qh_check_output(qh);


            int numfacets, numsimplicial, numridges, totneighbors, numcoplanars, numtricoplanars;
            qh->printoutnum = 0;
            qh_countfacets(qh, qh->facet_list, NULL, !qh_ALL, &numfacets, &numsimplicial,
                           &totneighbors, &numridges, &numcoplanars, &numtricoplanars);

            double **ext = new double *[numfacets];
            for (int i = 0; i < numfacets; ++i)
                ext[i] = new double[dim];

            int *half = new int[size + 1];
            qh_produce_outputt(qh, ext, half);  /* delete this line to help avoid io_r.c */
            //if (qh->VERIFYoutput && !qh->FORCEoutput && !qh->STOPadd && !qh->STOPcone && !qh->STOPpoint)
            //    qh_check_points(qh);

            /*
            for(int i = 0; i < numfacets; ++i)
            {
                for(int j = 0; j < dim; ++j)
                    cout << ext[i][j] << "  ";
                cout << "\n";
            }

            for(int i = 0 ; i < half[0]; ++i)
                cout << half[i+1] << "\n";
            */

            //update the set of extreme points
            //delete all the original extreme points

            while (ext_pts.size() > 0)
            {
                point_t *pt = ext_pts[ext_pts.size() - 1];
                ext_pts.pop_back();
                delete pt;
            }
            if (ext_pts.size() > 0)
                ext_pts.clear();

            //input new extreme points
            for (int i = 0; i < numfacets; ++i)
            {
                point_t *p = new point_t(dim);
                for (int j = 0; j < dim; ++j)
                    p->attr[j] = ext[i][j];
                ext_pts.push_back(p);
            }


            // update the set of hyperplanes
            int size = half[0];
            half[0] = -1;
            sort(half + 1, half + size + 1);
            int M = hyperplanes.size();
            for (int i = M - 1, count = size; i > -1; --i)
            {
                if (half[count] < i)
                    hyperplanes.erase(hyperplanes.begin() + i);
                else
                    --count;
            }

            delete[]half;

            set_bounding_with_extremePoints();
            /*
            if (qh->VERIFYoutput && !qh->FORCEoutput && !qh->STOPadd && !qh->STOPcone && !qh->STOPpoint)
                qh_check_points(qh);
            fflush(NULL);
            printf( "\n========\nadd halfspaces for cube to intersection\n");
            addhalf(qh, array[0], 4, SIZEdiamond, DIM, qh->feasible_point);
            qh_check_output(qh);
            qh_produce_output(qh);  // delete this line to help avoid io_r.c
            if (qh->VERIFYoutput && !qh->FORCEoutput && !qh->STOPadd && !qh->STOPcone && !qh->STOPpoint)
                qh_check_points(qh);
            fflush(NULL);
            */
        }
        qh->NOerrexit = True;
        qh->NOerrexit = True;
        updateWithAdd = 0;

        /*
    #ifdef qh_NOmem
        qh_freeqhull(qh, qh_ALL);
    #else
        qh_freeqhull(qh, !qh_ALL);
        qh_memfreeshort(qh, &curlong, &totlong);
        if (curlong || totlong)
            fprintf(stderr, "qhull warning (user_eg2, run 3): did not free %d bytes of long memory (%d pieces)\n",
                    totlong, curlong);
    #endif
         */
        return true;
    }
}


/**
 * @brief Already know the feasible of the points
 * @param fspt    The feasible point
 * @return
 */
bool hyperplane_set::setconvexhull(point_t *fspt)
{
    int dim = hyperplanes[0]->dim, size = hyperplanes.size();

    if(dim == 1)
    {
        hyperplane *leftHyper, *rightHyper;
        ext_pts.push_back(new point_t(dim));//used for left bound
        ext_pts[0]->attr[0] = -10;
        ext_pts.push_back(new point_t(dim));//used for right bound
        ext_pts[1]->attr[0] = 999999;
        double value;
        for(int i = 0; i < size; ++i)
        {
            if(hyperplanes[i]->norm[0] > 0)//right bound
            {
                value = - hyperplanes[i]->offset / hyperplanes[i]->norm[0];
                if(value < ext_pts[1]->attr[0])
                {
                    ext_pts[1]->attr[0] = value;
                    rightHyper = hyperplanes[i];
                }
            }
            else //for left bound
            {
                value = - hyperplanes[i]->offset / hyperplanes[i]->norm[0];
                if(value > ext_pts[0]->attr[0])
                {
                    ext_pts[0]->attr[0] = value;
                    leftHyper = hyperplanes[i];
                }
            }

            if(ext_pts[0]->attr[0] >= ext_pts[1]->attr[0])
                return false;
        }
        hyperplanes.clear();
        hyperplanes.push_back(leftHyper);
        hyperplanes.push_back(rightHyper);

        return true;
    }
    else
    {
        int curlong, totlong, exitcode;  /* used if !qh_NOmem */
        char options[2000];
        //qhT qh_qh;
        //qhT *qh= &qh_qh;  /* Alternatively -- qhT *qh= (qhT *)malloc(sizeof(qhT)) */
        QHULL_LIB_CHECK

        qh_init_A(qh, stdin, stdout, stderr, 0, NULL);
        exitcode = setjmp(qh->errexit);
        if (!exitcode)
        {
            qh->NOerrexit = False;
            strcat(qh->rbox_command, "user_eg2 halfspace example");
            sprintf(options, "qhull H0 s Tcv Fp Fx");
            qh_initflags(qh, options);
            //makehalf(array[0], SIZEcube, DIM);

            //the feasible point
            internal = fspt;
            //give the information of the convex hull to the qhull
            //qh_setfeasible(qh, DIM); /* from io_r.c, sets qh->feasible_point from 'Hn,n' */
            qh->feasible_point = (pointT *) qh_malloc((size_t) dim * sizeof(coordT));
            for (int i = 0; i < dim; ++i)
                qh->feasible_point[i] = fspt->attr[i];
            /* you may malloc and set qh->feasible_point directly.  It is only used for
               option 'Fp' */

            lengthArray = size * (dim + 1);
            array = new coordT[size * (dim + 1)];
            pointT *points;
            //hyper-planes
            for (int i = 0; i < size; ++i)
            {
                for (int j = 0; j < dim; ++j)
                    array[i * (dim + 1) + j] = hyperplanes[i]->norm[j];
                array[i * (dim + 1) + dim] = hyperplanes[i]->offset;
            }

            //qh_printmatrix(qh, stdout, "input as halfspace coefficients + offsets", array, hyperplanes.size(), dim+1);
            //fflush(NULL);


            points = qh_sethalfspace_all(qh, dim + 1, size, array, qh->feasible_point);
            qh_init_B(qh, points, size, dim, True); /* qh_freeqhull frees points */
            qh_qhull(qh);
            fflush(NULL);
            qh_check_output(qh);


            int numfacets, numsimplicial, numridges, totneighbors, numcoplanars, numtricoplanars;
            qh->printoutnum = 0;
            qh_countfacets(qh, qh->facet_list, NULL, !qh_ALL, &numfacets, &numsimplicial,
                           &totneighbors, &numridges, &numcoplanars, &numtricoplanars);

            double **ext = new double *[numfacets];
            for (int i = 0; i < numfacets; ++i)
                ext[i] = new double[dim];

            int *half = new int[size + 1];
            qh_produce_outputt(qh, ext, half);  /* delete this line to help avoid io_r.c */
            //if (qh->VERIFYoutput && !qh->FORCEoutput && !qh->STOPadd && !qh->STOPcone && !qh->STOPpoint)
            //    qh_check_points(qh);

            /*
            for(int i = 0; i < numfacets; ++i)
            {
                for(int j = 0; j < dim; ++j)
                    cout << ext[i][j] << "  ";
                cout << "\n";
            }

            for(int i = 0 ; i < half[0]; ++i)
                cout << half[i+1] << "\n";
            */

            //update the set of extreme points
            //delete all the original extreme points

            while (ext_pts.size() > 0)
            {
                point_t *pt = ext_pts[ext_pts.size() - 1];
                ext_pts.pop_back();
                delete pt;
            }
            if (ext_pts.size() > 0)
                ext_pts.clear();

            //input new extreme points
            for (int i = 0; i < numfacets; ++i)
            {
                point_t *p = new point_t(dim);
                for (int j = 0; j < dim; ++j)
                    p->attr[j] = ext[i][j];
                ext_pts.push_back(p);
            }


            // update the set of hyperplanes
            int size = half[0];
            half[0] = -1;
            sort(half + 1, half + size + 1);
            int M = hyperplanes.size();
            for (int i = M - 1, count = size; i > -1; --i)
            {
                if (half[count] < i)
                    hyperplanes.erase(hyperplanes.begin() + i);
                else
                    --count;
            }

            delete []half;
            delete []array;
            for (int i = 0; i < numfacets; ++i)
                delete[]ext[i];
            delete[]ext;

            set_bounding_with_extremePoints();

            /*
            if (qh->VERIFYoutput && !qh->FORCEoutput && !qh->STOPadd && !qh->STOPcone && !qh->STOPpoint)
                qh_check_points(qh);
            fflush(NULL);
            printf( "\n========\nadd halfspaces for cube to intersection\n");
            addhalf(qh, array[0], 4, SIZEdiamond, DIM, qh->feasible_point);
            qh_check_output(qh);
            qh_produce_output(qh);  // delete this line to help avoid io_r.c
            if (qh->VERIFYoutput && !qh->FORCEoutput && !qh->STOPadd && !qh->STOPcone && !qh->STOPpoint)
                qh_check_points(qh);
            fflush(NULL);
            */
        }
        qh->NOerrexit = True;
        qh->NOerrexit = True;
        updateWithAdd = 0;


#ifdef qh_NOmem
        qh_freeqhull(qh, qh_ALL);
#else
        qh_freeqhull(qh, !qh_ALL);
        qh_memfreeshort(qh, &curlong, &totlong);
        if (curlong || totlong)
            fprintf(stderr, "qhull warning (user_eg2, run 3): did not free %d bytes of long memory (%d pieces)\n",
                    totlong, curlong);
#endif

        return true;
    }
}


/**
 * @brief Add a halfspace to the convex hull
 *        Warning!!! Make sure that the feasible point is in the new convex hull,
 *        otherwise call feasible point function
 * @param h     The new halfspaces
 * @return
 */
bool hyperplane_set::add_halfspace(hyperplane *h, point_t *fspt)
{

    int dim = h->dim;
    coordT *point, *normal = new double[dim], offset, *next;
    facetT *facet;
    boolT isoutside;
    realT bestdist;
    double *newarray = new double[lengthArray + (dim + 1)];
    for (int i = 0; i < lengthArray; ++i)
        newarray[i] = array[i];
    delete[]array;
    array = newarray;
    lengthArray = lengthArray + dim + 1;

    //the newly added half-sapces
    for (int i = 0; i < dim; ++i)
        normal[i] = h->norm[i];
    offset = h->offset;

    for (int i = 0; i < dim; ++i)
        qh->feasible_point[i] = fspt->attr[i];

    //if (qh->JOGGLEmax < REALmax/2 && !qh->PREmerge)
    //    qh_fprintf(qh, qh->ferr, 7098, "qhull warning (user_eg2/addhalf): joggle 'QJ' is enabled.  Output is simplicial (i.e., triangles in 2-D)\n");

    point = array + lengthArray - dim - 1;  /* does not use point[dim] */
    qh_sethalfspace(qh, dim, point, &next, normal, &offset, qh->feasible_point);
    facet = qh_findbestfacet(qh, point, !qh_ALL, &bestdist, &isoutside);
    if (isoutside)
    {
        if (!qh_addpoint(qh, point, facet, False))
        {
            return false;;  /* user requested an early exit with 'TVn' or 'TCn' */
        }
    } else
    {
        return false;
    }
    //qh_printpoint(qh, stdout, "added offset -1 and normal", normal);
    //printf("%d points, %d extra points, %d vertices, and %d facets in total\n", qh->num_points, qh_setsize(qh, qh->other_points), qh->num_vertices, qh->num_facets);
    //qh_check_output(qh);
    //qh_produce_output(qh);  // delete this line to help avoid io_r.c


    int numfacets, numsimplicial, numridges, totneighbors, numcoplanars, numtricoplanars;
    qh->printoutnum = 0;
    qh_countfacets(qh, qh->facet_list, NULL, !qh_ALL, &numfacets, &numsimplicial,
                   &totneighbors, &numridges, &numcoplanars, &numtricoplanars);

    double **ext = new double *[numfacets];
    for (int i = 0; i < numfacets; ++i)
        ext[i] = new double[dim];

    int *half = new int[hyperplanes.size() + 1];
    qh_produce_outputt(qh, ext, half);
    if (qh->VERIFYoutput && !qh->FORCEoutput && !qh->STOPadd && !qh->STOPcone && !qh->STOPpoint)
        qh_check_points(qh);


    /*
    for(int i = 0; i < numfacets; ++i)
    {
        for(int j = 0; j < dim; ++j)
            cout << ext[i][j] << "  ";
        cout << "\n";
    }

    for(int i = 0 ; i < half[0]; ++i)
        cout << half[i+1] << "\n";
    */


    //update the set of extreme points
    //delete all the original extreme points
    while (ext_pts.size() > 0)
    {
        point_t *pt = ext_pts[ext_pts.size() - 1];
        ext_pts.pop_back();
        delete pt;
    }
    ext_pts.clear();
    //input new extreme points
    for (int i = 0; i < numfacets; ++i)
    {
        point_t *p = new point_t(dim);
        for (int j = 0; j < dim; ++j)
            p->attr[j] = ext[i][j];
        ext_pts.push_back(p);
    }

    // update the set of hyperplanes
    hyperplanes.push_back(h);
    int size = half[0];
    half[0] = -1;
    sort(half + 1, half + size + 1);
    int M = hyperplanes.size();
    for (int i = M - 1, count = size; i > -1; --i)
    {
        if (half[count] < i)
        {
            hyperplanes.erase(hyperplanes.begin() + i);
        } else
            --count;
    }

    delete[]half;

    set_bounding_with_extremePoints();

    if (qh->DOcheckmax)
        qh_check_maxout(qh);
    else if (qh->KEEPnearinside)
        qh_nearcoplanar(qh);

    updateWithAdd = 1;

    return true;

}/*.addhalf.*/



/**
 * @brief Check the relation between the hyperplane and the intersection of the hyperplane set
 *        Since the extreme points of the half_set can not be accurate enough, we set "Precision" to solve the error
 * @param h     The hyperplane
 * @return      1: half_set on the positive side of the hyperplane
 *              -1: half_set on the negative side of the hyperplane
 *              0: half_set intersects with the hyperplane
 */
int hyperplane_set::check_relation_fast(hyperplane *h)
{
    //exception check
    int M = ext_pts.size();
    if (M < 1)
    {
        printf("%s\n", "None of the ext_pts in the set.");
        return -2;
    }

    //check if the hyper_set is on one side of the hyper-plane
    double dis_set_plane = h->check_distance_withSign(internal);
    if(dis_set_plane < 0)
    {
        if(-dis_set_plane > outRadius + EQN6)
            return -1;
        else if(-dis_set_plane < inRadius - EQN6)
            return 0;
    }
    else
    {
        if(dis_set_plane > outRadius + EQN6)
            return 1;
        else if(dis_set_plane < inRadius - EQN6)
            return  0;
    }

    int positive = 0, negative = 0;
    for (int i = 0; i < M; i++)
    {
        int relation = h->check_position(ext_pts[i]);
        if (relation == -1)
            ++negative;
        else if (relation == 1)
            ++positive;
        if (positive > 0 && negative > 0)
        {
            return 0;
        }
    }
    if (negative > 0)
        return -1;
    else
        return 1;
}





/**
 * @brief Check the relation between the hyperplane and the intersection of the hyperplane set
 *        Since the extreme points of the half_set can not be accurate enough, we set "Precision" to solve the error
 * @param h     The hyperplane
 * @return      1: half_set on the positive side of the hyperplane
 *              -1: half_set on the negative side of the hyperplane
 *              0: half_set intersects with the hyperplane
 */
int hyperplane_set::check_relation(hyperplane *h)
{
    //exception check
    int M = ext_pts.size();
    if (M < 1)
    {
        printf("%s\n", "None of the ext_pts in the set.");
        return -2;
    }

    int positive = 0, negative = 0;
    for (int i = 0; i < M; i++)
    {
        int relation = h->check_position(ext_pts[i]);
        if (relation == -1)
            ++negative;
        else if (relation == 1)
            ++positive;
        if (positive > 0 && negative > 0)
        {
            return 0;
        }
    }
    if (negative > 0)
        return -1;
    else
        return 1;
}




/**
 * @brief Check whether p1 R-dominates p2
 * @param p1 The first point
 * @param p2 The second point
 * @return   1 R-dominates
 *          -1 Does not R-dominate
 */
bool hyperplane_set::R_dominate(point_t *p1, point_t *p2)
{
    int size = ext_pts.size(), d = ext_pts[0]->dim;
    hyperplane *h = new hyperplane(p1, p2, 0);
    for (int i = 0; i < size; i++)
    {
        if (h->check_positive(ext_pts[i]) != 1)
        {
            delete h;
            return false;
        }
    }
    delete h;
    return true;
}



/**
 * @brief Calculate the average point of the extreme points
 * @param ap The average point
 */
point_t* hyperplane_set::average_point()
{
    int size = ext_pts.size(), dim = ext_pts[0]->dim;
    point_t* avgPoint = new point_t(dim);
    for(int j = 0; j < dim; ++j)
        avgPoint->attr[j] = 0;
    //calculate the sum
    for(int i = 0; i < size; ++i)
    {
        for (int j = 0; j < dim; ++j)
            avgPoint->attr[j] += ext_pts[i]->attr[j];
    }
    for(int j = 0; j < dim; ++j)
        avgPoint->attr[j] /= size;
    return avgPoint;
}




void hyperplane_set::write(point_set *pset, char *filename)
{
    //char filename[MAX_FILENAME_LENG];
    int dim = pset->points[0]->dim, M = pset->points.size();
    ofstream wPtr;
    wPtr.open(filename, std::ios::out);
    wPtr.setf(ios::fixed, ios::floatfield);  // set as fixed model
    wPtr.precision(6);  // set precision to 6

    // write the points
    wPtr << dim <<"\n" << pset->points.size() <<"\n";
    for(int i = 0; i < M; ++i)
    {
        for(int j = 0; j < dim; j++)
            wPtr << pset->points[i]->attr[j] << " ";
        wPtr << "\n";
    }
    wPtr.close();
}




void hyperplane_set::swap(int position1, int position2)
{
    //make sure position1  < position2
    if(position1 > position2)
    {
        int pp = position1;
        position1 = position2;
        position2 = pp;
    }

    hyperplane *h = hyperplanes[position1];
    hyperplanes.insert(hyperplanes.begin() + position2, hyperplanes[position1]);
    hyperplanes.erase(hyperplanes.begin() + position1);

    hyperplanes.insert(hyperplanes.begin() + position1, hyperplanes[position2]);
    hyperplanes.erase(hyperplanes.begin() + position2 + 1);
}


/**
 * @brief Conduct bubble and place the largest value to end
 * @param start     The start position
 * @param end       The end position
 */
void hyperplane_set::bubble(int start, int end)
{
    for(int i = start; i < end; ++i)
    {
        if (hyperplanes[i]->xaxis > hyperplanes[i + 1]->xaxis)
        {
            hyperplanes.insert(hyperplanes.begin() + i + 2, hyperplanes[i]);
            hyperplanes.erase(hyperplanes.begin() + i);
        }
    }
}


/**
 * @brief Sort the hyperplanes based on the x-axis from strat to end
 * @param start     The start position
 * @param end       The end position
 */
void hyperplane_set::bubbleSort(int start, int end)
{
    for (int i = 0; i < end - start + 1; ++i)
        bubble(start, end - i);
}



hyperplane* hyperplane_set::comparableSelect(int start, int end, int k)
{
    if(end - start < 5)
    {
        bubbleSort(start, end);
        return hyperplanes[start + k - 1];
    }

    for (int i = 0; i <= ((end - start - 4)/5); ++i)
    {
        int s = start + 5 * i;
        for (int j = 4; j > 1; --j)
            bubble(s, s + j);
        //swap
        swap(start + i, s + 2);
    }

    hyperplane *h = comparableSelect(start, start + (end - start - 4)/5, (end - start + 6)/10);
    double xx = h->xaxis;
    int middlePosition = end + 1;

    int index = start;
    for(int i = start; i <= end; ++i)
    {
        if(hyperplanes[index]->xaxis == xx)
        {
            if(middlePosition > hyperplanes.size())
                hyperplanes.push_back(hyperplanes[index]);
            else
                hyperplanes.insert(hyperplanes.begin() + middlePosition, hyperplanes[index]);
            hyperplanes.erase(hyperplanes.begin() + index);
        }
        else if (hyperplanes[index]->xaxis > xx)
        {
            --middlePosition;
            hyperplanes.insert(hyperplanes.begin() + end + 1, hyperplanes[index]);
            hyperplanes.erase(hyperplanes.begin() + index);
        }
        else
        {
            ++index;
        }
    }

    --middlePosition;
    int j = middlePosition - start + 1;
    if(k <= j)
        return comparableSelect(start, middlePosition, k);
    else
        return comparableSelect(middlePosition + 1, end, k-j);

}


/**
 * @brief Find the position of the hyper-plane based on the x-axis
 * @param h     The hyper-plane
 * @return
 */
int hyperplane_set::findPosition(hyperplane *h)
{
    int left = 0, right = hyperplanes.size() - 1;
    while (left <= right)
    {
        int middle = (right + left)/2;
        if(h->xaxis <= hyperplanes[middle]->xaxis)
            right = middle - 1;
        else
            left = middle + 1;
    }
    return left;
}


/**
 * @brief Sampled the utility space
 * @param dimension     The number of dimensions which have been considered
 * @param occupy        The number of segments we have used
 * @param segment       The total number of segments
 * @param utility       It stores the number of segments used by each dimension
 * @param SampledV      It stores the sampled utility vector
 */
void hyperplane_set::samplingUtility(int dimension, int occupy, double segment, double *utility, std::vector<point_t*> &SampledV)
{
    int dim = hyperplanes[0]->dim;
    double dis = U_RANGE / segment;

    if(dimension == dim - 1)
    {
        point_t *p = new point_t(dim);
        for(int i = 0; i < dim; ++i)
            p->attr[i] = dis * utility[i];
        if(check_point_inside(p, U_RANGE/segment))
        {
            SampledV.push_back(p);
            //p->print();
        }
    }
    else
    {
        ++dimension;
        for (int j = 0; j <= segment - occupy; ++j)
        {
            utility[dimension] = j;
            samplingUtility(dimension, occupy + j, segment, utility, SampledV);
        }
    }
}



/**
 * @brief Sampled the utility space
 * @param dimension     The number of dimensions which have been considered
 * @param occupy        The number of segments we have used
 * @param segment       The total number of segments
 * @param utility       It stores the number of segments used by each dimension
 * @param SampledV      It stores the sampled utility vector
 */
point_t* hyperplane_set::sampling()
{
    int dim = hyperplanes[0]->dim + 1;
    point_t *u = new point_t(dim);
    for (int i = 0; i < dim; ++i)
    {
        u->attr[i] = rand() % 100;
    }
    return u;
}





/**
 * @brief Build the qhull once for each split (share the computation)
 * @param h
 * @param ptSet
 * @param ngSet
 * @return
 */
bool hyperplane_set::divide(hyperplane *h, hyperplane_set *ptSet, hyperplane_set *ngSet)
{
    int dim = h->dim;
    if(h->check_position(internal) == -1)
    {
        //update ngSet
        for(int i = 0; i < hyperplanes.size(); ++i)
            ngSet->hyperplanes.push_back(hyperplanes[i]);
        ngSet->hyperplanes.push_back(h);
        ngSet->setconvexhull(internal);
        ngSet->set_bounding_with_extremePoints();


        //update ptSet extreme points
        for (int i = 0; i < ngSet->ext_pts.size(); ++i)
        {
            double diss = h->check_distance_withSign(ngSet->ext_pts[i]);
            if (-EQN2 < diss && diss < EQN2)
                ptSet->ext_pts.push_back(ngSet->ext_pts[i]);
        }
        for (int i = 0; i < ext_pts.size(); ++i)
        {
            if (h->check_distance_withSign(ext_pts[i]) > EQN2)
                ptSet->ext_pts.push_back(ext_pts[i]);
        }
        //update ptSet hyper-plane
        for (int i = 0; i < hyperplanes.size(); ++i)
            ptSet->hyperplanes.push_back(hyperplanes[i]);
        hyperplane *hh = new hyperplane(h, -1);
        ptSet->hyperplanes.push_back(hh);
        ptSet->qhCanUse = false;
        ptSet->set_bounding_with_extremePoints();

    }
    else
    {
        //update ngSet
        for (int i = 0; i < hyperplanes.size(); ++i)
            ptSet->hyperplanes.push_back(hyperplanes[i]);
        hyperplane *hh = new hyperplane(h, -1);
        ptSet->hyperplanes.push_back(hh);
        ptSet->setconvexhull(internal);
        ptSet->set_bounding_with_extremePoints();

        //update ptSet extreme points
        for (int i = 0; i < ptSet->ext_pts.size(); ++i)
        {
            double diss = h->check_distance_withSign(ptSet->ext_pts[i]);
            if (-EQN2 < diss && diss < EQN2)
                ngSet->ext_pts.push_back(ptSet->ext_pts[i]);
        }
        for (int i = 0; i < ext_pts.size(); ++i)
        {
            if (h->check_distance_withSign(ext_pts[i]) < EQN2)
                ngSet->ext_pts.push_back(ext_pts[i]);
        }

        //update ngSet hyper-plane
        for (int i = 0; i < hyperplanes.size(); ++i)
            ngSet->hyperplanes.push_back(hyperplanes[i]);
        ngSet->hyperplanes.push_back(h);
        ngSet->qhCanUse = false;
        ngSet->set_bounding_with_extremePoints();
    }


    return true;
}


/**
 * @brief Build a qhull for each node
 * @param h
 * @param ptSet
 * @param ngSet
 * @return
 */
bool hyperplane_set::divide2(hyperplane *h, hyperplane_set *ptSet, hyperplane_set *ngSet)
{
    int dim = h->dim;
    if(h->check_position(internal) == -1)
    {
        //update ngSet
        for(int i = 0; i < hyperplanes.size(); ++i)
            ngSet->hyperplanes.push_back(hyperplanes[i]);
        ngSet->hyperplanes.push_back(h);
        ngSet->setconvexhull();

        //update ptSet
        for (int i = 0; i < hyperplanes.size(); ++i)
            ptSet->hyperplanes.push_back(hyperplanes[i]);
        hyperplane *hh = new hyperplane(dim);
        for (int j = 0; j < dim; ++j)
            hh->norm[j] = -h->norm[j];
        hh->offset = -h->offset;
        ptSet->hyperplanes.push_back(hh);
        ptSet->setconvexhull();

    }
    else
    {
        //update ngSet
        for (int i = 0; i < hyperplanes.size(); ++i)
            ngSet->hyperplanes.push_back(hyperplanes[i]);
        hyperplane *hh = new hyperplane(dim);
        for (int j = 0; j < dim; ++j)
            hh->norm[j] = -h->norm[j];
        hh->offset = -h->offset;
        ngSet->hyperplanes.push_back(hh);
        ngSet->setconvexhull();

        //update ptSet
        for (int i = 0; i < hyperplanes.size(); ++i)
            ptSet->hyperplanes.push_back(hyperplanes[i]);
        ptSet->hyperplanes.push_back(h);
        ptSet->setconvexhull();
    }
    return true;
}




/**
 * @brief It has three parts for the convex hull
 *        1. Set the average point based on the extreme points
 *        2. Set the outer-sphere radius
 *        3. Set the inner-sphere radius
 */
bool hyperplane_set::set_bounding_with_extremePoints()
{
    //calculate the average point
    if(ext_pts.size() < 1)
    {
        return false;
    }
    else
    {
        int dim = ext_pts[0]->dim;
        internal = new point_t(dim);
        for(int j = 0; j < dim; ++j)
            internal->attr[j] = 0;
        double stt = ext_pts.size();
        for(int i = 0; i < ext_pts.size(); ++i)
        {
            for(int j = 0; j < dim; ++j)
                internal->attr[j] += ext_pts[i]->attr[j] / stt;
        }

        //calculate the outer-sphere radius
        outRadius = -10;
        for(int i = 0; i < ext_pts.size(); ++i)
        {
            double dis = internal->distance(ext_pts[i]);
            if(dis > outRadius)
                outRadius = dis;
        }

        //calculate the inner-sphere radius
        inRadius = 999999;
        for(int i = 0; i < hyperplanes.size(); ++i)
        {
            double dis = hyperplanes[i]->check_distance(internal);
            if(dis < inRadius)
                inRadius = dis;
        }
        return true;
    }

}


/**
 * @brief Build the relation between points
 * @param pSet
 */
void hyperplane_set::buildRelationBetweenPoint(point_set *pSet)
{
    int size = pSet->points.size();
    for(int i = 0; i < size - 1; ++i)
    {
        for(int j = i + 1; j < size; ++j)
        {
            if(R_dominate(pSet->points[i], pSet->points[j]))
            {
                pSet->points[i]->dominating.push_back(pSet->points[j]);
                pSet->points[j]->dominated.push_back(pSet->points[i]);
            }
            else if (R_dominate(pSet->points[j], pSet->points[i]))
            {
                pSet->points[j]->dominating.push_back(pSet->points[i]);
                pSet->points[i]->dominated.push_back(pSet->points[j]);
            }
        }
    }
}


/**
 * @brief Find the points which are not R-dominated by k points
 * @param pSet
 */
void hyperplane_set::Rkskyband(point_set *pSet, int k)
{
    for(int i = 0; i < pSet->points.size(); ++i)
    {
        int dominated = 0;
        for(int j = 0; j < pSet->points.size(); ++j)
        {
            if(i != j)
            {
                if (R_dominate(pSet->points[j], pSet->points[i]))
                {
                    ++dominated;
                    if(dominated >= k)
                    {
                        pSet->points.erase(pSet->points.begin() + i);
                        --i;
                        break;
                    }
                }
            }
        }
    }
}

/**
 * @brief Constructor
 * @param R
 */
hyperplane_set::hyperplane_set(hyperplane_set *R)
{
    for(int i = 0; i < R->hyperplanes.size(); ++i)
    {
        hyperplanes.push_back(R->hyperplanes[i]);
    }
    internal = R->internal;
    inRadius = R->inRadius;
    outRadius = R->outRadius;

}


/**
 * @brief Check if it is feasible, if the hyper-plane is added into the hyper-plane set,
 * @param h     The newly added hyper-plane
 * @return
 */
point_t *hyperplane_set::detect_feasible(hyperplane *h, point_t *inp)
{
    if(h->check_position(inp) == -1)
        return inp;
    hyperplanes.push_back(h);
    point_t *p = find_feasible2();
    hyperplanes.pop_back();
    return p;
}





/**
 * @brief   Find the distance that the hyper-plane can move
 * @return  The distance / the interval
 */
double hyperplane_set::find_interval()
{
    int M = hyperplanes.size();
    int D = hyperplanes[0]->dim;

    // D + 2variables: D for dim, 2 for additional var for feasible
    int* ia = new int[1 + (D + 1) * M];  //TODO: delete
    int* ja = new int[1 + (D + 1) * M];  //TODO: delete
    double* ar = new double[1 + (D + 1) * M];   //TODO: delete
    int i, j;

    glp_prob *lp;
    lp = glp_create_prob();
    glp_set_prob_name(lp, "interval");
    glp_set_obj_dir(lp, GLP_MIN);


    glp_add_rows(lp, M);  // add D rows: q_1...q_D
    for (i = 1; i < M; i++)
    {
        char buf[10];
        sprintf(buf, "q%d", i);
        glp_set_row_name(lp, i, buf);
        glp_set_row_bnds(lp, i, GLP_UP, 0, - hyperplanes[i - 1]->offset); // qi = 0
    }
    glp_set_row_bnds(lp, M, GLP_UP, 0, hyperplanes[i - 1]->offset);


    glp_add_cols(lp, D + 1);    // add D columns: v[1] ... v[D]
    for (i = 1; i <= D + 1; i++)
    {
        char buf[10];
        sprintf(buf, "v%d", i);
        glp_set_col_name(lp, i, buf);
        glp_set_col_bnds(lp, i, GLP_LO, 0.0, 0.0); // 0 <= v[i] < infty

        glp_set_obj_coef(lp, i, 0);  // objective: 0
    }
    glp_set_obj_coef(lp, D + 1, 1);

    int counter = 1;
    // set value on row q1 ... qD
    for (i = 1; i < M; i++)
    {
        for (j = 1; j <= D + 1; j++)
        {
            ia[counter] = i; ja[counter] = j;
            if(j <= D)
                ar[counter++] = hyperplanes[i - 1]->norm[j - 1];
            else
                ar[counter++] = 0;
        }
    }
    ar[counter - 1] = -1;
    for (j = 1; j <= D + 1; j++)
    {
        ia[counter] = i; ja[counter] = j;
        if(j <= D)
            ar[counter++] = - hyperplanes[M - 1]->norm[j - 1];
        else
            ar[counter++] = 0;
    }
    // loading data
    glp_load_matrix(lp, counter - 1, ia, ja, ar);

    // running simplex
    glp_smcp parm;
    glp_init_smcp(&parm);
    parm.msg_lev = GLP_MSG_OFF; // turn off all message by glp_simplex
    glp_simplex(lp, &parm);

    int w = glp_get_status(lp);
    double interv = -100;
    //double w = glp_get_obj_val(lp);
    //std::cout << w << "  " << glp_get_col_prim(lp, 0 + 1) << "\n";
    if(w == GLP_OPT)
    {
        interv = glp_get_obj_val(lp);
    }
    else
    {
        interv = 99999;
    }


    glp_delete_prob(lp); // clean up
    delete[] ia;
    delete[] ja;
    delete[] ar;

    return interv / hyperplanes[M - 2]->normLength;
}

bool hyperplane_set::check_point_inside(point_t *p, double dis)
{
    for(int i = 0; i < hyperplanes.size(); ++i)
    {
        if(hyperplanes[i]->check_distance_withSign(p) > dis)
            return false;
    }
    return true;
}


