#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <sys/time.h>
#include <time.h>
#include <ctype.h>
#include "../Resources/unity.h"
#include "../include/skip_list.h"

#define COMPARESTRING compare_string
#define COMPAREINT compare_int

/* =============== DECLARATIONS FUNCTIONS ================= */

/* Functions to check word into dictionary */
void check_words(FILE* txt, SkipList* dictionary);

/* Functions to count_words */
int count_words(char character);

/* Functions to load skip list with path1(dictionary) e path2(correctme) */
void skip_list_load(char* path1, char* path2);

/* ====================== FUNCTIONS ======================== */

void check_words(FILE* txt, SkipList* dictionary) {
	char line[100];
	while(fscanf(txt, "%s", line) != -1) {
		int tmp = strlen(line) - 1;
		line[0] = tolower(line[0]);

		if(count_words(line[tmp]) == 1) {
			    line[strlen(line) - 1] = '\0';
		}

		if(SkipList_search(dictionary, line) == 0) {
            printf(" - %s\n",line);
		}
	}
}

int count_words(char character) {
    int wfound = 0;
    int count = 0;
    char ch[] = {' ', '\t', '\n', ':', '.', ',', '!', '"', ';', '?'};

    while(wfound == 0 && count<10) {
        if(ch[count] == character){wfound=1;}
        count++;
    }

    return wfound;
}


void skip_list_load(char* path1, char* path2) {
    SkipList* dictionary;
    struct timeval start, stop;
    double secs = 0;
    int algo;

    printf("DO YOU WANT TO CONTINUE ?? \n");
    printf("PRESS 1 TO CONTINUE \n");
    printf("PRESS 2 TO EXIT \n");

    scanf("%d",&algo);
    switch(algo) {
    	case 1:
    	    printf("\nSEARCH.....\n");
            gettimeofday(&start, NULL); 
            dictionary = SkipList_create(compare_string);

            FILE *fp = fopen(path1, "r");
            if(fp == NULL) {
                printf("\nUnable to open file.\n");
                printf("Please check if file exists and you have read privilege.\n");
                exit(EXIT_FAILURE);
            }

            char line[100];
            while(fscanf(fp, "%s", line) != -1) {
                char* save = (char*)malloc(sizeof(char) * strlen(line) + 1);
                strcpy(save, line);
                SkipList_insert(dictionary, save);
	        }

            gettimeofday(&stop, NULL); 
            secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
            fclose(fp);
            printf("\nDICTIONARY LOADED IN : %0.2fs\n", secs);

            FILE* correctme = fopen(path2, "r");

            if(correctme == NULL) {
                printf("\nUnable to open file.\n");
                printf("Please check if file exists and you have read privilege.\n");
                exit(EXIT_FAILURE);
            }

            printf("\nWORDS FOUND:\n");

            gettimeofday(&start, NULL); 
            check_words(correctme, dictionary);
    
            gettimeofday(&stop, NULL); 
            secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
            printf("\nCHECK COMPLETED IN : %0.2fs\n", secs);
            fclose(correctme);
            SkipList_delete(dictionary);

            printf("\nCOMPLETED\n");
       
    	break;
    	
    	case 2:
    	    printf("BYE \n");
    	break;
    	
    	default:
           printf("YOU TYPED AN INCORRECT NUMBER\n");
           exit(-1);
        break;

    }
}

int main(int argc, char *argv[]) {
	if(argc < 3) {
		printf("error while inserting arguments\n");
		exit(EXIT_FAILURE);
    }

	skip_list_load(argv[1], argv[2]);
	
	return (EXIT_SUCCESS);
}
