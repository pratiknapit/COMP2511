// Binary Search Tree ADT Test 

#include <stlib.h>
#include <stdio.h>
#include <BSTree.h>

int main(void) {
    Tree myTree = newTree();
    myTree = TreeInsert(myTree, 55); 
    myTree = TreeInsert(myTree, 23);
    myTree = TreeInsert(myTree, 88);

    showTree(myTree);

    return 0;
}   