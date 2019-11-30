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

    printf("%d -> %c -> %d\n", from_state->id,symbol, to_state->id);

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
        return NULL;
    }

    slist_node_t* tmp = state-> slist_head(_transitions); //create a temp list for checking the trans list
    while(tmp) {
         //create a new arc
        if (((pm_labeled_edge_t*)slist_data(tmp))->label == symbol) //check if we have a symbol match at the arc
            return ((pm_labeled_edge_t*)tmp->data)->state; // if so, return the arc state

        tmp = slist_next(tmp);
    }
    return NULL; // no transition found, return NULL
}



int pm_addstring(pm_t *pm,unsigned char *str, size_t n) {
    if (pm == NULL || str == NULL)
        return -1;

    if(n == 0) {
        printf("the string is empty");
        return 0;
    }

    pm_state_t *currentRoot = pm->zerostate;
    pm_state_t *next;
    int i;

    for(i = 0; i < n; i++){
        if((next = pm_goto_get(currentRoot,str[i])) == NULL) { //current state is empty
            pm_state_t *state = (pm_state_t *) malloc(sizeof(pm_state_t)); //create a new state
            if (state == NULL) { //checking allocation
                printf("Cannot allocate initial memory for data\n");
                return -1;
            }

            //printf("\ntest - next = null --> creating a new state\n");
            printf("Allocating state %d\n", pm->newstate);

            state->depth = currentRoot->depth + 1;
            state->id = pm->newstate;
            state->fail = NULL;
            //printf("\ntest: depth of the state is: %d\n", state->depth);
            state->output = (slist_t *) malloc(sizeof(slist_t));
            state->_transitions = (slist_t *) malloc(sizeof(slist_t));

            if (state->output == NULL || state->_transitions == NULL) {
                printf("Cannot allocate initial memory for data\n");
                return -1;
            }
            //printf("finish alloction for output and transition\n");

            slist_init(state->_transitions); //creating alloction for the new state lists
            slist_init(state->output);
            pm->newstate++;

            //printf("finish init for transitions and output\n");
           // printf("state->output size is: %d\n", state->output->size);
            //printf("state->transitions size is: %d\n", state->_transitions->size);
            //printf("state->id is: %d\n", state->id);
            //printf("pm->newstate is: %d\n", pm->newstate);

            if (pm_goto_set(currentRoot, str[i], state) == -1) { //setting the arc
                return -1;
            }

            currentRoot = state;
        }


        else {
            //printf("test 7 - next != null");
            if((next == pm_goto_get(currentRoot, str[i]) != NULL)) {
               //printf("test 6");
                currentRoot = next; //state exist -> go to the next state
              }
             }
        //printf("goto_get on current root succeed\n");

        if((next = pm_goto_get(currentRoot, str[i]) != NULL)) {
            currentRoot = next; //finish building the state. go to the next one
            printf("creating an arc between current and next. current is now next \n");
        }
    }
     //loop end
    //printf("\nTest 4\n");


    slist_append(currentRoot->output, str); //FIX THIS LINE - GETTING SIGSEGV!

    //printf("\nTest 5\n");

    return 0; //return 0 on success
}

int pm_makeFSM(pm_t *pm_tree)
{
    if(pm_tree == NULL)
        return -1;

    slist_t *queue = (slist_t*)malloc(sizeof(slist_t)); // creating a new queue
    if(queue == NULL) { // checking alloction
        //destroy tree
        return -1;
    }

    slist_init(queue); //intiate tree
    // creating a new edge and setting it to be the head of trans of the first state
    slist_node_t *edge = slist_head(pm_tree->zerostate->_transitions);

    //create a failure state for the dept = 1 to be the zerostate
    while(edge != NULL) {
        pm_state_t *tmp_state = ((pm_labeled_edge_t*)slist_data(edge));
        if(slist_append(queue, tmp_state) == -1) {
            //destroy tree;
            return -1;
        }

        //intiate failure state for dept 1 to be the zero state
        tmp_state->fail = pm_tree->zerostate;
        edge = slist_next(edge); //loop step
    }

    //deal with the other states


    return 0;
}


