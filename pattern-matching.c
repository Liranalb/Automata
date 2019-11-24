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

/*
 *
 * (slist_t*)malloc(sizeof(slist_t));
pm_state_t
struct pm_state
{
    pm_int_t id;
    pm_int_t depth;
    slist_t* output;  //list of patterns
    struct pm_state * fail; //failure function, pointer to the state that we should go when there is no transition
    slist_t* _transitions; //list of edges
};

*/