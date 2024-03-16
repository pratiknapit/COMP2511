// COMP2521 Assignment 1

// Written by:
// Date:

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileType.h"
#include "utility.h"

// implement the functions declared in utility.h here


int num_slashes(char *str) {
	int counter = 0;
	int length = strlen(str);
	char slash = '/';

	for (int i = 0; i < length; i++) {
		if (str[i] == slash) {
			counter ++;
		}
	}
	return counter;
}

//checks if child string starts with parent string
bool starts_with(char *start_str, char*total_str) {
	return strncmp(start_str, total_str, strlen(start_str)) == 0;
}
//Removes the parent substring and any slash in front, from child 
char *RemoveSubstring(char *parent, char *child) { 
    char *new = child;
	int parent_len = strlen(parent);
    if (strcmp(parent, "/") == 0) {
        new = new + parent_len;
    } else {
        new = new + parent_len + 1;
    }
    //printf("PARENT IS: %s, CHILD IS: %s , REMOVED IS: %s \n", parent, child, new);
	return new;
}

//checks if a file is a child of a parent by comparing their path strings
bool check_if_parent(char *parent, char *child) {
	bool is_parent = false;
	
	if (strlen(child) <= strlen(parent)) {
		return is_parent;
	}
	char *difference = RemoveSubstring(parent, child);
	if (starts_with(parent, child)) {
        if (num_slashes(difference) == 0) {
            is_parent = true;
        } 
    }
	return is_parent;
}