#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#define MAX_HEIGHT 13

typedef struct _SkipList SkipList;
typedef struct _Node Node;

typedef int (*SkipListCmp)(void*, void*);

/* ============================= UTILS ====================================== */

/* Create new Skip List */
SkipList* SkipList_create(SkipListCmp compare);

/* Create new Skip List Node */
Node* SkipList_create_node(void* item, int size);
void Node_next(Node* head_node, int size);

/* Insert an element inside the Skip List */
void SkipList_insert(SkipList* list, void* item);

/* Determines the number of pointers to be included in the new node 
   and must be made in accordance with the following algorithm. */
int randomLevel();

/* Search an element inside the Skip List */
void* SkipList_search(SkipList* list, void* find);

/* Delete an existing list */
void SkipList_delete(SkipList* list);

/* Determines the size of the skiplist */
int SkipList_size(SkipList* list);

/* Deallocates the Skip List Node */
void SkipList_free_node(Node* node);

/* =========================== COMPARATORS ================================== */

int compare_string (void* elem1, void* elem2);
int compare_int (void* elem1, void* elem2);

#endif