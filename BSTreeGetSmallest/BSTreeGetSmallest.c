
#include "BSTree.h"

#include <stdlib.h>

//assuming that the tree is in order, we only need to traverse to the most 
//left node to find the smallest value in the tree.

BSTree BSTreeGetSmallest(BSTree t) {
	// TODO

	if (t == NULL) {
		return NULL;
	} else if (t->left == NULL) {
		return t;
	} else {
		return BSTreeGetSmallest(t->left);
	}
}

