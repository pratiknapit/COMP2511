
#include <stdlib.h>

#include "tree.h"

int TreeSumOdds(Tree t) {

	if (t == NULL) {
		return 0;
	}

	int j = TreeSumOdds(t->left) + TreeSumOdds(t->right);

	if (t->value % 2 != 0) {
		return j + t->value;
	} else {
		return j;
	}

}

