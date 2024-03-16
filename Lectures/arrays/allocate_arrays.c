#include <stdlib.h>
#include <stdio.h>

int main(int args, char* argv[]) {

    // statically allocated array - no pointers involved 
    /*
    int arr[3][3] = {
        {1, 2, 3}, 
        {1, 2, 3}, 
        {1, 2, 3}
    };
    */

    //dynamically allocate 
    int i;
    int** arr = malloc(sizeof(int*) * 3); 
    for (i = 0; i < 3; i++) {
        arr[i] = malloc(sizeof(int) * 3); 
    }
    arr[0][0] = 1;
    arr[0][1] = 2;
    // ...

    //to free we need to undo what we have done

    free (i = 0; i < 3; i++) {
        free(arr[i]); 
        arr[i] = NULL;
    }

    free(arr);
    arr = NULL; 

    return 0; 
}
