#ifndef TREE_H
#define TREE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "mcduck.h" 
#include "node.h"

typedef struct tree *Tree;

struct tree {
    size_t nbNode;
    family_member root;
    family_member* nodes;
};

/*!
 * fonction permettant d'initialiser un arbre
 * \param _ objet de type générique 
*/
Tree init_tree(void*);

/**
 * permet de rejouter un frère ou une soeur à un duck quelconque non root 
 * \param tree
 * \param already_child de type générique 
 * \param the_fake_present soeur/frère nouvellement né(e) de type générique 
*/
void add_sibling(Tree, void*, void*); 

/*!
 * fonction permettant de faire enfanter aux parents
 * \param tree 
 * \param parent1 
 * \param parent2
 * \param new_child 
*/
void add_child(Tree, void*, void*, void*);

/*!
 * fonction permettant de connecter deux nodes par l'intérmédiraire de partner
 * \param tree 
 * \param parent1
 * \param parent2 
*/
void the_wedding_present(Tree, void*, void*); 

/**
 * permet de récupérer un family_member en comparant ses attributs
 * part du principe que les croisements entre attributs sont uniques.   
 * \param tree
 * \param duck  
*/
gen_t getMemberByAttributs(Tree, void*); 

/*!
 * fonction permettant de rechercher un noeud dans l'arbre parmis les descendant
 * et les /!\ frères et soeurs /!\ d'un noeud donné
 * \param tree le duck à partir duquel on commence la recherche
 * \param duck 
 * \param function la fonction de recherche 
 * \param duck recherché  
*/
void* search(Tree, void*, bool(*)(void*,void*),void*);

/*!
 * fonction permettant d'afficher la descendance d'un noeud d'un arbre
 * \param tree  
 * \param func de display 
 * \param duck à partir duquel on commence à afficher la descendance
*/
void show(Tree, char*(*)(void*), void*);

/*!
 * fonction permettant de detruire une descendance à partir 
 * d'un noeud
 * \param tree 
 * \param func de destruction d'objet de type générique
 * \param duck à partir duquel on commence à détruire la déscendance (root)
*/
void delete_from_node(Tree, void(*)(void*), void*); 

/**
 * Global search :
 * 1) Up getting to root, condition: root has no parents 
 * 2) Down getting to node 
 * \param tree 
 * \param duck à partir duquel on cherche 
 * \param func_str fonction de display et conversion en chaîne de caractères 
 * \param func_search fonction recherche 
 * \param func de comparaison 
 * \param duck que l'on cherche 
*/
void* global_search(Tree, void*, char*(*)(void*), bool(*)(void*), bool(*)(void*,void*), void*); 

/**
 * generate a .dot file to format a graph of the tree 
 * \param tree
 * \param func fonction de display et conversion en chaîne de caractères 
*/
void create_graph_viz(Tree, char*(*)(void*));

/**
 * std out the structure of the tree 
 * \param tree
 * \param func fonction de display et conversion en chaîne de caractères 
*/
void display_tree_structure(Tree, char*(*)(void*));


#endif
