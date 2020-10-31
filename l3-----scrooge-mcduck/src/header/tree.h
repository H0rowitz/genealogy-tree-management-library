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
 * \param canard
*/
Tree initTree(Duck);

/**
 * permet de rejouter un frère ou une soeur à un canard quelconque non root 
 * \param tree
 * \param already_child
 * \param the_fake_present soeur/frère nouvellement né(e)
*/
void addSibling(Tree, Duck, Duck); 

/*!
 * fonction permettant de faire enfanter aux parents
 * \param tree 
 * \param parent1 
 * \param parent2
 * \param new_child 
*/
void addChild(Tree, Duck, Duck, Duck);

/*!
 * fonction permettant de connecter deux nodes par l'intérmédiraire de partner
 * \param tree 
 * \param parent1
 * \param parent2 
*/
void the_wedding_present(Tree, Duck, Duck); 

/**
 * permet de récupérer un family_member en comparant ses attributs
 * part du principe que les croisements entre attributs sont uniques.   
 * \param tree
 * \param duck  
*/
gen_t getMemberByAttributs(Tree, Duck); 

/*!
 * fonction permettant de rechercher un noeud dans l'arbre parmis les descendant
 * et les /!\ frères et soeur /!\ d'un noeud donner
 * \param tree le canard a partir du qu'elle on commence la recherche
 * \param canard 
 * \param function la fonction de recherche TODO 
*/
void search(Tree, Duck, bool(*)(void*,void*),Duck);

/*!
 * fonction permettant d'afficher la descendance d'un noeud d'un arbre
 * \param tree  
 * \param canard le canard a partir du qu'elle on commence a afficher la descendance
*/
void show(Tree, Duck);

/*!
 * fonction permettant de detruire une descendance a partir 
 * d'un noeud idéal après avoir ragé sur fortnite
 * \param tree 
 * \param canard le canard a partir duquel on commence à détruire la déscendance (root)
*/
void delete_from_node(Tree, Duck); 

/**
 * Global search :
 * 1) Up getting to root, condition: root has no parents 
 * 2) Down getting to node 
*/
void global_search(Tree, Duck, bool(*)(gen_t), bool(*)(void*,void*), Duck); 

/**
 * generate a .dot file to format a graph of the tree 
*/
void createGraphViz(Tree tree);

/**
 * output the characteristics of the tree node 
*/
void displayTreeStructure(Tree tree);

#endif
