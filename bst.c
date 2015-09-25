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
	// Initially point to root node
	bsn_t *p_current = tree->root;
	
	// Initialize new node in tree
	bsn_t *p_new_node = (bsn_t *)malloc(sizeof(bsn_t));
	p_new_node->val = val;
	p_new_node->left = p_new_node->right = NULL;
	
	// Scenario 1: empty tree
	if(tree->size == 0){
		// Root node is the new node
		tree->root = p_new_node;
		tree->size += 1;
		return __TRUE;
	}

	// Scenario 2: non-empty tree; check if val already exists in tree
	while(p_current->val != val){
		// Check if must insert into left sub-tree
		if(val < p_current->val){
			// Check if left sub-tree is empty or not
			if(p_current->left == NULL){
				// Set left child as new node
				p_current->left = p_new_node;
				tree->size += 1;
				return __TRUE;
			}
			else{
				p_current = p_current->left;
			}
		}
		// Else insert into right sub-tree
		else{
			// Check if right sub-tree is empty or not
			if(p_current->right == NULL){
				// Set right child as new node
				p_current->right = p_new_node;
				tree->size += 1;
				return __TRUE;
			}
			else{
				p_current = p_current->right;
			}
		}
	}

	// Value already exists
	return __FALSE;
}

S32 bst_min( bst_t *tree ) {
	// Initially point to root node
	bsn_t *p_current = tree->root;
	
	// Empty tree
	if(tree->size == 0){
		return INT_MAX;
	}
	// Keep traversing to the left-most node
	while(p_current->left != NULL){
		p_current = p_current->left;
	}

	return p_current->val;
}

S32 bst_max( bst_t *tree ) {
	// Initially point to root node
	bsn_t *p_current = tree->root;
	
	// Empty tree
	if(tree->size == 0){
		return INT_MIN;
	}
	// Keep traversing to the right-most node
	while(p_current->right != NULL){
		p_current = p_current->right;
	}
	
	return p_current->val;
}

bool bst_erase( bst_t *tree, S32 val ) {
	// Initially point to root node
	bsn_t *p_current = tree->root;
	// Initialize pointer to parent node of node-to-erase
	bsn_t *p_parent = NULL;
	
	// Empty tree
	if(tree->size == 0){
		return __FALSE;
	}
	
	// Locate node-to-erase
	while(p_current != NULL && p_current->val != val){
		// Update parent node
		p_parent = p_current;
		// Which direction to traverse, depending on val
		if(val < p_current->val){
			p_current = p_current->left;
		}
		else{
			p_current = p_current->right;
		}
	}

	// Return false if val not found in tree
	if(p_current == NULL){
		return __FALSE;
	}
	
	// Scenario 1: leaf node
	if(p_current->left == NULL && p_current->right == NULL){
		// In the case that it is the only node in the tree
		if(p_current == tree->root){
			tree->root = NULL;
			free(p_current);
			p_current = NULL;
			tree->size -= 1;
		}
		else{
			// Check which child of parent is the current node - left or right?
			if(p_current->val < p_parent->val){
				p_parent->left = NULL;
			}
			else{
				p_parent->right = NULL;
			}
			free(p_current);
			p_current = NULL;
			tree->size -= 1;
		}
		return __TRUE;
	}
	
	// Scenario 2: one child
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
			if(p_current->val < p_parent->val){
				if(p_current->left != NULL){
					p_parent->left = p_current->left;
				}
				else{
					p_parent->left = p_current->right;
				}	
			}
			else{
				if(p_current->left != NULL){
					p_parent->right = p_current->left;
				}
				else{
					p_parent->right = p_current->right;
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
