// COMP2521 Assignment 1

// Written by:
// Date:

#ifndef UTILITY_H
#define UTILITY_H

// add your own #includes, #defines, typedefs, structs and
// function prototypes here



#define IS_TEXT_FILE 1
#define IS_DIRECTORY 0
#define MAX_PATH 4096

typedef struct file *File;
typedef struct FsRep *Fs;

int num_slashes(char *str);
bool starts_with(char *start_str, char*total_str);
bool check_if_parent(char *parent, char *child);
char* RemoveSubstring(char *parent, char *child);
#endif