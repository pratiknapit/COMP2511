#include <stdio.h>


int fac(int x) {
    // BASE CASE
    if (x == 0) return 1;
    if (x == 1) return 1;

    //recursive step 
    return x * fac(x-1);
}

int main() {
    int result = fac(5);
    printf("%d \n", result);
    return 0;
}