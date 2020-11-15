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
 * fonction permettant de créer un canard
 * \param name le prenom du canard
 * \param firstName le nom de famille du canard
 * \param surname le surnom porté par le canard
 * \return un carnard
*/
Duck create_duck(char*, char*, char*);
bool is_same(void*, void*);
char* to_string_duck(void*);
void destruct(void*);
void display_duck(void*);

#endif
