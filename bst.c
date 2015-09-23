#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "bst.h"

void bst_init( bst_t *tree ) {
	tree->root = NULL;
	tree->size = 0;
}

size_t bst_size( bst_t *tree ) {
	return tree->size;
}

bool bst_insert( bst_t *tree, S32 val ) {	
	bsn_t *p_current = tree->root;
	bsn_t new_node;
	new_node.val = val;
	new_node->left = new_node->right = NULL;
	
	if(tree->size == 0){
		tree->root = &new_node;
		tree->size = 1;
		return __TRUE;
	}
	while(p_current->val != val){
		if(val < p_current->val){
			if(p_current->left == NULL){
				p_current->left = &new_node;
				tree->size = tree->size + 1;
				return __TRUE;
			}
			else{
				p_current = p_current->left;
			}
		}
		else{
			if(p_current->right == NULL){
				p_current->right = &new_node;
				tree->size = tree->size + 1;
				return __TRUE;
			}
			else{
				p_current = p_current->right;
			}
		}
	}
	return __FALSE;
}

S32 bst_min( bst_t *tree ) {
	bsn_t *p_current = tree->root;
	
	if(tree->size == 0){
		return INT_MAX;
	}
	while(p_current->left != NULL){
		p_current = p_current->left;
	}
	return p_current->val;
}

S32 bst_max( bst_t *tree ) {
	bsn_t *p_current = tree->root;
	
	if(tree->size == 0){
		return INT_MIN;
	}
	while(p_current->right != NULL){
		p_current = p_current->right;
	}
	return p_current->val;
}

bool bst_erase( bst_t *tree, S32 val ) {
	bsn_t *p_current = tree->root;
	bsn_t *p_previous = NULL;
	
	if(tree->size == 0){
		return __FALSE;
	}
	
	while(p_current->val != val && p_current != NULL){
		if(val < p_current->val){
			p_previous = p_current;
			p_current = p_current->left;
		}
		else{
			p_previous = p_current;
			p_current = p_current->right;
		}
	}
	if(p_current == NULL){
		return __FALSE;
	}
	
	//Scenario 1 Leaf Node
	if(p_current->left == NULL && p_current->right == NULL){
		if(p_current == tree->root){
			free(p_current);
			p_current = tree->root = NULL;
			tree->size = 0;
		}
		else{
			if(p_current->val < p_previous->val){
				p_previous->left = NULL;
			}
			else{
				p_previous->right = NULL;
			}
		}
		free(p_current);
		p_current = NULL;
		tree->size = tree->size - 1;
		return __TRUE;
	}
	
	//Scenario 2 One Child
	else if (p_current->left == NULL || p_current->right == NULL){
		if(p_current = tree->root){
			if(p_current->left != NULL){
				tree->root = p_current->left;
			}
			else{
				tree->root = p_current->right;
			}
			free(p_current);
			tree->size = tree->size - 1;
			return __TRUE;
		}
		else{
			if(p_current->val < p_previous->val){
				if(p_current->left != NULL){
					p_previous->left = p_current->left;
				}
				else{
					p_previous->left = p_current->right;
				}	
			}
			else{
				if(p_current->left != NULL){
					p_previous->right = p_current->left;
				}
				else{
					p_previous->right = p_current->right;
				}
			}
			free(p_current);
			tree->size = tree->size - 1;
			return __TRUE;	
		}
	}
	
	//Scenario 3
	return __FALSE;
}
