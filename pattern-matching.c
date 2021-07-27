#include "pattern-matching.h"
#include "slist.h"

//void checkSymbol(pm_t*, pm_state_t*, unsigned char);
int failToZero(pm_t *pm_tree, slist_t* queue, slist_node_t *edge);
void findEdge(pm_t *pm_tree, pm_state_t **fail, unsigned char symbol);
int FStateSetAndPrint(pm_state_t **origin, pm_state_t *fail, unsigned char symbol);
void stateDestructor(pm_state_t* state, slist_node_t *queue);

int pm_init(pm_t *fsm) {
    if(!fsm) {
        return -1;
    }

    fsm->zerostate = (pm_state_t*)malloc(sizeof(pm_state_t)); //check
    if (!(fsm->zerostate)) { // checking if allocation succeed
        printf("Cannot allocate initial memory for data\n");
        return -1;
    }

    fsm->zerostate->_transitions = (slist_t*)malloc(sizeof(slist_t));
    if (!(fsm->zerostate->_transitions)) { // checking if allocation succeed
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
    if(!(from_state) || !(to_state)) {
        printf("Cannot allocate initial memory for data\n");
        return -1;
    }

    printf("%d -> %c -> %d\n", from_state->id,symbol, to_state->id);

    pm_labeled_edge_t *newEdge = (pm_labeled_edge_t*)malloc(sizeof(pm_labeled_edge_t)); //creating a new arc
    if (!newEdge) { // checking arc allocation
        printf("Cannot allocate initial memory for data\n");
        return -1;
    }

    newEdge->label = symbol; // assigning symbol and to_state in the the arc
    newEdge->state = to_state;

    return slist_append(from_state->_transitions, newEdge); //add the new arc to the transition using appand

}


pm_state_t* pm_goto_get(pm_state_t *state, unsigned char symbol) { //NEED TESTING
    if(!state) {
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
    if (!pm  || !str)
        return -1;

    if(n == 0) {
        printf("the string is empty");
        return 0;
    }

    if((pm->newstate + n) > PM_CHARACTERS){
        printf("error: string exceeded max symbols (256)");
        return -1;
    }

    pm_state_t *currentRoot = pm->zerostate;
    pm_state_t *next;
    int i;

    for(i = 0; i < n; i++){
        if((next = pm_goto_get(currentRoot,str[i])) == NULL) { //current state is empty
            pm_state_t *state = (pm_state_t *) malloc(sizeof(pm_state_t)); //create a new state
            if (!state) { //checking allocation
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

            if (!(state->output) || !(state->_transitions)) {
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
            if(next == pm_goto_get(currentRoot, str[i])) {
               //printf("test 6");
                currentRoot = next; //state exist -> go to the next state
              }
             }
        //printf("goto_get on current root succeed\n");

        if(next = pm_goto_get(currentRoot, str[i])) {
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




int pm_makeFSM(pm_t *pm_tree){
    slist_t* queue = (slist_t*)malloc(sizeof(slist_t));
    if (!queue){
        pm_destroy(pm_tree);
        return -1;
    }

    slist_init(queue); //initiate queue
    slist_node_t* edge = slist_head(pm_tree->zerostate->_transitions);
    if(failToZero(pm_tree, queue, edge) == -1)  //define zerostate to the first level states
        return -1;


    while (slist_size(queue) > 0){
        pm_state_t *current = slist_pop_first(queue); //check the first-in-line state
        if (!current) //if queue is empty, exit
            break;

        edge = slist_head(current->_transitions);

        while (edge){
            pm_state_t* origin = ((pm_labeled_edge_t*)slist_data(edge))->state;
            if (slist_append(queue, origin) == -1) {
                pm_destroy(origin);
                return -1;
            }

            pm_state_t *fail_status = current->fail;
            unsigned char symbol = ((pm_labeled_edge_t*)slist_data(edge))->label;
            findEdge(pm_tree, &(fail_status), symbol); //find the edge by going over the fail-states

            if (pm_goto_get(fail_status, symbol)){ //if the is a path to fail state for the symbol
                if((FStateSetAndPrint(&(origin) , fail_status, symbol)) == -1) //set and print a fail-state
                    return -1;
            }
            edge = slist_next(edge);
        }
    }
    slist_destroy(queue, SLIST_LEAVE_DATA);
    return 0;
}

//define the fail state of dept 1 to be zerostate
int failToZero(pm_t *pm_tree, slist_t* queue, slist_node_t *edge) {
    while (edge){
        pm_state_t* tmp_state = ((pm_labeled_edge_t*)slist_data(edge))->state;
        if (slist_append(queue, tmp_state) == -1) {
            pm_destroy(pm_tree);
            return -1;
        }
        edge = slist_next(edge);
        tmp_state->fail = pm_tree->zerostate;
    }
    return 0;
}

//search for the edge of the char by hoping back to the prvious fail state.
// if the fail is NULL, the state fail will be the zerostate
void findEdge(pm_t *pm_tree, pm_state_t **fail, unsigned char symbol) {
    while (!pm_goto_get((*fail), symbol)) {
        if (!(*fail)) {
            (*fail) = pm_tree->zerostate;
            break;
        }
        (*fail) = (*fail)->fail;
    }
}

//set and print the fail state
int FStateSetAndPrint(pm_state_t **origin ,pm_state_t *fail, unsigned char symbol){
                (*origin)->fail = pm_goto_get(fail, symbol); //set the fail state on the origin (source)
                printf("Setting f(%d) = %d\n", (*origin)->id, (*origin)->fail->id);

                if (!(*origin)->output && (*origin)->fail->output){ //allocate output list
                    (*origin)->output = (slist_t*)calloc(1, sizeof(slist_t));
                    if (!(*origin)->output){

                        return -1;
                    }
                }

                //add the the fail state to origin output
                if (slist_append_list((*origin)->output, (*origin)->fail->output) == -1){
                    pm_destroy(origin);
                    return -1;
                }
                return 0;
}

void pm_destroy(pm_t *pm_tree) {
    if(!pm_tree) {
        exit(-1);
    }

    slist_node_t *queue;
    queue = pm_tree->zerostate->slist_head(_transitions);
    stateDestructor(pm_tree->zerostate, queue);
    free(pm_tree);
}

void stateDestructor(pm_state_t* state, slist_node_t *queue){
    if(!queue)
        return;

    stateDestructor(state, queue->next);

    slist_destroy(state->_transitions, SLIST_FREE_DATA);
    slist_destroy(state->output, SLIST_LEAVE_DATA);
    free(state);
}
