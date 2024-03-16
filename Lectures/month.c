// Write a function monthName(int) that 
/*
accepts a month number 1=Jan, ..., 12=Dec
returns a string containing the month name 
assume that the string wil be read only 
use a switch to decide on the month 
*/

#include <assert.h>
#include <stdio.h> 
#include <string.h>

char* monthName(int monthNumber) {
    switch (monthNumber) {
        case 1: return "Jan";
        case 2: return "Feb";
        case 3: return "Mar";
        case 4: return "Apr";
        case 5: return "May";
        case 6: return "Jun";
        case 7: return "Jul";
        case 8: return "Aug";
        case 9: return "Sep";
        case 10: return "Oct";
        case 11: return "Nov";
        case 12: return "Dec";
        default: return NULL;
    }
}

int main(int argc, char* argv[]) {
    assert(strcmp(monthName(1), "Jan") == 0); //strcmp returns 0 if the 2 strings are the same
}