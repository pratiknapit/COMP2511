// Interface to the File System ADT
// COMP2521 Assignment 1

// !!! DO NOT MODIFY THIS FILE !!!

#ifndef FS_H
#define FS_H

#define PATH_MAX 4096

/**
 * Creates a new pointer to a FsRep which contains a filename, etc. 
 */
Fs FsNew(void);

/**
 * Put the canonical path of the current working directory (cwd) into a given 
 * cwd array. Assume that the cwd is no longer than PATH_MAX characters. 
 */
void FsGetCwd(Fs fs, char cwd[PATH_MAX + 1]);

/**
 * Free all memory associated with the given Fs. You may need to update this function 
 * as you work on each stage to free any new data structures that you created.
 */
void FsFree(Fs fs);

/**
 * Takes the path and creates a new directory at that path in the given file system.
 * FsMkDir performs roughly the same function as the mkdir command in Linux.
 */
void FsMkdir(Fs fs, char *path);

/**
 * Takes the path and creates a new regular file at that path in the given file system.
 * 
 */
void FsMkfile(Fs fs, char *path);

/**
 * Takes a path which may be NULL. If the path is not NULL, the fucntion should 
 * change the cwd to that path.
 * If the path is NULL, it defaults to the root directory (not the home directory, 
 * since we do not have home directories in this assignment)
 */
void FsCd(Fs fs, char *path);

/**
 * Takes a path which may be NULL. 
 * If the path is not NULL and refers to a directory, then the function should print the 
 * names of all the files in that directory (except for . and ..) in ASCII order, one per line.
 * If the path refers to a regular file, then the function should just print the given path if it exists
 * in the file system.
 */
void FsLs(Fs fs, char *path);

/**
 * The function prints the canonical path of the cwd.
 * The function roughly corresponds to the pwd command in Linux.
 */
void FsPwd(Fs fs);

/**
 * The function takes one path which may be NULL.
 * If the path is NULL, it defaults to the root directory.
 * If the path is not NULL, it is expected to refer to a directory and the function
 * should print out the contents of the directory in a tree-like format.
 */
void FsTree(Fs fs, char *path);

void FsPut(Fs fs, char *path, char *content);

void FsCat(Fs fs, char *path);

void FsDldir(Fs fs, char *path);

void FsDl(Fs fs, bool recursive, char *path);

void FsCp(Fs fs, bool recursive, char *src[], char *dest);

void FsMv(Fs fs, char *src[], char *dest);

#endif

