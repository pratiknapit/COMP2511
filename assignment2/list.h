

// Implementation of a linked list for collecting urls 

#ifndef LIST_H
#define LIST_H 

#include <stdbool.h>

// Data structure used: 


typedef struct Node *node;

typedef struct List *list; 

typedef struct Node {
    char url_name[100]; //Assume that url is not more than 100 characters in length
    int index; 
    int word_counter; 
    float page_rank; 
    node next; 
} Node; 

typedef struct List { // pointer to the head of the list 
    int nelems; // number of urls in the list
    node head; // pointer to the head of the list 
} List;


// Functions used.

list new_list(); 
void free_list(list l);
void insert_url(list l, char *url);
int count_list(list l);
bool check_list(list l, char *url);
void print_url_list(list l); 


#endif 