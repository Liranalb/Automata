
#include <stdio.h>
#include "slist.h"
#include <stdlib.h>

void slist_init(slist_t * list) {
    if (list == NULL) { //checking if the list is empty
        return;
    }

    slist_head(list) = NULL;
    slist_tail(list) = NULL;
    slist_size(list) = 0;
}


void slist_destroy(slist_t * list,slist_destroy_t dealloc) {
    if (list == NULL) { //checking if the list is empty
        return;
    }

    slist_node_t *tmp; // may need allocation

    while(slist_head(list) !=NULL) {
        tmp = slist_head(list);
        slist_head(list) = slist_next(slist_head(list));
        if(dealloc) //check
            free(slist_data(tmp));
        free(tmp);
    }
    free(list);
}

int slist_append(slist_t *list,void *data) {

    //printf("\nStarting append\n");

    if (list == NULL || data == NULL) { // checking if allocation succeed
        return -1;
    }

    slist_node_t *tmp = (slist_node_t*)malloc(sizeof(slist_node_t));
    if (tmp == NULL) { // checking if allocation succeed
        printf("Cannot allocate initial memory for data\n");
        return -1;
    }

    slist_data(tmp) = data;

    if (slist_head(list) == NULL){ //if there is no head in the list
        slist_head(list) = tmp;
        slist_tail(list) = tmp;
        //printf("\ninside append 1\n");
        return 0;
    }

    slist_next(slist_tail(list))= tmp; //old tail points at
    slist_tail(list) = tmp;
    slist_size(list)++;
    //printf("\ninside append 2\n");

    return 0;
}

void *slist_pop_first(slist_t * list) {
    if (list == NULL) { //checking if the list is empty
        return NULL;
    }

    slist_node_t *tmp = slist_head(list);
    slist_head(list) = slist_next(tmp); //head becomes the next
    void* oldData = slist_data(tmp); //saving the data
    free(tmp);
    slist_size(list)--;
    return oldData; //CHECK
}

int slist_prepend(slist_t *list,void *data) {
    if (list == NULL) { // checking if allocation succeed
        return -1;
    }

    slist_node_t *tmp = (slist_node_t*)malloc(sizeof(slist_node_t));
    if (tmp == NULL) { // checking if allocation succeed
        printf("Cannot allocate initial memory for data\n");
        return -1;
    }

    slist_data(tmp) = data;

    if (slist_head(list) == NULL){ //if there is no head in the list
        slist_head(list) = tmp;
        slist_tail(list) = tmp;
        slist_size(list) = 1;
        return 0;
    }

    slist_next(tmp) = slist_head(list);
    slist_head(list) = tmp;
    slist_size(list)++;

    return 0;
}

int slist_append_list(slist_t* source, slist_t* dest) {
    if(source == NULL || dest == NULL) {
        return -1;
    }

    slist_node_t* tmp;
    for(tmp = slist_head(dest); tmp != NULL; tmp = slist_next(tmp)) {
        slist_append(source, slist_data(tmp));
    }
    return 0;
}

/*


//! Single linked list type
typedef struct slist slist_t;


// you have to use these macros, do not use the inner variables of the list!!
//! Macro to get the head node of a list l
#define slist_head(l) l->head
//! Macro to get the tail node of a list l
#define slist_tail(l) l->tail
//! Macro to get the size of a list l
#define slist_size(l) l->size
//! Macro to get the next node of l
#define slist_next(n) n->next
//! Macro to get the data of node l
#define slist_data(n) n->data
*/


