
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int comp(Node a, Node b, int tolerance);

// Worst case time complexity of this solution: O(m * n)
int numSubsequences(List listA, List listB, int tolerance) {
    int num_seq = 0; // this is our counter for the number of sequence  
    Node first_A = listA->first;
    Node first_B = listB->first;

    while(1) {
        int compare = comp(first_A, first_B, tolerance);

        if (compare == -1) {
            return(num_seq);
        } else {
            num_seq = num_seq + compare;
        }

        first_A = first_B->next;
    }
}

int comp(Node a, Node b, int tolerance) {
    int total_match = 0;
    int match = 0;

    while(b != NULL) {
        if(a == NULL) {
            return(-1);
        }

        if (a->value == b->value) {
            match++;
        }
        total_match++;

        a = a->next;
        b = b->next;
    }

    if ((total_match - match) <= tolerance) {
        return 1;
    } else {
        return 0;
    }
}
