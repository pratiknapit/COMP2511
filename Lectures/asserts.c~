//Testing, now we can use asserts

//In Comp1511, we had: 
/*

	
#include <stdio.h>
 
int is_even(int num) {
    if (num % 2 == 0) {
        return 1; //Return true/even 
    }
    return 0;
}
 
void test_is_even() {
    if (is_even(2) != 1) {
        printf("Failed is_even(2)\n");
    }
    if (is_even(3) != 0) {
        printf("Failed is_even(3)\n");
    }
}
 
int main(int argc, char* argv[]) {
    test_is_even();
}

*/


// Now in Comp2521 we have asserts: 

	
#include <assert.h>
#include <stdio.h>
 
int is_even(int num) {
    if (num % 2 == 0) {
        return 1;
    }
    return 0;
}
 
void test_is_even() {
    assert(is_even(2) == 1);
    assert(is_even(3) == 0);
}
 
int main(int argc, char* argv[]) {
    test_is_even();
}
