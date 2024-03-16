// COMP2521 Assignment 1

// Written by:
// Date:

#ifndef UTILITY_H
#define UTILITY_H

#define PATH_MAX 4096

// add your own #includes, #defines, typedefs, structs and
// function prototypes here

//Typedefs for structs.
typedef struct file *File; 
typedef struct FsRep *Fs;

//Structs: 

struct file {

    int file_type; //boolean check FileType.h

    int level; //level of file in FS

    char *path_to_file; //path to file

    char *file_name; // filename with no '/'

    //File parent_file; 

    char *text; //input into text file

    File child_file; //Pointer to child node/file

    File next_file; //Pointer to next node/file on same level

};

struct FsRep {

    //char *cwd_path; 

    File root_file;
    
    File cwd_file;

};

//Function prototypes here: 

void free_fs(File file);
File make_file(Fs fs, int file_type, char *path);
void insert_file(Fs fs, File new_file, char *path);
void insert_in_order(File parent_file, File new_file);
char *get_path_level(char *path, int level);
int get_file_level(char *path);
char *get_file_name(char *path);
File get_last_file_in_path(File file, char *path);
char *remove_consecutive_slashes(char *path);
char *add_root_to_path(char *path);
char *fix_path(char *path);
void print_tree_recursive(File file, int level);


#endif

