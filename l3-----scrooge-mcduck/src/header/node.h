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
 * \param _ le premier objet de la famille
*/
gen_t create_node(void*);

/*!
 * fonction permettant d'ajouter un frère ou une soeur à un noeud
 * \param noeud le noeud sur lequel on va devoir ajouter le frere ou la soeur
 * \param _ le objet à ajouter en tant que frere ou soeur
*/
void _addSibling(gen_t, void*);

/*!
 * fonction permettant d'ajouter un enfant à un couple de noeuds
 * dont un des deux peut être NULL 
 * \param noeud1 parent n°1 
 * \param noeud2 parent n°2
 * \param noeud3 l'enfant à ajouter
*/
void _addChild(gen_t, gen_t, gen_t);

/*!
 * fonction permettant de marier 2 noeuds
 * \param node à marier n°1
 * \param node à marier n°2
*/
void _the_wedding_present(gen_t, gen_t);

/*!
 * fonction permettant de rechercher un noeud dans l'arbre parmis les descendants
 * et les /!\ frères et soeurs /!\ d'un noeud donné
 * \param noeud à partir duquel on commence la recherche
 * \param func permettant de comparer deux objets de même type générique 
 * \param _ l'objet que l'on cherche 
*/
void* _search(gen_t, bool(*)(void*,void*), void*);

/*!
 * fonction permettant d'afficher la descendance d'un noeud d'un arbre
 * \param noeud à partir duquel on commence à afficher la descendance
 * \param func permettant de cast un objet en string 
 * \param num pour le formatage des distances
*/
void _show(gen_t, char*(*)(void*), int);

/*!
 * fonction permettant de détruire une descendance à partir d'un noeud
 * \param noeud à partir duquel on commence à detruire la descendance
 * \param func permettant de déréférencer un objet de type générique.  
*/
void _delete_from_node(gen_t, void(*)(void*));

/*!
 * Global search :
 * 1) Up getting to root, condition: root has no parents 
 * 2) Down getting to node 
 * Ne pas rester bloqué dans un root local (sub_root): 
 *      - repasse par un enfant si bloqué 
 *      - atteint parents[not(i)]
 * \param noeud à partir duquel on cherche 
 * \param func_str fonction permettant de cast un objet de type générique
 * \param searchRoot 
 * \param searchNode 
 * \param _ objet de type générique que l'on cherche  
*/
void* _global_search(gen_t, char*(*)(void*), bool(*)(void*), bool(*)(void*,void*), void*);

/*!
 * fonction permettant de savoir si un noeud ne possède pas de parent(s)
 * \param noeud sur lequel on veut obtenir l'information des parents
*/
bool _is_orphelin(gen_t);

/**
 * return true if member is root 
 * \param _ objet de type générique
 */
bool is_root_member(void*);

#endif
    