#include "header/tree.h"
#include <stdio.h>

Tree initTree(Duck duck) {
    generic_type root_duck = createNode(duck); 
    Tree newTree = malloc(sizeof(struct tree)); 
    newTree->nodes = malloc(sizeof(generic_type));
    newTree->nbNode = 1;
    newTree->root = root_duck;
    newTree->nodes[newTree->nbNode-1] = root_duck; 
    return newTree;
} 

generic_type getMemberByName(Tree tree, Duck other_duck) {
    for(size_t i = 0; i < tree->nbNode; ++i) {
        if (is_same(tree->nodes[i]->current, other_duck)) {
            return tree->nodes[i]; 
        }
    }
    return NULL; 
}

void _addSibling(Tree tree, Duck sibling, Duck new_sibling) {
    generic_type _sibling = getMemberByName(tree, sibling);
    Duck new_parent1 = getMemberByName(tree, _sibling->parents[0]->current)->current;
    Duck new_parent2 = getMemberByName(tree, _sibling->parents[1]->current)->current;
    _addChild(tree, new_parent1, new_parent2, new_sibling); 
}

void _addChild(Tree tree, Duck parent1, Duck parent2, Duck child) {  
    generic_type new_parent1 = getMemberByName(tree, parent1); 
    generic_type new_parent2 = parent2 == NULL ? NULL : getMemberByName(tree, parent2); 
    generic_type new_child = createNode(child);
    addChild(new_parent1, new_parent2, new_child); 
    tree->nodes = realloc(tree->nodes, sizeof(generic_type) * ++(tree->nbNode));
    tree->nodes[tree->nbNode-1] = new_child; 
}

void _the_wedding_present(Tree tree, Duck partner1, Duck partner2) {
    generic_type new_partner2 = createNode(partner2); 
    generic_type new_partner1 = getMemberByName(tree, partner1);  
    the_wedding_present(new_partner1, new_partner2); 
    tree->nodes = realloc(tree->nodes, sizeof(generic_type) * ++(tree->nbNode));
    tree->nodes[tree->nbNode-1] = new_partner2; 
}

void _search(Tree tree, Duck duck, bool(*searchFunction)(void*,void*), Duck other_duck) {
    generic_type _duck = getMemberByName(tree, duck); 
    search(_duck, searchFunction, other_duck); 
}

void _show(Tree tree, Duck duck) {
    generic_type _duck = getMemberByName(tree, duck); 
    show(_duck); 
}

void _delete_from_node(Tree tree, Duck duck) {
    generic_type _duck = getMemberByName(tree, duck); 
    delete_tree_from_node(_duck);  
}

void _globalSearch(Tree tree, Duck duck, 
    bool(*searchRoot)(generic_type), bool(*searchNode)(void*,void*), Duck other_duck) {
    generic_type _duck = getMemberByName(tree, duck); 
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

// HELPER FUCNTION
void displayAttributsNodes(Tree tree) {
    for (size_t i = 0; i < tree->nbNode; ++i) {
        generic_type node = tree->nodes[i]; 
        if (node->parents[0]!=NULL){
            printf("%zu Name: %s\t\tParents: %s & %s\n", 
                i, 
                node->current->name, 
                node->parents[0]->current->name, 
                node->parents[1]->current->name
            ); 
        } else {
            printf("%zu Name: %s\t\t\tParents: %s & %s\n", 
                i, 
                node->current->name, 
                "NULL", 
                "NULL"
            );      
        }
    }
}
