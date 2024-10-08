#include "header/mcduck.h"
#include "header/node.h"

size_t get_nb_set_parents(gen_t m) {
    size_t n = 0; 
    for(size_t i = 0; i < 2; ++i){
        if (m->parents[i] != NULL) n++; 
    }
    return n; 
}

gen_t create_node(void* data) {
    gen_t member = malloc(sizeof(struct node));  
    member->children = malloc(sizeof(gen_t));  
    member->data = data;
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



void _show(gen_t current_point, char*(*str)(void*), int n) {
    if(current_point->data != NULL) {
        printf("%s ------- %s\n", str(current_point->data), str(current_point->partner->data));
        printf("%*s", n, "(");
        for(unsigned int i = 0; i < current_point->nbChildren; ++i) {
            if(current_point->children[i]->nbChildren == 0) {
                printf(" %s %s", str(current_point->children[i]->data), i+1 == current_point->nbChildren ? "" : ", ");
            } else {
                _show(current_point->children[i], str, n+=2);
            }
        }
        printf(") ");
    }
}


// delegaton fonction destruct de la data
void _destruct_node(gen_t node, void(*destructFunc)(void*)) {
    destructFunc(node->data);
    free(node->data);
    free(node->children);
    node->children = NULL;
    node->data = NULL;
    free(node);
    node = NULL;
}
 
void _delete_from_node(gen_t current_point, void(*destructFun)(void*)) {
    if (current_point == NULL) return;
    for(size_t i = 0; i < current_point->nbChildren; ++i) {
        _delete_from_node(current_point->children[i], destructFun);
    }
    _destruct_node(current_point, destructFun);
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

void* _search(gen_t current_point, bool(*is_same)(void*,void*), void* data) {  
    if(is_same(current_point->data, data))
        return current_point->data; 
    void* found = NULL;
    void* temp = NULL;
    for (size_t i = 0; i < current_point->nbChildren; ++i)  {
        temp = _search(current_point->children[i], is_same, data);
        found = temp ? temp:found;  
    }
    return found;
}

void* _global_search(gen_t current_node, char*(*str)(void*), bool(*searchRoot)(void*), bool(*searchNode)(void*,void*), void* data) {
    if(searchRoot(current_node)){
        printf("ROOT MEMBER: %s\n", str(current_node->data));
        return _search(current_node, searchNode, data); 
    }
    void* found = NULL;
    void* temp = NULL; 
    for(size_t i = 0; i < get_nb_set_parents(current_node); ++i) 
        temp = _global_search(current_node->parents[i], str, searchRoot, searchNode, data);
        found = temp ? temp:found; 
    if (_is_orphelin(current_node) && current_node->nbChildren > 0) {
        if (current_node->children[0]->parents[0] != NULL 
        && searchNode(current_node->data, current_node->children[0]->parents[0]->data)==0) {
            temp = _global_search(current_node->children[0]->parents[0], str, searchRoot, searchNode, data); 
            found = temp ? temp:found;  
        } else if (current_node->children[0]->parents[1] != NULL 
        && searchNode(current_node->data, current_node->children[0]->parents[1]->data)==0) {
            temp = _global_search(current_node->children[0]->parents[1], str, searchRoot, searchNode, data);
            found = temp ? temp:found; 
        }
    }
    return found; 
}
