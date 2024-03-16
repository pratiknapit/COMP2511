//New switch statments

//Comp1511

#include <stdio.h>
/*
int main(int argc, char* argv[]) {
    char input;
    scanf("%c\n", &input);
    if (input == 'W') {
        printf("Up\n");
    } else if (input == 'A') {
        printf("Left\n");
    } else if (input == 'S') {
        printf("Down\n");
    } else if (input == 'D') {
        printf("Right\n");
    } else {
        printf("Not valid\n");
    }
}
*/

//Comp2521 - switch statements 

int main(int argc, char* argv[]) {
    char input;
    scanf("%c", &input);
    switch (input) {
        case 'W': 
            printf("Up\n"); 
            break;
        case 'A': 
            printf("Left\n"); 
            break;
        case 'S': 
            printf("Down\n"); 
            break;
        case 'D': 
            printf("Right\n"); 
            break;
        default: 
            printf("Not valid\n");
    }
}
