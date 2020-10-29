#include "header/tree.h"
#include <stdio.h>

Tree initTree(Duck duck) {
    generic_type root_duck = createNode(duck); 
    Tree newTree = malloc(sizeof(struct tree)); 
    newTree->nodes = malloc(sizeof(generic_type));
    newTree->nbNode = 1;
    newTree->root = root_duck;
    newTree->nodes[newTree->nbNode-1] = root_duck; 
    if(newTree == NULL) exit(1); 
    return newTree;
} 

generic_type getMemberByAttributs(Tree tree, Duck other_duck) {
    for(size_t i = 0; i < tree->nbNode; ++i) {
        if (is_same(tree->nodes[i]->current, other_duck)) {
            return tree->nodes[i]; 
        }
    }
    return NULL; 
}

void _addSibling(Tree tree, Duck sibling, Duck new_sibling) {
    generic_type _sibling = getMemberByAttributs(tree, sibling);
    Duck new_parent1 = getMemberByAttributs(tree, _sibling->parents[0]->current)->current;
    Duck new_parent2 = getMemberByAttributs(tree, _sibling->parents[1]->current)->current;
    _addChild(tree, new_parent1, new_parent2, new_sibling); 
}

void _addChild(Tree tree, Duck parent1, Duck parent2, Duck child) {  
    generic_type new_parent1 = (parent1==NULL) ? NULL : getMemberByAttributs(tree, parent1);
    generic_type new_parent2 = (parent2==NULL) ? NULL : getMemberByAttributs(tree, parent2); 
    generic_type new_child = createNode(child);
    addChild(new_parent1, new_parent2, new_child); 
    tree->nodes = realloc(tree->nodes, sizeof(generic_type) * ++(tree->nbNode));
    tree->nodes[tree->nbNode-1] = new_child; 
}

void _the_wedding_present(Tree tree, Duck partner1, Duck partner2) {
    generic_type new_partner2 = createNode(partner2); 
    generic_type new_partner1 = getMemberByAttributs(tree, partner1);  
    the_wedding_present(new_partner1, new_partner2); 
    tree->nodes = realloc(tree->nodes, sizeof(generic_type) * ++(tree->nbNode));
    tree->nodes[tree->nbNode-1] = new_partner2; 
}

void _search(Tree tree, Duck duck, bool(*searchFunction)(void*,void*), Duck other_duck) {
    generic_type _duck = getMemberByAttributs(tree, duck); 
    search(_duck, searchFunction, other_duck); 
}

void _show(Tree tree, Duck duck) {
    generic_type _duck = getMemberByAttributs(tree, duck); 
    show(_duck); 
}

void _delete_from_node(Tree tree, Duck duck) {
    generic_type _duck = getMemberByAttributs(tree, duck); 
    delete_from_node(_duck);  
}

void _globalSearch(Tree tree, Duck duck, 
    bool(*searchRoot)(generic_type), bool(*searchNode)(void*,void*), Duck other_duck) {
    generic_type _duck = getMemberByAttributs(tree, duck); 
    globalSearch(_duck, searchRoot, searchNode, other_duck); 
}   

void createGraphViz(Tree tree) {
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

void displayTreeStructure(Tree tree) {
    for (size_t i = 0; i < tree->nbNode; ++i) {
        generic_type node = tree->nodes[i]; 
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
