#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#include <string>

using namespace std;

struct AVLNode
{
	AVLNode *parent, *left, *right;
	int height;
	matrix* value;
};

class AVL
{

	public:
	AVLNode *root;

	AVL(){
		this->root = NULL;
	};

	AVLNode* left_rotate(AVLNode *node_x)
	{
		AVLNode *node_y, *temp;
		node_y = node_x->right;
		node_y->parent = node_x->parent;
		node_x->parent = node_y;
		temp = node_y->left;
		node_y->left = node_x;
		node_x->right = temp;
		if(temp != NULL){
			temp->parent = node_x;
		}
		if(node_y->parent != NULL)
		{
			if(node_y->parent->left == node_x){
				node_y->parent->left = node_y;
			}else{
				node_y->parent->right = node_y;
			}
		}else{
			this->root = node_y;
		}
		node_x->height = this->height(node_x);
		node_y->height = this->height(node_y);
		return node_x;
	};

	AVLNode* right_rotate(AVLNode *node_y)
	{
		AVLNode *node_x, *temp;
		node_x = node_y->left;
		node_x->parent = node_y->parent;
		node_y->parent = node_x;
		temp = node_x->right;
		node_x->right = node_y;
		node_y->left = temp;
		if(temp != NULL){
			temp->parent = node_y;
		}
		if(node_x->parent != NULL)
		{
			if(node_x->parent->left == node_y){
				node_x->parent->left = node_x;
			}else{
				node_x->parent->right = node_x;
			}
		}else{
			this->root = node_x;
		}
		node_y->height = this->height(node_y);
		node_x->height = this->height(node_x);
		return node_y;
	};

	bool check_balance(AVLNode *node)
	{
		if(node == NULL)return true;
		int leftHeight, rightHeigh;
		if(node->right != NULL)
		{
			rightHeigh = node->right->height;
		}else{
			rightHeigh = -1;
		}
		if(node->left != NULL)
		{
			leftHeight = node->left->height;
		}else{
			leftHeight = -1;
		}
		if(leftHeight >= rightHeigh)
		{
			return (leftHeight-rightHeigh > 1) ? false : true;
		}else{
			return (rightHeigh-leftHeight > 1) ? false : true;
		}
	};

	void update_heights(AVLNode *node)
	{
		if(node == NULL)return;
		node->height = this->height(node);
		this->update_heights(node->parent);
	}

	int height(AVLNode *node)
	{
		if(node == NULL)return -1;
		int leftHeight, rightHeigh;
		if(node->right != NULL)
		{
			rightHeigh = node->right->height;
		}else{
			rightHeigh = -1;
		}
		if(node->left != NULL)
		{
			leftHeight = node->left->height;
		}else{
			leftHeight = -1;
		}
		return (leftHeight >= rightHeigh) ? leftHeight+1 : rightHeigh+1;
	};

	void insert(matrix* value)
	{
		AVLNode *node = new AVLNode;
		node->value = value;
		node->parent = NULL;
		node->left = NULL;
		node->right = NULL;
		AVLNode *current = this->root;
		if(this->root != NULL)
		{
			while(true){
				if(node->value->get_name() <= current->value->get_name())
				{
					if(current->left != NULL){
						current = current->left;
					}else{
						current->left = node;
						node->parent = current;
						break;
					}
				}else{
					if(current->right != NULL){
						current = current->right;
					}else{
						current->right = node;
						node->parent = current;
						break;
					}
				}
			}
			current = node;
			while(current->parent != NULL){
				current = current->parent;
				current->height = this->height(current);
			}
		}else{
			this->root = node;
			node->height = 0;
		}
		current = node;
		bool is_next_left = true /* left*/, is_prev_left = true /*left*/;
		while(current->parent != NULL)
		{
			if(current->parent->left == current)
			{
				is_prev_left = is_next_left;
				is_next_left = true;
			}else
			{
				is_prev_left = is_next_left;
				is_next_left = false;
			}
			bool flag = false;
			if(!this->check_balance(current->parent) && false)
			{
				/* case 0 : left left*/
				if(is_prev_left && is_next_left)
				{
					current = this->right_rotate(current->parent);
					flag = true;
					current = current->parent;
				}
				/* case 1 : left right*/
				if(!is_prev_left && is_next_left)
				{
					current = this->left_rotate(current);
					current = current->parent;
					current = this->right_rotate(current->parent);
					current = current->parent;
					flag = true;
				}
				/* case 2 : right right*/
				if(!is_prev_left && !is_next_left)
				{
					current = this->left_rotate(current->parent);
					flag = true;
					current = current->parent;
				}
				/* case 3 : right left*/
				if(is_prev_left && !is_next_left)
				{
					current = this->right_rotate(current);
					current = current->parent;
					current = this->left_rotate(current->parent);
					current = current->parent;
					flag = true;
				}
			}
			if(flag)
			{
				this->update_heights(current);
			}else{
				current = current->parent;
			}
		}
	};

	AVLNode* min(AVLNode *node)
	{
		AVLNode *current = node;
		bool flag = true;
		while(current->left != NULL){
			current = current->left;
			flag = false;
		}
		return flag ? node : current;
	};

	AVLNode* max(AVLNode *node)
	{
		AVLNode *current = node;
		bool flag = true;
		while(current->right != NULL){
			current = current->right;
			flag = false;
		}
		return flag ? node : current;
	};

	AVLNode* next_max(AVLNode *node)
	{
		if(node->right != NULL)
		{
			return this->min(node->right);
		}if(this->root == node){
			return NULL;
		}
		else if(node->parent->left == node){
			return node->parent;
		}else{
			AVLNode *current = node;
			while(current->parent != NULL && current->parent->right == current){
				current = current->parent;
			}
			if(current->parent != NULL){
				return current->parent;
			}
			return NULL;
		}
	};

	matrix* find(string name)
	{
		AVLNode* current = this->root;
		while(current != NULL)
		{
			string currentName = current->value->get_name();
			if(name == currentName)
			{
				return current->value;
			}else if(name < currentName){
				current = current->left;
			}else{
				current = current->right;
			}
		}
		return NULL;
	}

	void print()
	{
		AVLNode *current = NULL;
		if(this->root != NULL){
			current = this->min(this->root);
		}else{
			cout<<endl<<"---------------------- THE TREE IS EMPTY ------------------------";
		}
		while(current != NULL){
			current->value->print_matrix();
			//cout<<endl<<" at "<<current->height<<endl;
			current = this->next_max(current);
		}
		cout<<endl;
	}

};
