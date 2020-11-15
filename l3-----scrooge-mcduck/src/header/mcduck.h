#ifndef DUCK_H
#define DUCK_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct duck* Duck;

struct duck {
    char *name;
    char *firstname;
    char *surname;
};

/*!
 * fonction permettant de créer un duck
 * \param name le prenom du duck
 * \param firstName le nom de famille du duck
 * \param surname le surnom porté par le duck
 * \return un duck
*/
Duck create_duck(char*, char*, char*);

/**
 * Comparaison entre deux objets du même type générique. 
 */
bool is_same(void*, void*);

/**
 * fonction permettant de cast un duck en chaîne de caractères 
 * \param duck à display
 */
char* to_string_duck(void*);

/**
 * \param objet à déréférencer 
 */
void destruct(void*);

/**
 * \param duck attributs à output 
 */
void display_duck(void*);

#endif
