#ifndef RTREE_H
#define RTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <vector>

#ifndef WIN32
#include <sys/resource.h>
#include <sys/times.h>
#include <unistd.h>
#endif

#include "data_struct.h"
#include "point_set.h"

void overflow(node_type *over_node, int over_level, int old_level, node_type
	*extra_node, node_type *root, rtree_info *aInfo);

void build_tree(node_type **root, R_TYPE **data, int no_data, rtree_info *aInfo);

node_type* contructRtree(point_set *P, std::vector<int> C_idx, rtree_info *aInfo);

node_type* contructRtree(point_set *C, rtree_info *aInfo);

point_set* BBSskyline(point_set* P);
#endif 

