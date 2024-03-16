#include <stdio.h>
#include <stdlib.h>

long long add(int a, int b) {
    return a + b;
}

long long mul(int a, int b) {
    return a * b;
}

void exec(long long (*fun)(int, int)) {
    printf("%lld\n", fun(5, 7));
}

int main(int argc, char *argv[]) {

    exec(&mul);

    return 0; 
}