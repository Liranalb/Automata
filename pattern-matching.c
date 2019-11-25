//
// Created by liran on 11/15/19.
//

#include "pattern-matching.h"
#include "slist.h"

int pm_init(pm_t *fsm) { //NEED TESTING
    if(fsm == NULL) {
        printf("Cannot allocate initial memory for data\n");
        return -1;
    }

    fsm->zerostate = (pm_state_t*)malloc(sizeof(pm_state_t)); //check
    if (fsm->zerostate == NULL) { // checking if allocation succeed
        printf("Cannot allocate initial memory for data\n");
        return -1;
    }

    fsm->zerostate->_transitions = (slist_t*)malloc(sizeof(slist_t));
    if (fsm->zerostate->_transitions == NULL) { // checking if allocation succeed
        printf("Cannot allocate initial memory for data\n");
        return -1;
    }

    slist_init(fsm->zerostate->_transitions);
    fsm->newstate = 1;
    fsm->zerostate->id = 0;
    fsm->zerostate->depth = 0;
    fsm->zerostate->fail = NULL;
    fsm->zerostate->output = NULL;

    return 0;
}

int pm_goto_set(pm_state_t *from_state, unsigned char symbol, pm_state_t *to_state) { //NEEDS TESTING
    if(from_state == NULL || to_state == NULL) {
        printf("Cannot allocate initial memory for data\n");
        return -1;
    }

    pm_labeled_edge_t *newEdge = (pm_labeled_edge_t*)malloc(sizeof(pm_labeled_edge_t)); //creating a new arc
    if (newEdge == NULL) { // checking arc allocation
        printf("Cannot allocate initial memory for data\n");
        return -1;
    }

    newEdge->label = symbol; // assigning symbol and to_state in the the arc
    newEdge->state = to_state;

    return slist_append(from_state->_transitions, newEdge); //add the new arc to the transition using appand

}


pm_state_t* pm_goto_get(pm_state_t *state, unsigned char symbol) { //NEED TESTING
    if(state == NULL) {
        printf("Cannot allocate initial memory for data\n");
        return NULL;
    }

    slist_node_t* tmp = state-> slist_head(_transitions); //create a temp list for checking the trans list
    while(tmp != NULL) {
        pm_labeled_edge_t* newEdge = ((pm_labeled_edge_t*)slist_data(tmp)); //create a new arc
        if(newEdge->label == symbol) { //check if we have a symbol match at the arc
            return newEdge->state; // if so, return the arc state
        }
    }

    return NULL; // no transition found, return NULL
}


/*
int pm_addstring(pm_t *pm,unsigned char *str, size_t n) {
    if (pm == NULL || n == NULL) {
        printf("Cannot allocate initial memory for data\n");
        return -1;
    }

    pm_state_t *currentRoot = pm->zerostate;
    pm_state_t *next;

    for(int i = 0; i < n; i++){

    }
}


*/


