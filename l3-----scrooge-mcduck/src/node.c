#include "header/mcduck.h"
#include "header/node.h"

generic_type createNode(Duck duck) {
    generic_type member = malloc(sizeof(struct node));  
    member->children = malloc(sizeof(generic_type));  
    member->current = duck;
    member->parents[0] = NULL; 
    member->parents[1] = NULL; 
    member->partner = NULL; 
    member->nbChildren = 0; 
    if(member == NULL) exit(1); 
    return member;   
}

static void _addChildren(generic_type parent, generic_type child) {
    size_t size = ++parent->nbChildren;
    parent->children = realloc(parent->children, sizeof(generic_type) * size);
    if (parent->children == NULL) exit(1);
    parent->children[size-1] = child;
}

void addChild(generic_type parent1, generic_type parent2, generic_type new_child) {
    if (parent1==NULL && parent2==NULL) exit(1); 
    if (parent2 == NULL) {
        _addChildren(parent1, new_child);
        new_child->parents[0] = parent1;
    } else if (parent1 == NULL) {
        _addChildren(parent2, new_child);
        new_child->parents[1] = parent2;
    } else {
        _addChildren(parent1, new_child);
        _addChildren(parent2, new_child);
        new_child->parents[0] = parent1;
        new_child->parents[1] = parent2;
    }
}

void the_wedding_present(generic_type node, generic_type other_node) {
    node->partner = other_node; 
    other_node->partner = node; 
}

void search(generic_type current_point, bool(*searchFunction)(void*,void*), Duck other_duck) { 
    if(searchFunction(current_point->current, other_duck)) printf("condition OK: %s\n", current_point->current->name);
    for (unsigned int i = 0; i < current_point->nbChildren; ++i) {
        search(current_point->children[i], searchFunction, other_duck);
    }
}

void show(generic_type current_point) {
    if(current_point->current != NULL ) {
        printf("%s ", current_point->current->name);
        printf("(");
        for(unsigned int i = 0; i < current_point->nbChildren; ++i) {
            if(current_point->children[i]->nbChildren == 0) {
                printf("%s%s", current_point->children[i]->current->name, i+1 == current_point->nbChildren ? "" : ", ");
            } else {
                show(current_point->children[i]);
            }
        }
        printf(")");
    } 
}

void _destruct_node(generic_type node) {
    free(node->current);
    free(node->children);
    free(node);
    node->children = NULL; 
    node->current = NULL; 
    node = NULL; 
}
 
void delete_from_node(generic_type current_point) {
    if (current_point == NULL) return; 
    for(unsigned int i = 0; i < current_point->nbChildren; ++i) {
        delete_from_node(current_point->children[i]);
    }
    _destruct_node(current_point); 
}

/*SEARCH ON GLOBAL TREE :
 * 1) from node : toRoot(){ while toRoot() }
 * 2) from root : toNode(){ while toNode() }
*/
bool isOrphelin(generic_type orphelin) {
    return (orphelin->parents[0] == NULL && orphelin->parents[1] == NULL); 
}

void globalSearch(generic_type current_node, 
    bool(*searchRoot)(generic_type), bool(*searchNode)(void*,void*),Duck other_duck) {

    if(searchRoot(current_node)){
        printf("ROOT MEMBER: %s\n", current_node->current->name);
        search(current_node, searchNode, other_duck); 
        return;
    } 
    // Ne pas rester bloqué dans un root local (sub_root)
    for(unsigned int i = 0; i < 2; ++i) { 
        if (current_node->parents[i] != NULL) {
            globalSearch(current_node->parents[i], searchRoot, searchNode, other_duck); 
        } else if (current_node->nbChildren > 0) {
            // repasse par enfant pour atteindre autre parent d'indice not(i)
            if (isOrphelin(current_node)) { 
                if (current_node->children[0]->parents[!(i)]->parents[0] != NULL 
                    || current_node->children[0]->parents[!(i)]->parents[1] != NULL) {
                    globalSearch(current_node->children[0]->parents[!(i)], searchRoot, searchNode, other_duck); 
                }
            }
        }
    }    
}           
