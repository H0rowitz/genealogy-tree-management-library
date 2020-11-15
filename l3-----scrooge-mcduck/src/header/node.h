#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mcduck.h" 
 
typedef struct node* family_member; 
typedef family_member gen_t; // shorter 

struct node {
    void* data;
    gen_t parents[2]; 
    gen_t *children;
    gen_t partner; 
    size_t nbChildren;
};

/*!
 * fonction permettant d'initialiser un arbre
 * \param canard le premier canard de la famille
*/
gen_t create_node(void*);

/*!
 * fonction permettant d'ajouter un frère ou une soeur à un canard (noeud de l'arbre)
 * \param noeud le noeud sur lequel on va devoir ajouter le frere ou la soeur
 * \param canard le canard à ajouter en tant que frere ou soeur
*/
void _addSibling(gen_t, void*);

/*!
 * fonction permettant d'ajouter un enfant à un couple de canard
 * \param canard1 parent n°1
 * \param canard2 parent n°2
 * \param canard3 l'enfant à ajouter
*/
void _addChild(gen_t, gen_t, gen_t);

/*!
 * fonction permettant de marier 2 canards (noeud de l'arbre)
 * \param canard1 le canard à marrier n°1
 * \param canard2 le canard à marrier n°2
*/
void _the_wedding_present(gen_t, gen_t);

/*!
 * fonction permettant de rechercher un noeud dans l'arbre parmis les descendants
 * et les /!\ frères et soeurs /!\ d'un noeud donné
 * \param canard à partir duquel on commence la recherche
 * \param function de recherche TODO 
 * \param canard que l'on cherche 
*/
void* _search(gen_t, bool(*)(void*,void*), void*);

/*!
 * fonction permettant d'afficher la descendance d'un noeud d'un arbre
 * \param canard le canard à partir duquel on commence à afficher la descendance
*/
void _show(gen_t, char*(*)(void*), int);

/*!
 * fonction permettant de detruire une descendance à partir d'un noeud
 * \param canard le canard a partir duquel on commence à detruire la descendance
*/
void _delete_from_node(gen_t, void(*)(void*));

/*!
 * Global search :
 * 1) Up getting to root, condition: root has no parents 
 * 2) Down getting to node 
 *  // Ne pas rester bloqué dans un root local (sub_root): 
 *         - repasse par un enfant si bloqué 
 *         - atteint parents[not(i)]
 * \param tree 
 * \param duck à partir duquel on cherche 
 * \param searchRoot 
 * \param searchNode 
 * \param duck que l'on cherche  
*/
void* _global_search(gen_t, char*(*)(void*), bool(*)(void*), bool(*)(void*,void*), void*);

/*!
 * fonction permettant de savoir si un canard ne possède pas de parent(s)
 * \param canard le canard sur lequel on veut obtenir l'information des parents
*/
bool _is_orphelin(gen_t);

/**
 * return true if member is root
 */
bool is_root_member(void*);

#endif
    