#include "header/mcduck.h"
#include "header/node.h"

generic_type createNode(Duck duck) {
    generic_type member = malloc(sizeof(struct node));    
    member->current = duck;
    member->parents[0] = NULL; 
    member->parents[1] = NULL; 
    member->partner = NULL; 
    member->children = malloc(sizeof(generic_type));
    member->nbChildren = 0; 
    return member;   
}

static void _addChildren(generic_type parent, generic_type child) {
    size_t size = ++parent->nbChildren; 
    parent->children = realloc(parent->children, sizeof(generic_type) * size);
    if (parent->children == NULL) exit(1);
    parent->children[size-1] = child;
}

void addChild(generic_type parent1, generic_type parent2, generic_type new_child) {
    _addChildren(parent1, new_child);
    _addChildren(parent2, new_child);
    new_child->parents[0] = parent1;
    new_child->parents[1] = parent2;
}

void the_wedding_present(generic_type node, generic_type other_node) {
    node->partner = other_node; 
    other_node->partner = node; 
}

void search(generic_type current_point, bool(*searchFunction)(generic_type a)) { 
    if(searchFunction(current_point)) printf("condition OK: %s\n", current_point->current->name);
    for (unsigned int i = 0; i < current_point->nbChildren; ++i) {
        search(current_point->children[i], searchFunction);
    }
}

void printDescendance(generic_type current_point) {
    for (unsigned int i = 0; i < current_point->nbChildren; ++i) {
        printf("* nom (père: %s): %s\n", 
            current_point->current->name,
            current_point->children[i]->current->name
        );
        printDescendance(current_point->children[i]);
    }
}

void show(generic_type current_point) {
    if (current_point->parents[0] != NULL){
        printf("Frères et soeurs: \n");
        for (unsigned int i = 0; i < current_point->parents[0]->nbChildren; ++i){
            printf("* nom: %s\n", current_point->parents[0]->children[i]->current->name);
        }
    } else {
        printf("%s has no siblings.\n", current_point->current->name); 
    }
    printf("Déscendance:\n");
    printDescendance(current_point); 
}
 
void delete_tree_from_node(generic_type current_point) {
    if (current_point == NULL) return; 
    for(unsigned int i = 0; i < current_point->nbChildren; ++i) {
        delete_tree_from_node(current_point->children[i]);
    }
    free(current_point);  
}

// HELPER FUNCTIONS 
void display(generic_type member) {
    printf("Current member: %s\n", member->current->name); 
    for(unsigned int i = 0; i < 2; ++i) 
        printf("parent %d: %s, nb enfants : %zu\n", i, member->parents[i]->current->name, member->parents[i]->nbChildren); 
}

void displayChild(generic_type parent) {
    printf("Current member: %s\n", parent->current->name); 
    for(unsigned int i = 0; i < parent->nbChildren; ++i) {
        printf("Children %d: %s\n", 
            i, 
            parent->children[i]->current->name
        );
    }
}

/*SEARCH ON GLOBAL TREE :
 * 1) from node : toRoot(){ while toRoot() }
 * 2) from root : toNode(){ while toNode() }
*/
unsigned int not(unsigned int i){
    return (i == 1) ? 0 : 1; 
}

bool isOrphelin(generic_type orphelin) {
    return (orphelin->parents[0] == NULL && orphelin->parents[1] == NULL); 
}

void globalSearch(generic_type current_node, 
    bool(*searchRoot)(generic_type member1), bool(*searchNode)(generic_type member2)) {

    if(searchRoot(current_node)){
        printf("ROOT MEMBER: %s\n", current_node->current->name);
        search(current_node, searchNode); 
        return; // just need one root 
    } 
    // Ne pas rester bloqué dans un root local 
    for(unsigned int i = 0; i < 2; ++i) { 
        if (current_node->parents[i] != NULL) {
            globalSearch(current_node->parents[i], searchRoot, searchNode); 
        } else if (current_node->nbChildren > 0) {
            if (isOrphelin(current_node)) { // repasse par enfant pour atteindre autre parent: not(i)
                if (current_node->children[0]->parents[not(i)]->parents[0] != NULL 
                    || current_node->children[0]->parents[not(i)]->parents[1] != NULL) {
                    globalSearch(current_node->children[0]->parents[not(i)], searchRoot, searchNode); 
                }
            }
        }
    }    
}           
