#include <stdio.h>
#include <stdlib.h>
#include "slist.h"
#include "pattern-matching.h"


int main() {
    pm_t* tree = (pm_t*)malloc(sizeof(pm_t));
    pm_init(tree);
    printf("#Init zerostate Test:\nID: %d", tree->zerostate->id);
    printf(":\nDepth: %d", tree->zerostate->depth);
    char* str = "TEST";
    char* str2 = "TEST2";
    void* test = pm_goto_get(tree->zerostate, 'v');
    printf("\ngoto_get: %d", test);


    slist_t* list = (slist_t*)malloc(sizeof(slist_t));
    slist_t* list2 = (slist_t*)malloc(sizeof(slist_t));

    slist_init(list);
    slist_init(list2);

    int x = 1;
    int y = 2;
    printf("\n*** adding to list ***\n");
    slist_append(list, &x);
    slist_prepend(list, &y);
    printf("\n*** adding to list2 ***\n");
    slist_append(list2, &x);
    slist_prepend(list2, &y);


    printf("\n*** Pop list ***\n");
    slist_pop_first(list);


    printf("\n*** Appending lists ***\n");
    slist_append_list(list, list2);


    printf("\n*** Destroying lists ***\n");
    slist_destroy(list, SLIST_LEAVE_DATA);
    slist_destroy(list2, SLIST_LEAVE_DATA);

    free(list);
    free(list2);
    return 0;

}