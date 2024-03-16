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

struct file {
    int file_type;
    //what directory level the file is on
    int level;
    char *path;
    //name is the parent string and any slashes removed FROM the file string
    char *name;
    char *text;

    File next_file;
    File child_file;
    File parent_file;
};

struct FsRep {
    //path for the current working directory
    char *current_path;
    //Root file for all directories
    File root_file;
    File current_file;
    bool path_has_been_found;
};

/*
Quick Helper Function for freeing
*/
void free_recursively(File curr_file) {
    if(curr_file == NULL) {
        return;
    }
    free_recursively(curr_file->child_file);
    free_recursively(curr_file->next_file);

    free(curr_file->path);
    free(curr_file);
}

//STAGE 0
Fs FsNew(void) {
    // TODO
    Fs new_fs = malloc(sizeof(*new_fs));
    new_fs->current_path = "/";

    //create the root file
    File root_file = malloc(sizeof(*root_file));
    root_file -> child_file = NULL;
    root_file -> next_file = NULL;
    root_file->file_type = IS_DIRECTORY;
    root_file->path = malloc(sizeof("/"));
    root_file->path[0] = '/';
    root_file->path[1] = '\0'; 
    root_file->level = 0;

    new_fs->root_file = root_file;
    new_fs->current_file = root_file;
    new_fs->path_has_been_found = false;
    return new_fs;
}

void FsGetCwd(Fs fs, char cwd[PATH_MAX + 1]) {
    // TODO
    strcpy(cwd, fs->current_file->path);
    return;
}

void FsFree(Fs fs) {
    // TODO
    free_recursively(fs->root_file);
    free(fs);
}

//STAGE 1

/*
HELPER FUNCTIONS HERE FOR STAGE 1
*/

//add a file in order
void addFileInOrder(File parent_file, File new_file) {
    //If empty, add as a child
    char *path = new_file->path;
    if (parent_file->child_file == NULL) {
        parent_file->child_file = new_file;
        return;
    }
    File curr_file = parent_file->child_file;
    File last_file = parent_file->child_file;
    //get last file
    while (last_file->next_file != NULL) {
        last_file = last_file->next_file;
    }
    //If less than first child file
    if (strcmp(path, curr_file->path) < 0) {
        parent_file->child_file = new_file;
        new_file->next_file = curr_file;
        
    //If more than last child file horizontally
    } else if (strcmp(path, last_file->path) > 0) {
        last_file->next_file = new_file;

    //If in between, insert it
    } else {
        while (curr_file != NULL) {
			if (strcmp(path, curr_file->next_file->path) < 0) {
				new_file->next_file = curr_file->next_file;
				curr_file->next_file = new_file;
				break;
			}
		}
    }
}

//search and add recursively.
//Uses: check_if_parent(), Remove_Substring() and addFileInOrder()
void SearchAndAddRecursively(File curr_file, char *child_path, File file_to_add) {
    if (curr_file != NULL) {
        if (check_if_parent(curr_file->path, child_path)) {
            file_to_add->parent_file = curr_file;
            file_to_add->level++;
            addFileInOrder(curr_file, file_to_add);
            return;
        }
        SearchAndAddRecursively(curr_file->child_file, child_path, file_to_add);
        SearchAndAddRecursively(curr_file->next_file, child_path, file_to_add);
    }
}

//print all elements recursively
void PrintAll(File curr_file) {
    //base case
    if (curr_file == NULL) {
        return;
    }
    //indent
    for (int i = 0; i < curr_file->level; i++) {
        printf("    ");
    }
    char *print_str;
    //If root-file, print / 
    if (strcmp(curr_file->path,"/") == 0) {
        print_str = "/";
    //Print without the parent substrings
    } else {
        print_str = RemoveSubstring(curr_file->parent_file->path, curr_file->path);
    }
    printf("%s \n", print_str);
    PrintAll(curr_file->child_file);
    PrintAll(curr_file->next_file);
}

void CheckIfAlreadyExists(File curr_file, char *path, Fs fs) {
    if (curr_file != NULL) {
        if (strcmp(curr_file->path, path) == 0) {
            fs->path_has_been_found = true;
            return;
        }
        CheckIfAlreadyExists(curr_file->child_file, path, fs);
        CheckIfAlreadyExists(curr_file->next_file, path, fs);
    }
}

/*
ACTUAL FUNCTIONS START HERE
*/
void FsMkdir(Fs fs, char *path) {
    // TODO
    File new_dir = malloc(sizeof(*new_dir));
    new_dir->next_file = NULL;
    new_dir->child_file = NULL;
    new_dir->file_type = IS_DIRECTORY;
    new_dir->parent_file = NULL;
    new_dir->path = malloc(sizeof(path)+ sizeof("/") + 3);
    new_dir->path[0] = '/';
    new_dir->path[1] = '\0'; 

    //Add the slash in front, if no slash
    if (path[0] != '/') {
        strcat(new_dir->path, path);
    } else {
        strcpy(new_dir->path, path);
    }
    
    File curr_file = fs->current_file;
    //checks if it already exists and changes the boolean value in fs- for error checking
    CheckIfAlreadyExists(curr_file, new_dir->path, fs);
    if (fs->path_has_been_found) {
        fprintf(stdout, "mkdir: cannot create directory '%s': File exists \n", path);
        //reset it
        fs->path_has_been_found = false;
        //free it because it wont be added
        free(new_dir->path);
        free(new_dir);
        return;
    }
    //This is where the file is searched for and added
    SearchAndAddRecursively(curr_file, new_dir->path, new_dir);
    //If it is a text file, return error
    if (new_dir->parent_file->file_type == IS_TEXT_FILE) {
        fprintf(stdout, "mkdir: cannot create directory '%s': Not a directory \n", path);
        //free it because it wont be added
        free(new_dir->path);
        free(new_dir);
        return;
    }
    //new_dir should always have a parent if the parent was found
    if (new_dir->parent_file == NULL) {
        fprintf(stdout, "mkdir: cannot create directory '%s': No such file or directory\n", path);
        //free it because it wont be added
        free(new_dir->path);
        free(new_dir);
        return;
    }
    new_dir->level = new_dir->parent_file->level + 1;
}

void FsMkfile(Fs fs, char *path) {
    // TODO
}

void FsCd(Fs fs, char *path) {
    // TODO
}

void FsLs(Fs fs, char *path) {
    // TODO
}

void FsPwd(Fs fs) {
    // TODO
}

void FsTree(Fs fs, char *path) {
    // TODO
    //print whole thing
    File curr_file;
    if (path == NULL) {
        curr_file = fs->root_file;
    } else {
        curr_file = fs->current_file;
    }
    PrintAll(curr_file);
}


//STAGE 2
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


//STAGE 3
void FsCp(Fs fs, bool recursive, char *src[], char *dest) {
    // TODO
}


//STAGE 4
void FsMv(Fs fs, char *src[], char *dest) {
    // TODO
}