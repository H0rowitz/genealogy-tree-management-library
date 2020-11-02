#include "header/tree.h"
#include <stdio.h>

Tree init_tree(Duck duck) {
    gen_t root_duck = create_node(duck); 
    Tree newTree = malloc(sizeof(struct tree)); 
    newTree->nodes = malloc(sizeof(gen_t));
    newTree->nbNode = 1;
    newTree->root = root_duck;
    newTree->nodes[newTree->nbNode-1] = root_duck; 
    if(newTree == NULL) exit(1); 
    return newTree;
} 

gen_t getMemberByAttributs(Tree tree, Duck other_duck) {
    for(size_t i = 0; i < tree->nbNode; ++i) {
        if (is_same(tree->nodes[i]->current, other_duck)) {
            return tree->nodes[i]; 
        }
    }
    return NULL; 
}

void add_sibling(Tree tree, Duck sibling, Duck new_sibling) {
    gen_t _sibling = getMemberByAttributs(tree, sibling);
    Duck new_parent1 = getMemberByAttributs(tree, _sibling->parents[0]->current)->current;
    Duck new_parent2 = getMemberByAttributs(tree, _sibling->parents[1]->current)->current;
    if (new_parent1 == NULL && new_parent2 == NULL) exit(1); 
    add_child(tree, new_parent1, new_parent2, new_sibling); 
}

void add_child(Tree tree, Duck parent1, Duck parent2, Duck child) {  
    gen_t new_parent1 = (parent1 == NULL) ? NULL : getMemberByAttributs(tree, parent1);
    gen_t new_parent2 = (parent2 == NULL) ? NULL : getMemberByAttributs(tree, parent2); 
    if (new_parent1 == NULL && new_parent2 == NULL) exit(1); 
    gen_t new_child = create_node(child);
    _addChild(new_parent1, new_parent2, new_child); 
    tree->nodes = realloc(tree->nodes, sizeof(gen_t) * ++(tree->nbNode));
    tree->nodes[tree->nbNode-1] = new_child; 
}

void the_wedding_present(Tree tree, Duck partner1, Duck partner2) {
    gen_t new_partner2 = create_node(partner2); 
    gen_t new_partner1 = getMemberByAttributs(tree, partner1);  
    _the_wedding_present(new_partner1, new_partner2); 
    tree->nodes = realloc(tree->nodes, sizeof(gen_t) * ++(tree->nbNode));
    tree->nodes[tree->nbNode-1] = new_partner2; 
}

Duck search(Tree tree, Duck duck, bool(*searchFunction)(void*,void*), Duck other_duck) {
    gen_t _duck = getMemberByAttributs(tree, duck);    
    return _search(_duck, searchFunction, other_duck); 
}

void show(Tree tree, Duck duck) {
    gen_t _duck = getMemberByAttributs(tree, duck); 
    _show(_duck); 
}

void delete_from_node(Tree tree, Duck duck) {
    gen_t _duck = getMemberByAttributs(tree, duck); 
    _delete_from_node(_duck);  
}

Duck global_search(Tree tree, Duck duck, bool(*searchRoot)(void*), bool(*searchNode)(void*,void*), Duck other_duck) {
    gen_t _duck = getMemberByAttributs(tree, duck); 
    return _global_search(_duck, searchRoot, searchNode, other_duck); 
}  

void create_graph_viz(Tree tree) {
    FILE *file = fopen("graph.dot", "w+");
    if(file == NULL) exit(EXIT_FAILURE);

    fprintf(file, "graph {\n");
    for(unsigned int i = 0; i < tree->nbNode; ++i) {
        for(unsigned int ii = 0; ii < tree->nodes[i]->nbChildren; ++ii) {
            fprintf(file, "\t%s -- %s;\n", tree->nodes[i]->current->name, tree->nodes[i]->children[ii]->current->name);
        }
    }
    fprintf(file, "}");
    fclose(file);
}

void display_tree_structure(Tree tree) {
    for (size_t i = 0; i < tree->nbNode; ++i) {
        gen_t node = tree->nodes[i]; 
        char* parent1 = (node->parents[0]) ? node->parents[0]->current->name:"NULL"; 
        char* parent2 = (node->parents[1]) ? node->parents[1]->current->name:"NULL"; 
        printf("%zu Name: %s \tParents: %s & %s\n", 
            i, 
            node->current->name, 
            parent1, 
            parent2
        ); 
    }
}
