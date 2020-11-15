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
 * permet de rajouter un frère ou une soeur à un objet quelconque qui n'est pas un root.  
 * \param tree
 * \param already_child de type générique 
 * \param new_child soeur/frère nouvellement né(e) de type générique 
*/
void add_sibling(Tree, void*, void*); 

/*!
 * fonction permettant de faire enfanter aux parents
 * ou de faire adopter un parent (un des parents peut être NULL)
 * \param tree 
 * \param parent1 
 * \param parent2
 * \param new_child 
*/
void add_child(Tree, void*, void*, void*);

/*!
 * fonction permettant de connecter deux nodes par l'intérmédiaire de partner
 * \param tree 
 * \param parent1
 * \param parent2 
*/
void the_wedding_present(Tree, void*, void*); 

/**
 * permet de récupérer un family_member en comparant ses attributs
 * part du principe que les croisements de données entre attributs 
 * sont uniques et de même type.    
 * \param tree
 * \param _  
*/
gen_t getMemberByAttributs(Tree, void*); 

/*!
 * fonction permettant de rechercher un noeud dans l'arbre parmis les descendant
 * et les /!\ frères et soeurs /!\ d'un noeud donné
 * \param tree 
 * \param _ l'objet à partir duquel on commence la recherche
 * \param function la fonction de comparaison 
 * \param _ l'objet recherché  
*/
void* search(Tree, void*, bool(*)(void*,void*),void*);

/*!
 * fonction permettant d'afficher la descendance d'un noeud dans un arbre
 * \param tree  
 * \param func de display 
 * \param duck à partir duquel on commence à afficher la descendance
*/
void show(Tree, char*(*)(void*), void*);

/*!
 * fonction permettant de détruire la descendance d'un objet   
 * \param tree 
 * \param func de déstruction d'objet de type générique
 * \param _ objet à partir duquel on commence à détruire la déscendance
*/
void delete_from_node(Tree, void(*)(void*), void*); 

/**
 * Global search :
 * 1) Up getting to root, condition: root has no parents 
 * 2) Down getting to node 
 * \param tree 
 * \param duck à partir duquel on cherche 
 * \param func_str permet de cast en string un objet de type générique 
 * \param func_search fonction recherche 
 * \param func de comparaison 
 * \param _ objet que l'on cherche 
*/
void* global_search(Tree, void*, char*(*)(void*), bool(*)(void*), bool(*)(void*,void*), void*); 

/**
 * generate a .dot file to format a graph of the tree 
 * \param tree
 * \param func fonction de conversion en chaîne de caractères 
*/
void create_graph_viz(Tree, char*(*)(void*));

/**
 * std out the structure of the tree 
 * \param tree
 * \param func fonction de conversion en chaîne de caractères 
*/
void display_tree_structure(Tree, char*(*)(void*));


#endif
