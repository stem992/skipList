#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
#include <malloc.h>
#include "../Resources/unity.h"
#include "../include/skip_list.h"

#define COMPARESTRING compare_string
#define COMPAREINT compare_int

typedef struct _SkipList SkipList;
typedef struct _Node Node;

static void test_not_null() {
	SkipList* list = SkipList_create((SkipListCmp) COMPAREINT);
	TEST_ASSERT_NOT_NULL(list);
	
	free(list);
}

static void test_empty() {
    SkipList* list = SkipList_create((SkipListCmp) COMPAREINT); 
    TEST_ASSERT_FALSE(SkipList_search(list, (void *)2));

    free(list);
}

static void test_insert_one() {
    SkipList* list = SkipList_create((SkipListCmp) COMPAREINT); 
    SkipList_insert(list, (void *)2);

    TEST_ASSERT_EQUAL_INT(1, SkipList_size(list));

    free(list);
}

static void test_insert_string() {
    SkipList* list = SkipList_create((SkipListCmp) COMPARESTRING); 
    SkipList_insert(list, (void *) "ciao");

    TEST_ASSERT_EQUAL_INT(1, SkipList_size(list));
    
    free(list);	
}

static void test_insert_and_delete() {
    SkipList* list = SkipList_create((SkipListCmp) COMPAREINT); 
    SkipList_insert(list, (void *)2);

    TEST_ASSERT_EQUAL_INT(1, SkipList_size(list));
    
    SkipList_delete(list);
    
    TEST_ASSERT_NOT_NULL(list);

}

int main() {

	UNITY_BEGIN();
	RUN_TEST(test_not_null);
    RUN_TEST(test_empty);
    RUN_TEST(test_insert_one);
    RUN_TEST(test_insert_string);
    RUN_TEST(test_insert_and_delete);
	UNITY_END();
	
	return 0;
}