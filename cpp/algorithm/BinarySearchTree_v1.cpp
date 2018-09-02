/*
* BinarySearchTree.cpp
*
*  Created on: Dec 9, 2014
*      Author: mawang
*/
#include <iostream>
#include <limits.h>

struct node {
	int data;
	struct node *left;
	struct node *right;
};

static bool lookup(struct node *node, int target) {
	if (node == NULL) {
		return false;
	} else {
		if (target == node->data)
			return true;
		else {
			if (target < node->data)
				return lookup(node->left, target);
			else
				return lookup(node->right, target);
		}
	}
}

static struct node* newNode(int data) {
	struct node* node = new struct node();
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}

static struct node* insert(struct node* node, int data) {
	if(node == NULL) {
		return newNode(data);
	} else {
		if (data <= node->data)
			node->left = insert(node->left, data);
		else
			node->right = insert(node->right, data);

		return node;
	}
}

int size(struct node* node) {
	if (node == NULL) {
		return 0;
	} else {
		return size(node->left) + 1 + size(node->right);
	}
}

int maxDepth(struct node* node) {
	if (node == NULL) {
		return 0;
	} else {
		int	a = maxDepth(node->left);
		int	b = maxDepth(node->right);

		return a > b ? a + 1 : b + 1;
	}
}

int minValue(struct node* node) {
	struct node* current = node;

	while(current->left != NULL) {
		current = current->left;
	}

	return current->data;
}

int maxValue(struct node* node) {
	struct node* current = node;
	while(current->right != NULL) {
		current = current->right;
	}

	return current->data;
}

void printPreorder(struct node* node) {
	if (node == NULL)
		return;

	std::cout << node->data << " ";
	printPreorder(node->left);
	printPreorder(node->right);
}

void printInoder(struct node* node) {
	if (node == NULL)
		return;
	printInoder(node->left);
	std::cout << node->data << " ";
	printInoder(node->right);
}

void printPostorder(struct node* node) {
	if (node == NULL)
		return;
	printPostorder(node->left);
	printPostorder(node->right);
	std::cout << node->data << " ";
}

struct node* mirror(struct node* node) {
	if (node == NULL) {
		return node;
	} else {
		mirror(node->left);
		mirror(node->right);
		struct node* tmp = node->left;
		node->left = node->right;
		node->right = tmp;
		return node;
	}
}

void doubleTree(struct node* node) {
	struct node* oldLeft;
	if (node == NULL)
		return;

	doubleTree(node->left);
	doubleTree(node->right);
	oldLeft = node->left;
	node->left = newNode(node->data);
	node->left->left = oldLeft;
}

bool sameTree(struct node*a, struct node* b) {
	if (a == NULL && b == NULL)
		return true;
	else if (a != NULL && b != NULL)
		return (a->data == b->data)
				&& sameTree(a->left, b->left)
				&& sameTree(a->right, b->right);
	else
		return false;
}

bool isBST_v1(struct node* node) {
	if (node == NULL)
		return true;

	if (node->left != NULL && minValue(node->left) > node->data)
		return false;

	if (node->right != NULL && maxValue(node->left) <= node->data)
		return false;

	if (!isBST_v1(node->left) || !isBST_v1(node->right))
		return false;

	return true;
}

bool isBST_v2_Util(struct node* node, int min, int max) {
	if (node == NULL)
		return true;

	if (node->data < min || node->data > max)
		return false;

	return isBST_v2_Util(node->left, min, node->data) &&
			isBST_v2_Util(node->right, node->data+1, max);
}

bool isBST_v2(struct node* node) {
	return isBST_v2_Util(node, INT_MIN, INT_MAX);
}

int main()
{
	struct node *root = NULL;
	root = insert(root, 4);
	root = insert(root, 2);
	root = insert(root, 3);
	root = insert(root, 1);
	root = insert(root, 5);

	root = mirror(root);
	std::cout << sameTree(root, root) << std::endl;
	std::cout << size(root) << std::endl;
	std::cout << maxDepth(root) << std::endl;
	printInoder(root);
	std::cout << std::endl;
	printPostorder(root);
	std::cout << std::endl;
	printPreorder(root);
	return 0;
}


