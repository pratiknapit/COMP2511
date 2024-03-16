
#include <stdio.h>
#include <stdlib.h>
#include "list_recursive.h"

void print_listR(struct node *list);

int main(int argc, char *argv[]) {
    struct node *list = NULL;
    int number;

    list = create_node(50, NULL);
    print_listR(list);



    return 0;
}

// Create a new struct node containing the specified data,
// and next fields, return a pointer to the new struct node.
struct node *create_node(int data, struct node *next) {
    struct node *n = malloc(sizeof (struct node));
    if (n == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    n->data = data;
    n->next = next;
    return n;
}

void print_list(struct node *list) {

    struct node *l; 
    for(l=list; l != NULL; l = l->next) {
        printf("%d \n", l->data);
    }

}

//recursively void

void print_listR(struct node *list) {
    if(list == NULL) {
        return;
    }
    else {
        printf("%d \n", list->data);
        print_listR(list->next);
    }
}

//NULL ?

// 45, 71, ? 

//recursively, not iteratively

struct node *append(struct node *list, int value) {

    if(list == NULL) {
        return create_node(value, NULL);
    }
    else {
        list->next = append(list->next, value);
        return list;

    }

}