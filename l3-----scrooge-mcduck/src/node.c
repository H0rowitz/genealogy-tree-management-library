#include "header/mcduck.h"
#include "header/node.h"

gen_t createNode(Duck duck) {
    gen_t member = malloc(sizeof(struct node));  
    member->children = malloc(sizeof(gen_t));  
    member->current = duck;
    member->parents[0] = NULL;
    member->parents[1] = NULL;
    member->partner = NULL;
    member->nbChildren = 0;
    if(member == NULL) exit(1);
    return member;
}

static void _addChildren(gen_t parent, gen_t child) {
    size_t size = ++parent->nbChildren;
    parent->children = realloc(parent->children, sizeof(gen_t) * size);
    if (parent->children == NULL) exit(1);
    parent->children[size-1] = child;
}

void _addChild(gen_t parent1, gen_t parent2, gen_t new_child) {
    if (parent1 == NULL && parent2 == NULL) exit(1);
    if (parent1 != NULL) {
        _addChildren(parent1, new_child);
        new_child->parents[0] = parent1;
    }
    if (parent2 != NULL) {
        _addChildren(parent2, new_child);
        new_child->parents[1] = parent2;
    } 
}

void _the_wedding_present(gen_t node, gen_t other_node) {
    node->partner = other_node; 
    other_node->partner = node; 
}

void _search(gen_t current_point, bool(*searchFunction)(void*,void*), Duck other_duck) { 
    if(searchFunction(current_point->current, other_duck)) 
        printf("Duck trouvé (depuis fonction): %s\n", current_point->current->name);
    for (size_t i = 0; i < current_point->nbChildren; ++i) {
        _search(current_point->children[i], searchFunction, other_duck); 
    }
}

void _show(gen_t current_point) {
    if(current_point->current != NULL ) {
        printf("%s ", current_point->current->name);
        printf("(");
        for(unsigned int i = 0; i < current_point->nbChildren; ++i) {
            if(current_point->children[i]->nbChildren == 0) {
                printf("%s%s", current_point->children[i]->current->name, i+1 == current_point->nbChildren ? "" : ", ");
            } else {
                _show(current_point->children[i]);
            }
        }
        printf(")");
    }
}

void _destruct_node(gen_t node) {
    free(node->current);
    free(node->children);
    free(node);
    node->children = NULL;
    node->current = NULL;
    node = NULL;
}
 
void _delete_from_node(gen_t current_point) {
    if (current_point == NULL) return;
    for(unsigned int i = 0; i < current_point->nbChildren; ++i) {
        _delete_from_node(current_point->children[i]);
    }
    _destruct_node(current_point);
}

bool _is_orphelin(gen_t orphelin) {
    return (orphelin->parents[0] == NULL && orphelin->parents[1] == NULL);
}

size_t get_nb_set_parents(gen_t m) {
    size_t n = 0; 
    for(size_t i = 0; i < 2; ++i){
        if (m->parents[i] != NULL) n++; 
    }
    return n; 
}

void _global_search(gen_t current_node, bool(*searchRoot)(gen_t), bool(*searchNode)(void*,void*), Duck other_duck) {

    if(searchRoot(current_node)){
        printf("ROOT MEMBER: %s\n", current_node->current->name);
        _search(current_node, searchNode, other_duck);
    }
    
     
    for(size_t i = 0; i < get_nb_set_parents(current_node); ++i) {
        if (current_node->parents[i] != NULL) {
            _global_search(current_node->parents[i], searchRoot, searchNode, other_duck);
        } else if (current_node->nbChildren > 0) {
            if (_is_orphelin(current_node)) {
                if (current_node->children[0]->parents[!(i)]->parents[0] != NULL 
                    || current_node->children[0]->parents[!(i)]->parents[1] != NULL) {
                    _global_search(current_node->children[0]->parents[!(i)], searchRoot, searchNode, other_duck); 
                }
            }
        }
    }       
}
