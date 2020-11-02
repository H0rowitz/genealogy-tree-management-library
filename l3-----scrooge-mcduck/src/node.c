#include "header/mcduck.h"
#include "header/node.h"

size_t get_nb_set_parents(gen_t m) {
    size_t n = 0; 
    for(size_t i = 0; i < 2; ++i){
        if (m->parents[i] != NULL) n++; 
    }
    return n; 
}

gen_t create_node(Duck duck) {
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

void _show(gen_t current_point) {
    if(current_point->current != NULL) {
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

bool is_root_member(void* m) {
    gen_t member = (gen_t)m;
    return ( (member->nbChildren > 0) 
    && 
        (member->children[0]->parents[0]->parents[0] == NULL 
        && member->children[0]->parents[0]->parents[1] == NULL)
    ); 
}

Duck _search(gen_t current_point, bool(*searchFunction)(void*,void*), Duck other_duck) {  
    if(searchFunction(current_point->current, other_duck)) 
        return current_point->current;
    Duck found = NULL;
    for (size_t i = 0; i < current_point->nbChildren; ++i) 
        found = _search(current_point->children[i], searchFunction, other_duck); 
    return found;
}
   
Duck _global_search(gen_t current_node, bool(*searchRoot)(void*), bool(*searchNode)(void*,void*), Duck other_duck) {
    if(searchRoot(current_node)){
        printf("ROOT MEMBER: %s\n", current_node->current->name);
        return _search(current_node, searchNode, other_duck); 
    }

    Duck found = NULL; 
    for(size_t i = 0; i < get_nb_set_parents(current_node); ++i) 
        found = _global_search(current_node->parents[i], searchRoot, searchNode, other_duck);
        
    if (_is_orphelin(current_node) && current_node->nbChildren > 0) {
        if (current_node->children[0]->parents[0] != NULL 
        && searchNode(current_node->current, current_node->children[0]->parents[0]->current)==0) {
            found = _global_search(current_node->children[0]->parents[0], searchRoot, searchNode, other_duck);
        } else if (current_node->children[0]->parents[1] != NULL 
        && searchNode(current_node->current, current_node->children[0]->parents[1]->current)==0) {
            found = _global_search(current_node->children[0]->parents[1], searchRoot, searchNode, other_duck);
        }
    }
    return found; 
}
