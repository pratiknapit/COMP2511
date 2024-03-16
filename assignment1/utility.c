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

void free_fs(File file) {

    //Base Case
    if (file == NULL) {
        return;
    }

    //Recursively remove
    free_fs(file->child_file);
    free_fs(file->next_file);
    free(file);
}

File make_file(Fs fs, int file_type, char *path) {
    File file = malloc(sizeof(*file));
    file->file_type = file_type;
    file->level = get_file_level(path);//getlevel(on the file->path_to_file
    file->path_to_file = path;
    file->file_name = get_file_name(path);//getfilename(from the file->path_to_file)
    file->text = NULL;
    file->child_file = NULL;
    file->next_file = NULL; 

    return file;
}



void insert_file(Fs fs, File new_file, char *path) {
    //remove all extra slashes by a function called remove consecutive slashes.
    
    char *path_to_parent_file = get_path_level(path, new_file->level-1); //get path to parent using splitstring()
    File parent_file = get_last_file_in_path(fs->root_file, path_to_parent_file); //get you the parent file

    insert_in_order(parent_file, new_file); //insert new file given the parent file 
}

void insert_in_order(File parent_file, File new_file) {
    
    //Case 1: If parent file has no child file, then new file is the first child file
    if (parent_file->child_file == NULL) {
        parent_file->child_file = new_file;
        return;
    }

    //Case 2: There is already a child file present.
    else {
        File child = parent_file->child_file; 

        //smallest

        if (strcmp(new_file->file_name, child->file_name) < 0) {
            //then we need to add the new_file as the first child
            parent_file->child_file = new_file; 
            new_file->next_file = child;
            return;
        } 
            
        //This will give us the final child on the level.
        while (child->next_file != NULL) {
            child = child->next_file;
        }

        if(strcmp(new_file->file_name, child->file_name) > 0) {
            child->next_file = new_file; 
            return;
        }

        //inserting into the middle of a level.
        File file = parent_file->child_file;
        while (file->next_file != NULL) {
            if (strcmp(file->file_name, new_file->file_name) < 0 && strcmp(file->next_file->file_name, new_file->file_name) >= 0) {
                new_file->next_file = file->next_file; 
                file->next_file = new_file;
                return;
            }
            file = file->next_file;
        }
    }
    return;
}



char *get_path_level(char *path, int level) {

    if (strcmp(path, "/") == 0) {
        return path;
    }

    char *num = malloc(sizeof(char) * (PATH_MAX + 1));
    int slash = 0;

    if (level == 0) {
        num = "/";
        return num;
    }

    for (int i = 0; i < strlen(path); i++) {

        if (path[i] == '/' && i != 0) {
            slash++;
        }

        if (slash == level) {
            break;
        }
        num[i] = path[i];

    }

    return num; 
}

int get_file_level(char *path) {

    path = fix_path(path);

    if (strcmp(path, "/") == 0) {
        return 0;
    }

    int slash = 0;

    for (int i = 0; i < strlen(path); i++) {
        if (path[i] == '/') {
            slash++;
        }
    }
    return slash;
}

char *get_file_name(char *path) {
    if (strcmp(path, "/") == 0) {
        return path; 
    }
    char *word = strrchr(path, '/') + 1;
    return word;
}

File get_last_file_in_path(File file, char *path) {

    //base case for recursion 
    if (strcmp(path, file->path_to_file) == 0) {
        return file; //just return the cwd file
    }

    //Traverse through the ADT.
    for (File iter = file; iter != NULL; iter = iter->next_file) {
        if (strcmp(iter->path_to_file, get_path_level(path, iter->level)) == 0) {
            iter = iter->child_file;
            return get_last_file_in_path(iter, path);
        }
    }

    return NULL;

}

char *remove_consecutive_slashes(char *path) {

    char *temp = malloc(sizeof(char) * (PATH_MAX + 1));
    int j = 0;
    bool alpha = true;
    for (int i = 0; i < strlen(path); i++) {
        if (isalpha(path[i]) != 0) {
            alpha = true;
        }
        else if (path[i] == '/' && alpha == true) {
            temp[j] = path[i];
            j++; 
            alpha = false;
        } 
        if (alpha == true) {
            temp[j] = path[i]; 
            j++; 
        }
    }

    return temp;
}

char *add_root_to_path(char *path) { 
    char *abs = malloc(sizeof(char) * (PATH_MAX + 1));
    
    if (path[0] != '/') {
        abs[0] = '/';
        strcat(abs, path);
    } else {
        strcpy(abs, path); 
    }
    return abs;
}

char *fix_path(char *path) {
    if (path == NULL) {
        return path; 
    }
    char *abs = malloc(sizeof(char) * (PATH_MAX + 1));
    abs = remove_consecutive_slashes(path); 
    abs = add_root_to_path(abs);
    return abs;
}



