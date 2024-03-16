#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "list.h"

// This file has been adapted by the ones I have used in the labs.

list new_list() {
   list l = malloc(sizeof(*l));
   if (l == NULL) {
      fprintf(stderr, "Insufficient memory\n");
      exit(EXIT_FAILURE);
   }

   l->nelems = 0;
   l->head = NULL; 
   
   return l;
}

void free_list(list l) {
    if (l == NULL) return; 
    
    struct Node *curr = l->head; 
    while (curr != NULL) {
        struct Node *temp = curr;
        curr = curr->next; 
        free(temp);
    }
    free(l); 
}

/*
int main(void) {

    list list1 = new_list(); 
    
    char *url = "url11";
    insert_url(list1, url);
    url = "url22";
    insert_url(list1, url);
    print_url_list(list1);
    printf("%d\n", list1->nelems); 


    return 0; 
}
*/

void insert_url(list l, char *url) {

    if (check_list(l, url) == true) {
        return; 
    }

    node n = malloc(sizeof(*n)); 

    if (n == NULL) {
        fprintf(stderr, "Insufficient memory\n");
        exit(EXIT_FAILURE);
    }

    n->next = NULL; 
    strcpy(n->url_name, url); 

    n->word_counter = 1; 
    n->page_rank = 0.0;

    if (l->head == NULL) {
        l->head = n; 
        n->index = 0; 
        l->nelems++; 
        return; 
    }

    node curr = l->head; 

    int i = 0; 
    while (curr->next != NULL) {
        curr = curr->next; 
        i++; 
    } 
    curr->next = n; 
    n->index = i+1;
    l->nelems++; 
    
    return;

}

int count_list(list l) {
    int i = 0; 
    node curr = l->head;
    while (curr != NULL) {
        curr = curr->next; 
        i++; 
    } 

    return i;
    
}

bool check_list(list l, char *url) {
    node curr = l->head;

    if (curr == NULL) {
        return false;
    }

    while (curr != NULL) {

        if (strcmp(curr->url_name, url) == 0) {
            return true; 
        }

        curr = curr->next;

    }

    return false; 
}

void print_url_list(list l) {
    node curr = l->head; 
    while (curr != NULL) {
        printf("%s\n", curr->url_name); 
        curr = curr->next; 
    }
}

