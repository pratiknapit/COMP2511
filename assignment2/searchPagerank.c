// COMP2521 Assignment 2

// Written by: Pratik Napit 
// Date: 4/11/2021

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

void add_word_count(char **words, list l, int size);
void word_count(list l, char *url);
void add_page_ranks(list l);
void sort(list l);



int main(int argc, char *argv[]) {

    //get the search words required from the command line and store them into a 
    //double char array (array of strings) 

    if (argc == 1) {
        fprintf(stderr, "Error: invalid number of command-line arguments.");
    }

    char *words[1000]; 
    list url_list = new_list();
    
    int w_count = 0; 
    for (int i = 0; i < argc - 1; i++) {
        words[i] = malloc(strlen(argv[i+1]) + 1); 
        strcpy(words[i], argv[i+1]);
        w_count++;
    }

    //Read through invertedIndex.txt and add the number of words in each url into
    // the url list. 

    //Open invertedIndex.txt and count urls, then add them to the url_list for the
    //url struct.

    add_word_count(words, url_list, w_count);

    //Go through the pageRankList.txt and add it to each url in the list as well. 
    // Add each page rank into each url node in the list.

    add_page_ranks(url_list);

    //Sort the url_list in descending order of matches and then descending order of PageRank using
    // a stable list algorithm. - I have implemented a bubble sort but using linked lists.

    sort(url_list);

    //Print the url_list but only the url names in the sorted order.

    print_url_list(url_list);
 

    free_list(url_list);

    return 0; 

}

void add_word_count(char **words, list url_list, int size) {
    char scan_url[100];
    char all_urls[1000];

    //Open invertedIndex.txt and count urls 
    for (int i = 0; words[i] != NULL; i++) {
        FILE *in = fopen("invertedIndex.txt", "r");

        //Scan through each word in invertedIndex.txt
        while (fscanf(in, "%s", scan_url) != EOF) {
            //Check if the word is what we are searching for.
            if (strcmp(words[i], scan_url) == 0) {
                //If we are at the word we are looking for, we need to get the urls
                fgets(all_urls, 1000, in);
                //Split each word in the line by a token

                char *url = strtok(all_urls, " ");

                while (url != NULL) {

                    if (strcmp(url, "\n") == 0) {
                        break;
                    }

                    if (check_list(url_list, url) == true) {
                        word_count(url_list, url);
                    } else {
                        insert_url(url_list, url);
                    }  

                    url = strtok(NULL, " "); //this will iterate through each token

                }

            }
        }

        fclose(in);
    }
}

void word_count(list url_list, char *url) {
    node curr = url_list->head;
    while (curr != NULL) {
        if (strcmp(curr->url_name, url) == 0) {

            curr->word_counter += 1;

        }
        curr = curr->next;
    }
}

// Add the pageranks for each URL to the list

void add_page_ranks(list url_list) {
    char index[100];
    char line[1000];

    FILE *in = fopen("pagerankList.txt", "r");

    while (fscanf(in, "%s", index) != EOF) { 

        // Take away the comma 
        for (int c = 0; index[c] != '\0'; c++) {
            if (index[c] == ',' || index[c] == '\n') {
                index[c] = '\0';
            }
        }

        if (strncmp(index, "url", 3) == 0) { 

            fgets(line, 1000, in);

            char *url = strtok(line, " ");

            url = strtok(NULL, " "); 

            node curr = url_list->head; 

            while (curr != NULL) {

                if (strcmp(index, curr->url_name) == 0) {

                    curr->page_rank = atof(url); 
                }

                curr = curr->next; 
            }

            

        }

    }

}

// To sort the linked list, just use a iterative selection sort. Easiest way to do it.

void sort(list l) {

    int N = count_list(l);

    node head = l->head; 

    for (int j = 0; j < N; j++) {
        node prev = NULL; 
        node curr = NULL;
        node next = NULL; 
        for (curr = head; curr->next != NULL; curr = curr->next) {

            if (curr->word_counter < curr->next->word_counter) {

                next = curr->next; 
                curr->next = next->next;
                next->next = curr; 

                if (curr == head) {
                    head = next;
                    curr = next; 
                } else {
                    prev->next = next;
                    curr = next;
                }

            } else if (curr->word_counter == curr->next->word_counter) {
                if (curr->page_rank < curr->next->page_rank) {

                    node next = curr->next; 
                    curr->next = next->next;
                    next->next = curr; 

                    if (curr == head) {
                        head = next;
                        curr = next; 
                    } else {
                        prev->next = next;
                        curr = next;
                    }

                }
            } 

            
            prev = curr; 

        }
        
    }

    l->head = head; 

}







/*
list url_list() {
    

    char *file = "ex1/pagerankList.txt"; 

    FILE *in = fopen(file, "r"); 

    list url_list = new_list(); 

    char url[1000]; 
    char *url_n = "url";

    while (fscanf(in, "%s", url) == 1) {
        if (prefix(url_n, url) == true) {
            int len = strlen(url);
            if (hasPunctuation(url) == 1) {
                url[len-1] = '\0';
            }
            insert_url(url_list, url);
        }
    }

    print_url_list(url_list); 

    fclose(in); 

    return url_list; 

     
}

list matched_url_list(char *word) {

    char *file = "ex1/invertedIndex.txt"; 

    FILE *in = fopen(file, "r");

}


//from stack overflow 
bool prefix(const char *pre, const char *str) {
    return strncmp(pre, str, strlen(pre)) == 0;
}

int hasPunctuation(char *str) {
  int len = strlen(str);
  if (str[len-1] == '.' || str[len-1] == ',' || str[len-1] == ';' || str[len-1] == '?') {
    return 1;
  }
  return 0;
}
*/