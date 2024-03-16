
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Fs.h"

void get_count(File node, int *text);

int totalTextSize(Fs fs) {
    int num = 0;
    get_count(fs->root, &num);

    return(num);
}

void get_count(File node, int *text) {
    if (node->files == NULL) {
        if (node->text != NULL) {
            *text = *text + strlen(node->text);
        }
    } else {
        FileList curr = node->files;
        while(curr != NULL) {
            get_count(curr->file, text);
            curr = curr->next;
        }
    }
}
