#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "../include/skip_list.h"

/* ================================ STRUCT ================================== */

struct _SkipList {
  int max_level;
  Node *head;
  SkipListCmp compare;
};

struct _Node {
    int size;
    void* item;
    Node** next;
};

/* =============================== FUNCTIONS ================================= */

SkipList* SkipList_create(SkipListCmp compare) {
    SkipList* list = (SkipList*)malloc(sizeof(*list));
    if (list == NULL) {
	    fprintf(stderr, "SkipList_create: unable to allocate memory for the skip list");
	    exit(EXIT_FAILURE);
    }

    list->head = (Node*)malloc(sizeof(Node));
    if (list->head == NULL) {
	    fprintf(stderr, "SkipList_create: list->head parameter cannot be NULL");
	    exit(EXIT_FAILURE);
    }

    list->max_level = 1;
    list->head->item = NULL;
    list->head->next = (Node**)malloc(sizeof(Node*)* MAX_HEIGHT);

    for(int i = 0; i < MAX_HEIGHT; i++) {
        list->head->next[i] = NULL;
    }

    list->head->size = MAX_HEIGHT;
    list->compare = compare;
    
    return list;
}

Node* SkipList_create_node(void* item, int size){
    Node* node = (Node*)malloc(sizeof(*node));
    if (node == NULL) {
	    fprintf(stderr, "SkipList_create_node: node parameter cannot be NULL");
	    exit(EXIT_FAILURE);
    }

    node->next = (Node**)malloc(sizeof(Node*) * size);
    if (node->next == NULL) {
	    fprintf(stderr, "SkipList_create_node: node->next parameter cannot be NULL");
	    exit(EXIT_FAILURE);
    }
    
    node->size = size;
    node->item = item;

    return node;
}

void Node_next(Node* head_node, int size){
    Node** node_realloc = (Node**)realloc(head_node->next, sizeof(Node*) * size);
    if (node_realloc == NULL) {
	    fprintf(stderr, "Node_next: node_realloc parameter cannot be NULL");
	    exit(EXIT_FAILURE);
    }

    head_node->next = node_realloc;
}

void SkipList_insert(SkipList* list, void* item){
    Node* new = SkipList_create_node(item, randomLevel());;
    if (new->size > list->max_level) {
        Node_next(list->head, new->size + 1);
        list->max_level = new->size;
    }

    Node* curr = list->head;;
    int i;

    for (i = list->max_level ; i >= 0 ; i--){
        if (curr->next[i] == NULL || list->compare(item, curr->next[i]->item) > 0){
            if (i < new->size){
                new->next[i] = curr->next[i];
                curr->next[i] = new;
            }
        }else{
            curr = curr->next[i];
            i++;
        }
    }
}

int randomLevel() {
    int lvl = 1;

    srand(time(NULL));
    while ((rand() % 2) && (lvl < MAX_HEIGHT)) {
    	lvl += 1;
    }
        
    return lvl;  
}

void* SkipList_search(SkipList* list, void* find) {
    Node* x = list->head;

    for (int i = list->max_level ; i >= 0 ; i--){
        while (x->next[i] != NULL && list->compare(x->next[i]->item, find) > 0){
            x = x->next[i];
        }
    }

    x = x->next[0];
    if (x != NULL && list->compare(x->item, find) == 0){return x->item;}

    return NULL;
}

void SkipList_delete(SkipList* list) {
    Node* curr_node = list->head;

    while (curr_node->next[0] != NULL){
        Node* next_node = curr_node->next[0];
        SkipList_free_node(curr_node);
        curr_node = next_node;
    }

    free(list);
}

int SkipList_size(SkipList* list) {
    Node *tmp = list->head;
    unsigned int size = 0;
    
    if(tmp->next[0] == NULL){
        return size;
    }else{
        size = 1;
        tmp = tmp->next[0];
        while(tmp->next[0] != NULL){
            size = size + 1;
            tmp = tmp->next[0];
        }
        return size;
    }
}

void SkipList_free_node(Node* node) {
    if (node == NULL) {
	    fprintf(stderr, "Skiplist_free_node: list parameter cannot be NULL");
	    exit(EXIT_FAILURE);
    }

    free(node->next);
    free(node);
}

/* =========================== COMPARATORS ================================== */

int compare_string(void* elem1, void* elem2) {
  return strcmp(((char*)elem1),((char*) elem2));
}

int compare_int(void* elem1, void* elem2) {
  if (*((int*) elem1) == *((int*) elem2)) { return 0;}
  if (*((int*) elem1) < *((int*) elem2)) { return -1;}
  return 1;
}