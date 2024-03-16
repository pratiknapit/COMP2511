// Main program for testing the File System ADT

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Fs.h"
#include "utility.h"


int main(void) {
	Fs fs = FsNew();
	FsPwd(fs);
	FsMkdir(fs, "home");
	FsCd(fs, "home");
	FsPwd(fs);
	FsMkdir(fs, "jas");
	FsCd(fs, "jas");
	FsPwd(fs);
	//FsTree(fs, NULL);
	char *name = get_file_name("/home/tmp");
	File file = get_last_file_in_path(fs->cwd_file, "/home/tmp");
	
	printf("%s\n", name);
	printf("%s\n", file->file_name);
}


/*
int main(void) {
    



	//FsLs(fs, NULL);
	
	FsMkfile(fs, "hello.txt");
	FsMkfile(fs, "world.txt");

	FsMkdir(fs, "bin");
	FsMkfile(fs, "bin/ls");
	FsMkfile(fs, "bin/pwd");
	FsMkdir(fs, "home");
	FsMkdir(fs, "home/jas");
	FsMkfile(fs, "home/jas/todo.txt");
	FsMkfile(fs, "home/jas/mail.txt");
	FsLs(fs, NULL);
	
	FsTree(fs, "/home/jas");
	printf("---\n"); // marker to separate output
	FsTree(fs, NULL);
	
    //FsFree(fs);

}

*/