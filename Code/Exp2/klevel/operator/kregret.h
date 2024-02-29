#ifndef K_LEVEL_KREGRET_H
#define K_LEVEL_KREGRET_H

#include "algorithm/level.h"


class kregret
{
public:
    static void single_query(level &idx, int k, vector<float> q, double epsilon);
    static void up_down_query(level &idx, int k, vector<float> q, double epsilon);
};


#endif //K_LEVEL_KREGRET_H
