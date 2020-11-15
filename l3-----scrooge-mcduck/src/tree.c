#include "header/tree.h"
#include <stdio.h>

Tree init_tree(void* data) {
    gen_t root_duck = create_node(data); 
    Tree newTree = malloc(sizeof(struct tree)); 
    newTree->nodes = malloc(sizeof(gen_t));
    newTree->nbNode = 1;
    newTree->root = root_duck;
    newTree->nodes[newTree->nbNode-1] = root_duck; 
    if(newTree == NULL) exit(1); 
    return newTree;
} 

/*
 * On as fait le choix de passer la méthode en static
 * car cela ajouter trop de fonctions en parametre et donc rendez le code
 * illisible pour l'utilisateur
*/
gen_t getMemberByAttributs(Tree tree, void* data) {
    for(size_t i = 0; i < tree->nbNode; ++i) {
        if (is_same(tree->nodes[i]->data, data)) {
            return tree->nodes[i]; 
        }
    }
    return NULL; 
}

void add_sibling(Tree tree, void* sibling, void* new_sibling) {
    gen_t _sibling = getMemberByAttributs(tree, sibling);
    void* new_parent1 = getMemberByAttributs(tree, _sibling->parents[0]->data)->data;
    void* new_parent2 = getMemberByAttributs(tree, _sibling->parents[1]->data)->data;
    if (new_parent1 == NULL && new_parent2 == NULL) exit(1); 
    add_child(tree, new_parent1, new_parent2, new_sibling); 
}

void add_child(Tree tree, void* parent1, void* parent2, void* child) {  
    gen_t new_parent1 = (parent1 == NULL) ? NULL : getMemberByAttributs(tree, parent1);
    gen_t new_parent2 = (parent2 == NULL) ? NULL : getMemberByAttributs(tree, parent2); 
    if (new_parent1 == NULL && new_parent2 == NULL) exit(1); 
    gen_t new_child = create_node(child);
    _addChild(new_parent1, new_parent2, new_child); 
    tree->nodes = realloc(tree->nodes, sizeof(gen_t) * ++(tree->nbNode));
    tree->nodes[tree->nbNode-1] = new_child; 
}

void the_wedding_present(Tree tree, void* partner1, void* partner2) {
    gen_t new_partner2 = create_node(partner2); 
    gen_t new_partner1 = getMemberByAttributs(tree, partner1);  
    _the_wedding_present(new_partner1, new_partner2); 
    tree->nodes = realloc(tree->nodes, sizeof(gen_t) * ++(tree->nbNode));
    tree->nodes[tree->nbNode-1] = new_partner2; 
}

void* search(Tree tree, void* duck, bool(*searchFunction)(void*,void*), void* other_duck) {
    gen_t _duck = getMemberByAttributs(tree, duck);    
    return _search(_duck, searchFunction, other_duck); 
}

void show(Tree tree, char*(*str)(void*), void* duck) {
    gen_t _duck = getMemberByAttributs(tree, duck); 
    _show(_duck, str, 2); 
}

void delete_from_node(Tree tree, void(*destructFunc)(void*), void* duck) {
    gen_t _duck = getMemberByAttributs(tree, duck); 
    _delete_from_node(_duck, destructFunc);  
}

void* global_search(Tree tree, void* duck, char*(*str)(void*), bool(*searchRoot)(void*), bool(*searchNode)(void*,void*), void* other_duck) {
    gen_t _duck = getMemberByAttributs(tree, duck); 
    return _global_search(_duck, str, searchRoot, searchNode, other_duck); 
}  


void create_graph_viz(Tree tree, char*(*str)(void*)) {
    FILE *file = fopen("graph.dot", "w+");
    if(file == NULL) exit(EXIT_FAILURE);

    fprintf(file, "graph {\n");
    for(unsigned int i = 0; i < tree->nbNode; ++i) {
        for(unsigned int ii = 0; ii < tree->nodes[i]->nbChildren; ++ii) {
            fprintf(file, "\t%s -- %s;\n", str(tree->nodes[i]->data), str(tree->nodes[i]->children[ii]->data));
        }
    }
    fprintf(file, "}");
    fclose(file);
}


void display_tree_structure(Tree tree, char*(str)(void*)) {
    for (size_t i = 0; i < tree->nbNode; ++i) {
        gen_t node = tree->nodes[i]; 
        char* parent1 = (node->parents[0]) ? str(node->parents[0]->data):"NULL"; 
        char* parent2 = (node->parents[1]) ? str(node->parents[1]->data):"NULL"; 
        printf("%zu Name: %s \tParents: %s & %s\n", 
            i, 
            str(node->data), 
            parent1, 
            parent2
        ); 
    }
}
