#include <stdio.h>
#include <stdlib.h>
#include "slist.h"
#include "pattern-matching.h"


int main() {
    pm_t* tree = (pm_t*)malloc(sizeof(pm_t));
    pm_init(tree);
    printf("#Init zerostate Test:\nID: %d", tree->zerostate->id);
    printf(":\nDepth: %d\n\n", tree->zerostate->depth);

    printf("####### Testing add_string: #######\n");
    pm_addstring(tree, "e", 1);
    pm_addstring(tree, "be", 2);
    pm_addstring(tree, "bd", 2);
    pm_addstring(tree, "bcd", 3);
    pm_addstring(tree, "cdbcab", 6);
    pm_addstring(tree, "bcaa", 4);

    pm_makeFSM(tree);


/*




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
    free(list2);*/
    return 0;

}