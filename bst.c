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
	// Need another pointer for when node-to-erase has two sub-trees, in which case
	// you can either get the greatest value in the left sub-tree or the smallest
	// in the right sub-tree; let's call this 'offspring'. 
	bsn_t *p_offspring = NULL;
	// We will also need a pointer to the offspring's parent
	bsn_t *p_offspring_parent = NULL;

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
	
	// Scenario 1: node-to-erase is leaf node
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
	
	// Scenario 2: node-to-erase has one sub-tree
	// Given the previous 'if' condition, the following condition
	// is only TRUE when ONLY ONE of the two children is NULL
	else if (p_current->left == NULL || p_current->right == NULL){
		// In the case that the root node is to be erased
		if(p_current = tree->root){
			// Update new root node of tree
			if(p_current->left != NULL){
				tree->root = p_current->left;
				p_current->left = NULL;
			}
			else{
				tree->root = p_current->right;
				p_current->right = NULL;
			}
			free(p_current);
			tree->size -= 1;
			return __TRUE;
		}
		else{
			// Check which child of parent is the current node - left or right?
			if(p_current->val < p_parent->val){
				// Update child of current to now be a child of parent
				if(p_current->left != NULL){
					p_parent->left = p_current->left;
					p_current->left = NULL;
				}
				else{
					p_parent->left = p_current->right;
					p_current->right = NULL;
				}	
			}
			else{
				// Update child of current to now be a child of parent
				if(p_current->left != NULL){
					p_parent->right = p_current->left;
					p_current->left = NULL;
				}
				else{
					p_parent->right = p_current->right;
					p_current->right = NULL;
				}
			}
			free(p_current);
			tree->size -= 1;
			return __TRUE;	
		}
	}
	
	//Scenario 3: node-to-erase has two sub-trees
	else {
		// Choose to traverse to and retrive node with greatest value in left sub-tree
		p_offspring = p_current->left;
		p_offspring_parent = p_current;
		while(p_offspring->right != NULL){
			p_offspring_parent = p_offspring;
			p_offspring = p_offspring->right;
		}

		// p_offspring will either have only a left child or none, so we adjust its
		// parent's children accordingly
		if (p_offspring_parent->left == p_offspring) {
			p_offspring_parent->left = p_offspring->left;
		}
		else {
			p_offspring_parent->right = p_offspring->left;
		}

		// Now set p_offspring's children
		p_offspring->left = p_current->left;
		p_offspring->right = p_current->right;


		// Now adjust p_parent's children; there's two cases - p_current is either the
		// root node or not
		// In the case that the node-to-erase is the root node
		if(p_current == tree->root){
		    tree->root = p_offspring;
		}
		else {
			if (p_parent->left == p_current) {
				p_parent->left = p_offspring;
			}
			else {
				p_parent->right = p_offspring;
			} 
		}

		// Finally we free the node
		free(p_current);
		tree->size -= 1;
		return __TRUE;
	}

	return __FALSE;
}
