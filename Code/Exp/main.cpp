#include "structure/data_utility.h"
#include "structure/data_struct.h"
#include "structure/point_set.h"
#include "structure/define.h"
#include <vector>
#include <ctime>
#include <sys/time.h>
#include "GroundTruth/Groundtruth.h"
#include "Baseline/Baseline.h"
#include "2DSW/sw.h"
#include "HDSP/HDSP.h"
#include "HDSP/APC.h"
#include "LPCTA/lpcta.h"

int main(int argc, char *argv[])
{
    /**********************************
    Configuration setting
    **********************************/
    ifstream config("../config.txt"); //configuration file
    string AlgName; //algorithm name
    char data_name[MAX_FILENAME_LENG]; //dataset name
    int dim, k; //parameter k
    double epsilon; // threshold for k-regret
    double SampleSize; // distance for sampling
    config >> AlgName >> dim >> data_name >> k >> epsilon >> SampleSize;
    cout << AlgName << "  " << data_name << "  k:" << k << "   epsilon:" << epsilon
         << "   SampleSize:" << SampleSize << "\n";


    /**********************************
    Initialization (Point set D and query point q)
    **********************************/
    point_set *pSet = new point_set(data_name);
    hyperplane_set *R = new hyperplane_set(pSet->points[0]->dim - 1);
    R->setconvexhull();
    R->set_bounding_with_extremePoints();

    //R->buildRelationBetweenPoint(pSet);
    //pSet->refineBasedonRelation(k);
    R->Rkskyband(pSet, k);
    //pSet->write("../data/island_40.txt");
    point_t *q = new point_t(pSet->points[0]->dim);
    for(int i = 0; i < pSet->points[0]->dim; ++i)
        config >> q->attr[i];
    q->print();

    /**********************************
    Measurements
    **********************************/
    long mem_baseline = get_mem_usage();
    timeval t1; gettimeofday(&t1, 0);


    /**********************************
    Algorithms
    **********************************/
    if(AlgName == "2DSW")
    {
        twodsw(pSet, q, R, k, epsilon);
    }
    else if(AlgName == "APC")
    {
        APC(pSet, q, R, k, epsilon);
    }
    else if(AlgName == "APC-AC")
    {
        APC_Accuracy(pSet, q, R, k, epsilon, SampleSize);
    }
    else if(AlgName == "EPT")
    {
        HDSWLazy(pSet, q, R, k, epsilon);
    }
    else if(AlgName == "LPCTA")
    {
        LPcta(pSet, q, R, k, epsilon);
    }

    timeval t2; gettimeofday(&t2, 0);
    double time_cost = (double) t2.tv_sec + (double) t2.tv_usec / 1000000 - (double) t1.tv_sec - (double) t1.tv_usec / 1000000;
    cout << "Time: " << time_cost << "\n\n\n";
    //cout << get_mem_usage() - mem_baseline << "\n";
    delete pSet;

    /**********************************
    std::ofstream out_cp("../../result.txt");
    out_cp << time_cost;
    out_cp.close();
    **********************************/

    return 0;
}
