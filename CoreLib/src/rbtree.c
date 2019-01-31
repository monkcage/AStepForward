#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

void rbtreeInit(TreeRoot* tree)
{
	tree->root = NULL;
}

void rbtreeNodeInit(TreeNode* node)
{
	node->left   = NULL;
	node->right  = NULL;
	node->parent = NULL;
	node->color  = RB_RED;
}

BOOL rbtreeNodeInsert(TreeRoot* tree, TreeNode* node) 
{
	if(node == NULL) {
		return FALSE;
	}

	TreeNode*  parent = tree->root;
	while(1) {
		if(parent->data > node->data) {
			if(parent->left == NULL) {
				parent->left = node;
				node->parent = parent;
				break;
			}
			parent = parent->left;
		} else if(parent->data < node->data) {
			if(parent->right == NULL) {
				parent->right = node;
				node->parent = parent;
				break;
			}
			parent = parent->right;
		} else {
			free(node);
			return FALSE;
		}
	}
	return TRUE;
}

static BOOL isRed(TreeNode* node) 
{
	return node && node->color == RB_RED;
}

static BOOL isBlack(TreeNode* node) 
{
	return node && node->color == RB_BLACK;
}

static void leftRotate(TreeRoot* tree, TreeNode* node) 
{
	if(tree == NULL || node == NULL) {
		return ;
	}

	//TreeNode* left   = node->left;
	TreeNode* parent = node->parent; 
	TreeNode* right  = node->right;
    TreeNode* gleft  = right->left;

	node->parent = right;
	right->left = node;

	node->right = gleft;
	if(gleft != NULL) {
		gleft->parent = node;
	}

	right->parent = parent;
	if(parent != NULL) {
		if(parent->left == node) {
			parent->left = right;
		} else {
			parent->right = right;
		}

	} else {
		tree->root = right;
	}
}

static void rightRotate(TreeRoot* tree, TreeNode* node)
{
	if(tree == NULL || node == NULL) {
		return ;
	}

	TreeNode* parent = node->parent;
	TreeNode* left   = node->left;
	TreeNode* gright = left->right;
	node->parent = left;
	left->right = node;
	node->left = gright;
	if(gright != NULL) {
		gright->parent = node;
	}
	left->parent = parent;
	if(parent != NULL) {
		if(parent->right == node) {
			parent->right = left;
		} else {
			parent->left = left;
		}
	} else {
		tree->root = left;
	}
}

static void rbtreeAdjust(TreeRoot* tree, TreeNode* node)
{
	if(tree == NULL || node == NULL) {
		return ;
	}

	// If tree is NULL, 
	if(node->parent == NULL) {
		node->color = RB_BLACK;  
		return ;
	}

	// If parent's color is black, insert directly;
	if(node->parent->color == RB_BLACK) {
		return;
	}

	TreeNode* parent = node->parent;
	TreeNode* gparent = parent->parent;
	TreeNode* uncle   = (gparent->left == parent) ? gparent->right :gparent->left;  
	// If parent's color is red,
	// 1) Uncle's color is red,
	if(isRed(uncle)) {
		parent->color = RB_BLACK;
		uncle->color  = RB_BLACK;
		gparent->color= RB_RED;
        rbtreeAdjust(tree, gparent);
		return ;
	}

	// 2) Uncle's color is black;
	if(node == parent->left && parent == gparent->left/*gparent->left->left == node*/) {
		parent->color = RB_BLACK;
		gparent->color = RB_RED;
		rightRotate(tree, gparent);
		return ;
	} else if(node == parent->right && parent == gparent->right/*gparent->right->right == node*/) {
		parent->color = RB_BLACK;
		gparent->color = RB_RED;
		leftRotate(tree, gparent);
		return ;
	} else if(node == parent->right && parent == gparent->left/*gparent->left->right == node*/) {
        node->color = RB_BLACK;
		gparent->color = RB_RED;
		leftRotate(tree, parent);
		rightRotate(tree, gparent);
		return ;
	} else if(node == parent->left && parent == gparent->right/*gparent->right->left == node*/) {
        node->color = RB_BLACK;
		gparent->color = RB_RED;
		rightRotate(tree, parent);
		leftRotate(tree, gparent);
		return ;
	}
}

void rbtreeValueInsert(TreeRoot* tree, int val)
{
	//printf("entry value insert\n");
	TreeNode* node = (TreeNode*)malloc(sizeof(*node));
	rbtreeNodeInit(node);
	node->data = val;
	if(tree->root != NULL) {
	//	printf("tree is not NULL\n");
		if(rbtreeNodeInsert(tree, node)){
			rbtreeAdjust(tree, node);
		}
	} else {
	//	printf("insert head node\n");
		tree->root  = node;
		node->color = RB_BLACK;
		return ; 
	}
//	printf("leave value insert\n");
}

static void rbtreeNodePrint(FILE* fp, TreeNode* node)
{
	if(node == NULL){
		return;
	}

	const char* color = (node->color == RB_RED) ? "red" : "black";
	fprintf(fp, "node[shape=record,style=filled,color=%s,fontcolor=white]; %d[label=\"<f0>|<f1> %d|<f2>\"];\n", color, node->data, node->data);
	if(node->parent){
		if(node == node->parent->left){
			fprintf(fp, "%d:f0:sw->%d:f1;\n", node->parent->data, node->data);
		} else {
			fprintf(fp, "%d:f2:se->%d:f1;\n", node->parent->data, node->data);
		}
	}

	rbtreeNodePrint(fp, node->left);
	rbtreeNodePrint(fp, node->right);
}

void rbtreeShow(TreeRoot* tree, const char* filename)
{
	if(tree->root == NULL) {
		return ;
	}

	FILE* fp = fopen(filename, "w");
	fprintf(fp, "digraph G{\n");
	rbtreeNodePrint(fp, tree->root);
	fprintf(fp, "}\n");
	fclose(fp);
	char cmd[1024];
	sprintf(cmd, "dot %s -Tpng -o %s.png", filename, filename);
	popen(cmd, "r");
}
/*
** Red-Black tree's delete :
**    Tips: 1)It is impossible that the target node to be removed has two child;
**          2)If the node has one child, the child's color must be red;
** 1) If the target node's color is red, then , it must be that the node has no child,
**    can be removed directly.
**
** 2) If the target node's color is black :
*8    2.1) Has a red child;
**    2.2) Has no child;
**         2.2.1) Has a red brother, then the parent node must be black,
**
**
**
*/
static TreeNode* findNode(TreeRoot* tree, int val)
{
	if(tree == NULL) {
		return NULL;
	}

	TreeNode* root = tree->root;
	while(1) {
		if(root == NULL) {
			break;
		}
		if(root->data == val) {
			return root;
		}
		root = (root->data > val) ? root->left : root->right; 
	}
	return NULL;
}

static TreeNode* findRemoveNode(TreeRoot* tree, TreeNode* node)
{
	if(tree == NULL || node == NULL) {
		// do something
		return NULL;
	}

	TreeNode* target = node;
	if(target->left != NULL) {
		target = target->left;
		while(target->right != NULL) {
			target = target->right;
		}
		return target;
	} else if(target->right != NULL) {
		target = target->right;
		while(target->left != NULL) {
			target = target->left;
		}
		return target;
	}
	return target;
}

static void removeAdjust(TreeRoot* tree, TreeNode* node)
{
	if(node->parent == NULL) {
		node->color = RB_BLACK;
		return ;
	}

	// 2.2) Has no child
 	// 2.2.1)If the brother's color is red, his child and parent's color must be black;
	TreeNode* parent = node->parent;
	TreeNode* brother = (parent->left == node) ? parent->right : parent->left;
	if(isRed(brother) && brother != NULL) {
		(brother == parent->left) ? rightRotate(tree, parent) : leftRotate(tree, parent);
		brother->color = RB_BLACK;
		parent->color = RB_RED;
//		removeAdjust(tree, node);          /////
		return;
	}

    // 2.2.2)If the brother's color is black, has no child, 
	//       and the parent's color is red
	TreeNode* lchild = brother->left;
	TreeNode* rchild = brother->right;
	if(isRed(parent) && isBlack(lchild) && isBlack(rchild)) {
		parent->color = RB_BLACK;
		brother->color = RB_RED;
		return ;
	}

	// 2.2.3)If the brother's color is black, and parent and child's color is black;
	if(isBlack(parent) && isBlack(lchild) && isBlack(rchild)) {
		brother->color = RB_RED;
		removeAdjust(tree, parent);
		return ;
	}

	// 2.2.3) Futher nephew's color is red
	if(node == parent->left && isRed(rchild)) {
		leftRotate(tree, parent);
		rchild->color = parent->color;
		return ;
	} else if(node == parent->right && isRed(lchild)) {
		rightRotate(tree, parent);
		lchild->color = parent->color;
		return ;
	}

	// 2.2.4) Closer nephew's color is red
	if(node == parent->left && isRed(lchild)) {
		rightRotate(tree, brother);
		lchild->color = RB_BLACK;
		brother->color = RB_RED;
		removeAdjust(tree, node);
		return ;
	} else if(node == parent->right && isRed(rchild)) {
		leftRotate(tree, brother);
		rchild->color = RB_BLACK;
		brother->color = RB_RED;
		removeAdjust(tree, node);
		return;
	}
}

BOOL rbtreeValueRemove(TreeRoot* tree, int val)
{
	TreeNode* node = findNode(tree, val);
	if(node != NULL) {
		rbtreeNodeRemove(tree, node);
	} else {
		// do something;
		return FALSE;
	}
	return TRUE;
}

BOOL rbtreeNodeRemove(TreeRoot* tree, TreeNode* node)
{
 	TreeNode* target = findRemoveNode(tree, node);
	if(target == NULL) {
		return FALSE;
	}

	node->data = target->data;
	TreeNode* parent = target->parent;
	if(parent == NULL) {
		tree->root = NULL;
		free(target);
		return TRUE;
	}

	// If the target node's color is red, and has no child;
	if(isRed(target) && target->left == NULL && target->right == NULL) {
		(parent->left == target) ? (parent->left = NULL) : (parent->right = NULL);
		target->parent = NULL;
		free(target);
		target = NULL;
		return TRUE;
	}

	// If the target node's color is black,
	// 2.1) Has a red child;
	if(target->left != NULL || target->right != NULL) {
		if(parent->left == target) {
			parent->left = (target->left == NULL) ? target->right : target->left;
			parent->left->parent = parent;
			parent->left->color = RB_BLACK;
		} else {
			parent->right = (target->left == NULL) ? target->right : target->left;
			parent->right->parent = parent;
			parent->right->color = RB_BLACK;
		}
		return TRUE;
	}

	// 2.2) Has no child;
	removeAdjust(tree, target);
	parent = target->parent;
	parent->left == target ? (parent->left = NULL) : (parent->right = NULL);
	free(target);
	return TRUE; 
}
