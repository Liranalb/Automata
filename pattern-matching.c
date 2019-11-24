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

/*


struct pm_labeled_edge {
    unsigned char label;  //the character "on" this edge
    struct pm_state *state; //the destination state
};

typedef struct pm_labeled_edge pm_labeled_edge_t;



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