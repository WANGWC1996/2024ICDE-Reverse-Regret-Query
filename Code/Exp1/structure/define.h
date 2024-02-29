#ifndef DEFINE_H
#define DEFINE_H

#include <math.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <iterator>
#include <string>
#include <map>
#include <fstream>
#include <sys/time.h>
#include <queue>


#define DIST_TYPE			double
#define PI					3.1415926
#define INF					100000000
#define	MAX_FILENAME_LENG	256

#define DEBUG 1


#define CONFIG_FILE	"rtree.config"
#define SAVE_RTREE_FILE "save_rtree_file"

#define FALSE    	0
#define TRUE     	1
#define COORD_TYPE	double

#define RANGE_SEARCH 0
#define kNN_SEARCH 1
#define CHOICE kNN_SEARCH

#define ASC_NUM  	48
#define NO_ID	 	-1
#define FOUND		1
#define NOT_FOUND 	0

#define ROOT  0
#define LEAF  1
#define NODE  2
#define EQN_EPS 1e-9
#define EQN2 1e-9
#define EQN3 1e-4
#define EQN4 1e-4
#define EQN6 1
#define EDGE 0
//#define INFINITY  FLT_MAX
//#define INFINITY  1E+37 //FLT_MAX
#define UNDEFINED -3  // for id of entries in PR

//#define R_FLOAT
//#define R_TYPE int
#define R_TYPE double
#define RAMDOM_C 1
#define RAMDOM_P 3
#define HEURISTIC 2

#define LABEL_LENGTH 150

// the domination options
#define HYPER_PLANE 1
#define CONICAL_HULL 2

// the skyline options
#define SQL 1
#define RTREE 2

//  the stopping options
#define NO_BOUND 1
#define EXACT_BOUND 2
#define APPROX_BOUND 3

//utility range
#define U_RANGE 1000

//updated range
#define UP_EPSIlON 1

#define Lnum 50 //number of children for spherical tree

//relation of node
#define SUM_TURN 1 //A + B = -C
#define SUM_KEEP 2 //A + B = C
#define ADD_TURN 3
#define ADD_KEEP 4





#endif //U_2_DEFINE_H
