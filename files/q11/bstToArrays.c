
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

void BSTreePrefix(BSTree t, char keys[]);
void getParents(BSTree t, int parents[], char keys[]);
int char_key(BSTree t, char keys[], char key);

// Worst case time complexity of this solution: O(n^2)
void bstToArrays(BSTree t, char keys[], int parents[], int leftSiblings[]) {
	// TODO

	BSTreePrefix(t, keys);
	getParents(t, parents, keys);

	return;
}

int key = 0;
void BSTreePrefix(BSTree t, char keys[]) {
	if (t == NULL) {
	return;
	}
	keys[key] = t->key;
	key++;
	BSTreePrefix(t->left, keys);
	BSTreePrefix(t->right, keys);
}

void getParents(BSTree t, int parents[], char keys[]) {
	if (t == NULL) {
		return;
	}

	
	if (t->left != NULL) {
		parents[char_key(t, keys, t->left->key)] = char_key(t, keys, t->key);
	} 
	if (t->right != NULL) {
		parents[char_key(t, keys, t->right->key)] = char_key(t, keys, t->key);
	} 
	
	
	getParents(t->left, parents, keys);
	getParents(t->right, parents, keys);

}

int char_key(BSTree t, char keys[], char key) {

	for (int a = 0; a < BSTreeNumNodes(t); a++) {
		if (keys[a] == key) {
			return a;
		}
	}
	return 0;
}

