// Random char array checks

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH_MAX 4096

typedef struct file *File; 
typedef struct FsRep *Fs;

//Define functions
Fs FsNew(void);
char *get_parent_prefix(char *path);

struct file {

    int file_type; //boolean check FileType.h

    int level;

    char path[PATH_MAX + 1];

    char *file_name;

    File parent_file; 

    File child_file;

    File next_file;

};

struct FsRep {

    char cwd_path[PATH_MAX + 1];

    File root_file;
    
    File cwd_file;

};


int main(void) {

    Fs fs = FsNew();
    printf("Path for cwd file is %s\n", fs->cwd_file->path);
    

    printf("Path for cwd %s.\n", fs->cwd_path);

    char *last = strrchr(fs->cwd_path, '/');
    if (last != NULL) {
        printf("%s\n", last);
    }

    printf("%lu\n", strlen(last));
    memmove(last, last + 1, strlen(last));
    printf("%s\n", last);
    printf("%lu\n", strlen(last));

    char* piece = strtok(fs->cwd_path, "/");
    printf("%s\n", piece); //gives me the first folder. 


    
    ///////////////////////////////////////////////////////////////////////////////////////////

    char *path = fs->cwd_file->path;

    int i, j, ls, lw, temp, chk = 0;
    
    char *l = strrchr(path, '/');
    if (l != NULL) {
        printf("%s\n", l);
    }

    printf("%s\n", path);
    memmove(l, l + 1, strlen(l));
    printf("%s\n", l); //successfull strip - contains home only.


    //now we want to strip home from /home to get /

    ls = strlen(path);
    lw = strlen(l);
    for(i=0; i<ls; i++)
    {
        temp = i;
        for(j=0; j<lw; j++)
        {
            if(path[i] == l[j])
            i++;
        }
        chk = i-temp;
        if(chk==lw)
        {
            i = temp;
            for(j=i; j<(ls-lw); j++) {
                path[j] = path[j+lw];
            }
            ls = ls-lw;
            path[j]='\0';
        }
    }

    //printf("%s\n", l);
    //printf("%s\n", path);

    
    
    return 0;
}



char *get_parent_prefix(char *path) {

    int i, j, ls, lw, temp, chk = 0;
    
    char *l = strrchr(path, '/');
    if (l != NULL) {
        printf("%s\n", l);
    }

    memmove(l, l + 1, strlen(l));

    ls = strlen(path);
    lw = strlen(l);
    for(i=0; i<ls; i++)
    {
        temp = i;
        for(j=0; j<lw; j++)
        {
            if(path[i] == l[j])
            i++;
        }
        chk = i-temp;
        if(chk==lw)
        {
            i = temp;
            for(j=i; j<(ls-lw); j++) {
                path[j] = path[j+lw];
            }
            ls = ls-lw;
            path[j]='\0';
        }
    }
    
    return path;
}



Fs FsNew(void) {

    Fs fs = malloc(sizeof(*fs));
    if (fs == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    strcpy(fs->cwd_path, "/home/tmp");

    File root_file = malloc(sizeof(*root_file));
    root_file->child_file = NULL;
    //root_file->next_file = NULL;
    root_file->file_type = 1;
    strcpy(root_file->path, "/home/tmp");
    root_file->level = 0;
    fs->root_file = root_file; 
    fs->cwd_file = root_file; 
    
    return fs;
}
