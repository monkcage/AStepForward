#ifndef _RBTREE_H_
#define _RBTREE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "common.h"

#define RB_RED      1
#define RB_BLACK    0

typedef struct TreeNode{
	struct TreeNode* left;
	struct TreeNode* right;
	struct TreeNode* parent;
	int              color;
	int              data;
}TreeNode;

typedef struct TreeRoot{
	TreeNode*    root;
}TreeRoot;

void rbtreeInit(TreeRoot* tree);
void rbtreeNodeInit(TreeNode* node);
BOOL rbtreeNodeInsert(TreeRoot* tree, TreeNode* node);
void rbtreeValueInsert(TreeRoot* tree, int value);
//void rbtreeAdjust(TreeRoot* tree, TreeNode* node);
void rbtreeShow(TreeRoot* tree, const char* filename);

BOOL rbtreeValueRemove(TreeRoot* tree, int value);
BOOL rbtreeNodeRemove(TreeRoot* tree, TreeNode* node);

#ifdef __cplusplus
}
#endif

#endif
