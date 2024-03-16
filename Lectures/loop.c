#include <stdio.h>

int main(int argc, char* arg[]) {
    int sum = 0;
    for (int i = 1; i < 10; i++) { //use a for loop when there is a counter, use while for other loops.
        sum = sum + i;
    }
    printf("%d\n", sum);
    return 0; //returning 0 means the main function is a success -- it will still run without the return 0.
}