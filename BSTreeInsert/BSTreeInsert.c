
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

static BSTree newBSTNode(int value);

BSTree BSTreeInsert(BSTree t, int val) {
	// TODO

	if (t == NULL) {
		t = newBSTNode(val);
	} 
	else if (val < t->value) {
		t->left = BSTreeInsert(t->left, val);

	} 
	else if (val > t->value) {
		t->right = BSTreeInsert(t->right, val);
	}
	return t;
}

static BSTree newBSTNode(int value) {
	BSTree t = malloc(sizeof(*t));
	if (t == NULL) {
		fprintf(stderr, "Insufficient memory!\n");
		exit(EXIT_FAILURE);
	}
	t->value = value;
	t->left = NULL;
	t->right = NULL;
	return t;
}
