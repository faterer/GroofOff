/*
* RBTree_v1.cpp
*
*  Created on: Dec 18, 2014
*      Author: http://www.cnblogs.com/skywang12345/p/3624291.html
*/
#include <iostream>

enum RBTColor {
	RED,
	BLACK
};

template<typename T>
class RBTNode
{
public:
	RBTColor color;
	T key;
	RBTNode *left;
	RBTNode *right;
	RBTNode *parent;

	RBTNode(T value, RBTColor c, RBTNode *p, RBTNode *l, RBTNode *r)
		: color(c), key(value), left(l), right(r), parent(r)
	{}
};

template<typename T>
class RBTree
{
private:
	RBTNode<T> *mRoot;
public:
	RBTree();
	~RBTree();
	void preOrder();
	void inOrder();
	void postOrder();

	RBTNode<T>* search(T key);
	RBTNode<T>* iterativeSearch(T key);

	T minimum();
	T maximum();

	RBTNode<T>* successor(RBTNode<T> *x);
	RBTNode<T>* predecessor(RBTNode<T> *x);

	void insert(T key);
	void remove(T key);
	void destory();
	void print();
private:
	void preOrder(RBTNode<T>* tree) const;
	void inOrder(RBTNode<T>* tree) const;
	void postOrder(RBTNode<T>* tree) const;

	RBTNode<T>* search(RBTNode<T>* x, T key) const;
	RBTNode<T>* iterativeSearch(RBTNode<T>* x, T key) const;

	RBTNode<T>* minimum(RBTNode<T>* tree);
	RBTNode<T>* maximum(RBTNode<T>* tree);

	void leftRotate(RBTNode<T>* &root, RBTNode<T> *x);
	void rightRotate(RBTNode<T>* &root, RBTNode<T> *y);
	void insert(RBTNode<T>* &root, RBTNode<T>* node);
	void insertFixUp(RBTNode<T>* &root, RBTNode<T>* node);
	void remove(RBTNode<T>* &root, RBTNode<T> *node);
	void removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent);
	void destory(RBTNode<T>* &tree);
	void print(RBTNode<T>* tree, T key, int direction);
};

#define rb_parent(r)		((r)->parent)
#define rb_color(r)			((r)->color)
#define rb_is_red(r)		((r)->color==RED)
#define rb_is_black(r)		((r)->color==BLACK)
#define rb_set_red(r)		do{(r)->color=RED;}while(0)
#define rb_set_black(r)		do{(r)->color=BLACK;}while(0)
#define rb_set_parent(r,p)	do{(r)->parent=(p);}while(0)
#define rb_set_color(r,c)	do{(r)->color=(c);}while(0)

template<typename T>
void RBTree<T>::leftRotate(RBTNode<T>* &root, RBTNode<T> *x)
{
	RBTNode<T> *y = x->right;

	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;

	y->parent = x->parent;

	if(x->parent == NULL) {
		root = y;
	} else {
		if(x->parent->left == x)
			x->parent->left = y;
		else
			x->parent->right = y;
	}

	y->left = x;
	x->parent = y;
}

template<typename T>
void RBTree<T>::rightRotate(RBTNode<T>* &root, RBTNode<T> *y)
{
	RBTNode<T> *x = y->left;

	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;

	x->parent = y->parent;

	if (y->parent == NULL) {
		root = x;
	} else {
		if (y == y->parent->right)
			y->parent->right = x;
		else
			y->parent->left = x;
	}

	x->right = y;
	y->parent = x;
}

template<typename T>
void RBTree<T>::insert(T key)
{
	RBTNode<T> *z = NULL;
	if ((z = new RBTNode<T>(key, BLACK, NULL, NULL, NULL)) == NULL)
		return;

	insert(mRoot, z);
}

template<typename T>
void RBTree<T>::insert(RBTNode<T>* &root, RBTNode<T>* node)
{
	RBTNode<T> *y = NULL;
	RBTNode<T> *x = root;

	//1. RBT is a BST, insert node as a BST.
	while (x != NULL)
	{
		y = x;
		if (node->key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	node->parent = y;
	if (y != NULL)
	{
		if (node->key < y->key)
			y->left = node;
		else
			y->right = node;
	}
	else
		root = node;

	node->color = RED;
	insertFixUp(root, node);
}


template<typename T>
void RBTree<T>::insertFixUp(RBTNode<T>* &root, RBTNode<T> *node)
{
	RBTNode<T> *parent, *gparent;

	// if parent is exist and is red color
	while ((parent = rb_parent(node)) && rb_is_red(parent))
	{
		gparent = rb_parent(parent);

		//if parent is gparent's left child
		if (parent == gparent->left) {

			//case 1: uncle node is red
			RBTNode<T> *uncle = gparent->right;
			if(uncle && rb_is_red(uncle))
			{
				rb_set_black(uncle);
				rb_set_black(parent);
				rb_set_red(gparent);
				node = gparent;
				continue;
			}

			//case 2: uncle doesn't exist or uncle node is black and current node is right child
			if(parent->right == node)
			{
				RBTNode<T> *tmp;
				leftRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			//case 3: uncle doesn't exist or uncle node is black and current node is left child
			rb_set_black(parent);
			rb_set_red(gparent);
			rightRotate(root, gparent);
		}
		else //if parent is gparent's right child
		{
			//case 1: uncle node is red
			RBTNode<T> *uncle = gparent->left;
			if (uncle && rb_is_red(uncle))
			{
				rb_set_black(uncle);
				rb_set_black(parent);
				rb_set_red(gparent);
				node = gparent;
				continue;
			}

			//case 2: uncle doesn't exist or uncle node is black and current node is right child
			if (parent->left == node)
			{
				RBTNode<T> *tmp;
				rightRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			//case 3: uncle doesn't exist or uncle node is black and current node is left child
			rb_set_black(parent);
			rb_set_red(gparent);
			leftRotate(root, gparent);
		}
	}

	rb_set_black(root);
}

template<typename T>
void RBTree<T>::remove(T key)
{
	RBTNode<T> *node;

	if((node = search(mRoot, key)) != NULL)
		remove(mRoot, node);
}

template<typename T>
void RBTree<T>::remove(RBTNode<T>* &root, RBTNode<T> *node)
{
	RBTNode<T> *child, *parent;
	RBTColor color;

	//node has left and right child
	if ((node->left != NULL) && (node->right != NULL))
	{
		RBTNode<T> *replace = node;
		replace = replace->right;

		while (replace->left != NULL)
			replace = replace->left;

		if(rb_parent(node))
		{
			if(rb_parent(node)->left == node)
				rb_parent(node)->left = replace;
			else
				rb_parent(node)->right = replace;
		}
		else
		{
			root = replace;
		}

		child = replace->right;
		parent = rb_parent(replace);
		color = rb_color(replace);

		if (parent == node)
		{
			parent = replace;
		}
		else
		{
			if(child)
				rb_set_parent(child, parent);

			parent->left = child;
			replace->right = node->right;
			rb_set_parent(node->right, replace);
		}

		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;

		if(color == BLACK)
			removeFixUp(root, child, parent);

		delete node;
		return;
	}

	if(node->left != NULL)
		child = node->left;
	else
		child = node->right;

	parent = node->parent;
	color = node->color;

	if(child)
		child->parent = parent;

	if(parent)
	{
		if(parent->left == node)
			parent->left = child;
		else
			parent->right = child;
	}
	else
	{
		root = child;
	}

	if(color == BLACK)
		removeFixUp(root, child, parent);

	delete node;
}

template<typename T>
void RBTree<T>::removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent)
{
	RBTNode<T> *other;

	while((!node || rb_is_black(node)) && node != root)
	{
		if (parent->left == node)
		{
			other = parent->right;
			//case 1: node's brother other is red
			if (rb_is_red(other))
			{
				rb_set_black(other);
				re_set_red(parent);
				leftRotate(root, parent);
				other = parent->right;
			}

			//case 2: node's brother other's right and left child are black
			if((!other->left || rb_is_black(other->left))
				&& (!other->right || rb_is_black(other->right)))
			{
				rb_set_red(other);
				node = parent;
				parent =rb_parent(node);
			}
			else
			{
				//case 3: node's brother other's right child is black and left child is red
				if(!other->right || rb_is_black(other->right))
				{
					rb_set_black(other->left);
					rb_set_red(other);
					rightRotate(root, other);
					other = parent->right;
				}

				//case 4: node's brother other's right child is red and left child is whatever
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				rb_set_black(other->right);
				leftRotate(root, parent);
				node = root;
				break;
			}
		}
		else
		{
			other = parent->left;
			//case 1: node's brother other is red
			if (rb_is_red(other))
			{
				rb_set_black(other);
				re_set_red(parent);
				rightRotate(root, parent);
				other = parent->left;
			}

			//case 2: node's brother other's right and left child are black
			if((!other->left || rb_is_black(other->left))
				&& (!other->right || rb_is_black(other->right)))
			{
				rb_set_red(other);
				node = parent;
				parent =rb_parent(node);
			}
			else
			{
				//case 3: node's brother other's left child is black and right child is red
				if(!other->left || rb_is_black(other->left))
				{
					rb_set_black(other->right);
					rb_set_red(other);
					leftRotate(root, other);
					other = parent->left;
				}

				//case 4: node's brother other's left child is red and right child is whatever
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				rb_set_black(other->left);
				rightRotate(root, parent);
				node = root;
				break;
			}
		}
	}

	if(node)
		rb_set_black(node);
}



int main()
{
	return 0;
}
