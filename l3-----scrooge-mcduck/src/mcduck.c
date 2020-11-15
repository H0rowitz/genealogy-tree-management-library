#include "header/mcduck.h"

Duck create_duck(char* name, char* firstname, char* surname){
    Duck duck = malloc(sizeof(struct duck)); 
    duck->name = strdup(name);  
    duck->firstname = strdup(firstname); 
    duck->surname = strdup(surname);
    if(duck == NULL) exit(1);  
    return duck; 
}

void display_duck(void* md) {
    Duck tmp = (Duck)md;
    strcmp(tmp->surname,"") == 0 ? printf("%s %s\t", tmp->firstname, tmp->name) : 
    printf("%s\n", tmp->name);
}

char* to_string_duck(void* duck) {
    Duck tmp = (Duck)duck;
    return tmp->name;
}

void destruct(void* duck) {
    Duck tmp = (Duck) duck;
    free(tmp->name);
    free(tmp->firstname);
    free(tmp->surname);
    tmp->name = NULL;
    tmp->firstname = NULL;
    tmp->surname = NULL;
}

bool is_same(void *m, void *m1) {
    Duck tmp = (Duck)m;
    Duck tmp1 = (Duck)m1;
    return (strcmp(tmp->name, tmp1->name) == 0 
        && strcmp(tmp->firstname, tmp1->firstname) == 0 
        && strcmp(tmp->surname, tmp1->surname) == 0);
}
