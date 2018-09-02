/*
* AVL_v1.cpp
*
*  Created on: Dec 15, 2014
*      Author: http://www.cnblogs.com/skywang12345/p/3577360.html
*/
#include <iostream>

template<typename T>
class AVLTreeNode
{
public:
	T key;
	int height;
	AVLTreeNode *left;
	AVLTreeNode *right;

	AVLTreeNode(T value, AVLTreeNode *_left, AVLTreeNode *_right)
		: key(value),height(0),left(_left),right(_right)
	{}
};

template<typename T>
class AVLTree
{
private:
	AVLTreeNode<T> *mRoot;

public:
	AVLTree();
	~AVLTree();
	int height();
	int max(int a, int b);
	void preOrder();
	void inOrder();
	void postOrder();
	AVLTreeNode<T>* search(T key);
	AVLTreeNode<T>* iterativeSearch(T key);
	T minimum();
	T maximum();
	void insert(T key);
	void remove(T key);
	void destroy();
	void print();

private:
	int height(AVLTreeNode<T>* tree);
	void preOrder(AVLTreeNode<T>* tree) const;
	void inOrder(AVLTreeNode<T>* tree) const;
	void postOrder(AVLTreeNode<T>* tree) const;
	AVLTreeNode<T>* search(AVLTreeNode<T>* x, T key) const;
	AVLTreeNode<T>* iterativeSearch(AVLTreeNode<T>* x, T key) const;
	AVLTreeNode<T>* minimum(AVLTreeNode<T>* tree);
	AVLTreeNode<T>* maximum(AVLTreeNode<T>* tree);
	AVLTreeNode<T>* leftLeftRotation(AVLTreeNode<T>* k2);
	AVLTreeNode<T>* rightRightRotation(AVLTreeNode<T>* k1);
	AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* k3);
	AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>* k1);
	AVLTreeNode<T>* insert(AVLTreeNode<T>* tree, T key);
	AVLTreeNode<T>* remove(AVLTreeNode<T>* tree, AVLTreeNode<T>* z);
	void destroy(AVLTreeNode<T>* tree);
	void print(AVLTreeNode<T>* tree, T key, int direction);
};


template<typename T>
AVLTree<T>::AVLTree() : mRoot(NULL)
{
}

template<typename T>
AVLTree<T>::~AVLTree()
{
	destroy(mRoot);
}

template <class T>
int AVLTree<T>::max(int a, int b)
{
   return a>b ? a : b;
}

template<typename T>
void AVLTree<T>::destroy()
{
	destroy(mRoot);
}

template<typename T>
void AVLTree<T>::destroy(AVLTreeNode<T>* tree)
{
	if (tree == NULL)
		return;

	destroy(tree->left);
	destroy(tree->right);

	delete tree;
}

template<typename T>
int AVLTree<T>::height(AVLTreeNode<T>* tree)
{
	if (tree != NULL)
		return tree->height;

	return 0;
}

template<typename T>
int AVLTree<T>::height()
{
	return height(mRoot);
}

template<typename T>
void AVLTree<T>::preOrder()
{
	preOrder(mRoot);
	std::cout << std::endl;
}

template<typename T>
void AVLTree<T>::inOrder()
{
	inOrder(mRoot);
	std::cout << std::endl;
}

template<typename T>
void AVLTree<T>::postOrder()
{
	postOrder(mRoot);
	std::cout << std::endl;
}

template<typename T>
void AVLTree<T>::preOrder(AVLTreeNode<T>* tree) const
{
	if(tree == NULL)
		return;
	std::cout << tree->key << " ";
	preOrder(tree->left);
	preOrder(tree->right);
}

template<typename T>
void AVLTree<T>::inOrder(AVLTreeNode<T>* tree) const
{
	if(tree == NULL)
		return;
	inOrder(tree->left);
	std::cout << tree->key << " ";
	inOrder(tree->right);
}

template<typename T>
void AVLTree<T>::postOrder(AVLTreeNode<T>* tree) const
{
	if(tree == NULL)
		return;
	postOrder(tree->left);
	postOrder(tree->right);
	std::cout << tree->key << " ";
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::search(AVLTreeNode<T> *x, T key) const
{
	if(x == NULL)
		return NULL;
	else {
		if(key == x->key) {
			return x;
		} else {
			if (key < x->key) {
				return search(x->left, key);
			} else {
				return search(x->right, key);
			}
		}
	}
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::search(T key)
{
	return search(mRoot, key);
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::iterativeSearch(AVLTreeNode<T>* x, T key) const
{
	while(x != NULL && x->key != key)
	{
		if (key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	return x;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::iterativeSearch(T key)
{
	return iterativeSearch(mRoot, key);
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::minimum(AVLTreeNode<T>* tree)
{
	while(tree->left)
		tree = tree->left;

	return tree;
}

template<typename T>
T AVLTree<T>::minimum()
{
	AVLTreeNode<T> *p = minimum(mRoot);
	if (p != NULL)
		return p->key;

	return (T)NULL;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::maximum(AVLTreeNode<T>* tree)
{
	while(tree->right)
		tree = tree->right;

	return tree;
}

template<typename T>
T AVLTree<T>::maximum()
{
	AVLTreeNode<T> *p = maximum(mRoot);
	if (p != NULL)
		return p->key;

	return (T)NULL;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::leftLeftRotation(AVLTreeNode<T>* k2)
{
	AVLTreeNode<T>* k1;

	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;

	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), k2->height) + 1;

	return k1;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::rightRightRotation(AVLTreeNode<T>* k1)
{
	AVLTreeNode<T>* k2;

	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;

	k1->height = max(height(k1->right), height(k1->left)) + 1;
	k2->height = max(height(k2->right), k1->height) + 1;

	return k2;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>* k3)
{
	k3->left = rightRightRotation(k3->left);
	return leftLeftRotation(k3);
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>* k1)
{
	k1->right = leftLeftRotation(k1->right);
	return rightRightRotation(k1);
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>* tree, T key)
{
	if(tree == NULL) {
		tree = new AVLTreeNode<T>(key, NULL, NULL);
		if (tree == NULL) {
			std::cout << "ERROR: Create AVL tree node failed!" << std::endl;
			return NULL;
		}
	} else if(key < tree->key) {
		tree->left = insert(tree->left, key);
		if (height(tree->left) - height(tree->right) == 2) {
			if (key < tree->left->key)
				tree = leftLeftRotation(tree);
			else
				tree = leftRightRotation(tree);
		}
	} else if(key > tree->key) {
		tree->right = insert(tree->right, key);
		if (height(tree->right) - height(tree->left) == 2) {
			if (key > tree->right->key)
				tree = rightRightRotation(tree);
			else
				tree = rightLeftRotation(tree);
		}
	} else {
		std::cout << "ERROR: Add failed!" << std::endl;
	}

	tree->height = max(height(tree->left), height(tree->right)) + 1;
	return tree;
}

template<typename T>
void AVLTree<T>::insert(T key)
{
	mRoot = insert(mRoot, key);
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>* tree, AVLTreeNode<T>* z)
{
	if (tree == NULL || z == NULL)
		return NULL;

	if (z->key < tree->key) {
		tree->left = remove(tree->left, z);
		if (height(tree->right) - height(tree->left) == 2) {

		}
	} else if (z->key > tree->key) {
		tree->right = remove(tree->right, z);
	} else {
		if ((tree->left != NULL) && (tree->right != NULL)) {
			if (height(tree->left) > height(tree->right)) {
				AVLTreeNode<T>* max = maximum(tree->left);
				tree->key = max->key;
				tree->left = remove(tree->left, max);
			} else {
				AVLTreeNode<T>* min = minimum(tree->right);
				tree->key = min->key;
				tree->right = remove(tree->right, min);
			}
		} else {
			AVLTreeNode<T>* tmp = tree;
			tree = (tree->left != NULL) ? tree->left : tree->right;
			delete tmp;
		}
	}

	return tree;
}

template<typename T>
void AVLTree<T>::remove(T key)
{
	AVLTreeNode<T>* z;

	if ((z = search(mRoot, key)) != NULL)
		mRoot = remove(mRoot, z);
}

static int arr[] = {3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9};
#define TBL_SIZE(a) ((sizeof(a))/(sizeof(a[0])))

int main()
{
	AVLTree<int>* tree = new AVLTree<int>();

	for(unsigned int i = 0; i < TBL_SIZE(arr); ++i)
	{
		std::cout << arr[i] << " ";
		tree->insert(arr[i]);
	}

	std::cout << std::endl;

	tree->preOrder();
	tree->inOrder();
	tree->postOrder();

	return 0;
}
