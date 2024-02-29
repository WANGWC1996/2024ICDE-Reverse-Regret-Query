#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include "define.h"

// R-tree related data structures
typedef struct rtree_info_s
{
	int m, M, dim, reinsert_p, no_histogram;
	int extra_level;
} rtree_info;

// R-tree related data structures
typedef struct node {
	R_TYPE *a;
	R_TYPE *b;
	int id;
	int attribute;
	int vacancy;
	struct node *parent;
	struct node **ptr;
	int dim;
    int num;

} node_type;

// R-tree related data structures
struct nodeCmp
{
	bool operator()(const node_type* lhs, const node_type* rhs) const
	{
		double dist1 = 0, dist2 = 0;
		for (int i = 0; i < lhs->dim; i++)
		{
			dist1 += lhs->b[i];
			dist2 += rhs->b[i];
		}

		return dist1 < dist2;
	}
};

// R-tree related data structures
typedef struct NN {
	double dist;
	int oid;
	struct node *pointer;
	int level;
	struct NN *next;
} NN_type;

// R-tree related data structures
typedef struct BranchArray {
	double min;
	node_type *node;
} ABL;

// R-tree related data structures
typedef struct config_rt {
	int dim;
	int m;
	int M;
	int reinsert_p;
	int no_histogram;
	//char nodefile[FILENAME_MAX];
	//char rootfile[FILENAME_MAX];
	char queryfile[FILENAME_MAX];
	char positionfile[FILENAME_MAX];
	char save_tree_file[FILENAME_MAX];
}   config_type;

// R-tree related data structures
struct setNode_s
{
	int noOfNode;
	node_type **elt;
	int *level;
};

typedef struct setNode_s setNode;
#endif