#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mcduck.h" 
 
typedef struct node* family_member; 
typedef family_member generic_type; 

struct node {
    Duck current;
    generic_type parents[2]; 
    generic_type *children;
    generic_type partner; 
    size_t nbChildren;
};

/*!
 * fonction permettant d'initialiser un arbre
 * \param canard le premier canard de la famille
*/
generic_type createNode(Duck);

/*!
 * fonction permettant d'ajouter un frère ou une soeur a un canard (noeud de l'arbre)
 * \param noeud le noeud sur lequel on va devoir ajouter le frere ou la soeur
 * \param canard le canard a ajouter en tant que frere ou soeur
*/
void addSibling(generic_type, Duck);

/*!
 * fonction permettant d'ajouter un enfant a un couple de canard
 * \param canard1 parent n°1
 * \param canard2 parent n°2
 * \param canard3 l'enfant a ajouter
*/
void addChild(generic_type, generic_type, generic_type);

/*!
 * fonction permettant de marrier 2 canard (noeud de l'arbre)
 * \param canard1 le canard a marrier n°1
 * \param canard2 le canard a marrier n°2
*/
void the_wedding_present(generic_type, generic_type);

/*!
 * fonction permettant de rechercher un noeud dans l'arbre parmis les descendant
 * et les /!\ frères et soeur /!\ d'un noeud donner
 * \param canard le canard a partir du qu'elle on commence la recherche
 * \param function la fonction de recherche TODO 
*/
void search(generic_type, bool(*)(void*,void*), Duck);

/*!
 * fonction permettant d'afficher la descendance d'un noeud d'un arbre
 * \param canard le canard a partir du qu'elle on commence a afficher la descendance
*/
void show(generic_type);

/*!
 * fonction permettant de detruire une descendance a partir d'un noeud idéal après avoir rager sur fortnite
 * \param canard le canard a partir du qu'elle on commence a detruire la descendance
*/
void delete_tree_from_node(generic_type);

/*!
 * Global search :
 * 1) Up getting to root, condition: root has no parents 
 * 2) Down getting to node 
*/
void globalSearch(generic_type, bool(*)(generic_type), bool(*)(void*,void*), Duck);  

/*!
 * Helper functions 
*/
void display(generic_type);
void displayChild(generic_type);

#endif
