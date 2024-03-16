// Implementation of the File System ADT
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
#include "Fs.h"
#include "utility.h"


// Stage 0

Fs FsNew(void) {

    // Create and initialise a new struct FsRep. - create a new file system.
    Fs fs = malloc(sizeof(*fs));
    
    if (fs == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    

    //Create a root file at the top of the directory containing filename '/'. 
    File root_file = malloc(sizeof(*root_file));
    root_file->file_type = DIRECTORY;
    root_file->level = 0;
    root_file->path_to_file = "/";
    root_file->file_name = "/";
    root_file->text = NULL;
    root_file->child_file = NULL;
    root_file->next_file = NULL;
    
    //Need the file system to point at this root.
    
    fs->root_file = root_file;
    fs->cwd_file = root_file;
    
    return fs;
}

void FsGetCwd(Fs fs, char cwd[PATH_MAX + 1]) {
    // TODO
    strcpy(cwd, fs->cwd_file->path_to_file); 
}

void FsFree(Fs fs) {
    // TODO: Need to iterate through the FS, remove each file and then remove the FS as a whole.
    free_fs(fs->root_file);
    free(fs);
    return;
}


// STAGE 1

//Make a directory in fs.
void FsMkdir(Fs fs, char *path) {

    //Check if file arealy exists at the given path.

    //A prefix of the path is a regular file.
    char *path_to_parent_file = get_path_level(path, get_file_level(path)-1); //get path to parent using splitstring()
    File parent_file = get_last_file_in_path(fs->root_file, path_to_parent_file);
    if (parent_file->file_type == REGULAR_FILE) {
        printf("mkdir: cannot create directory 'path': Not a directory");
        return;
    }
    //A proper prefix of the path does not exist. 

    char *canon_path;

    canon_path = fix_path(path);

    File new_file = make_file(fs, DIRECTORY, canon_path);

    insert_file(fs, new_file, canon_path);
    
    return;
}

// Make a regular file in fs.
void FsMkfile(Fs fs, char *path) {

    //Check if file arealy exists at the given path.

    //A prefix of the path is a regular file.
    char *path_to_parent_file = get_path_level(path, get_file_level(path)-1); //get path to parent using splitstring()
    File parent_file = get_last_file_in_path(fs->root_file, path_to_parent_file);
    if (parent_file->file_type == REGULAR_FILE) {
        printf("mkdir: cannot create directory '%s': Not a directory", path);
        return;
    }

    //A proper prefix of the path does not exist. 

    char *canon_path;

    canon_path = fix_path(path);

    File new_file = make_file(fs, REGULAR_FILE, canon_path);

    insert_file(fs, new_file, canon_path);

    return;

}

// Change the cwd to the specific path given.
void FsCd(Fs fs, char *path) {

    char *path_to_parent_file = get_path_level(path, get_file_level(path)-1); //get path to parent using splitstring()
    File parent_file = get_last_file_in_path(fs->root_file, path_to_parent_file);
    if (parent_file->file_type == REGULAR_FILE) {
        printf("mkdir: cannot create directory '%s': Not a directory", path);
        return;
    }

    if (path == NULL) {
        fs->cwd_file = fs->root_file;
        return;
    }

    char *canon_path;

    canon_path = fix_path(path);

    fs->cwd_file = get_last_file_in_path(fs->root_file, canon_path);//return the file that the path is pointing at.
    
}

//Print the names of all the files in the directory that the path refers to. 
//need to consider regular files vs directories later as well.
void FsLs(Fs fs, char *path) {
    
    char *canon_path;
    
    canon_path = fix_path(path);
    
    File file = NULL; 

    if (canon_path == NULL) { 
        file = fs->cwd_file; 
    } else {
        file = get_last_file_in_path(fs->root_file, canon_path);
    }

    if (file->file_type == REGULAR_FILE) {
        printf("%s\n", path); 
    
    } else {
        for (File child = file->child_file; child != NULL; child = child->next_file) {
            if (child->next_file == NULL) {
                printf("%s\n", child->file_name);
            } else {
                printf("%s/", child->file_name);
            }
        }
       
    }
}

// This function prints the canonical path of the cwd. 
void FsPwd(Fs fs) {

    printf("%s\n", fs->cwd_file->path_to_file);
}

void FsTree(Fs fs, char *path) {
    /*
    File file = NULL;
    
    if (path == NULL) {
        file = fs->root_file;
    } else {
        path = fix_path(path);
        file = get_last_file_in_path(fs->root_file, path);
    }

    char *path_to_parent_file = get_path_level(path, get_file_level(path)-1); //get path to parent using splitstring()
    File parent_file = get_last_file_in_path(fs->root_file, path_to_parent_file);
    if (parent_file->file_type == REGULAR_FILE) {
        printf("tree: '%s': Not a directory", path);
        return;
    }
    else {
        //try to recursively print the tree here. TODO.
    }
    */
}

void FsPut(Fs fs, char *path, char *content) {
    // TODO
}

void FsCat(Fs fs, char *path) {
    // TODO
}

void FsDldir(Fs fs, char *path) {
    // TODO
}

void FsDl(Fs fs, bool recursive, char *path) {
    // TODO
}

void FsCp(Fs fs, bool recursive, char *src[], char *dest) {
    // TODO
}

void FsMv(Fs fs, char *src[], char *dest) {
    // TODO
}

