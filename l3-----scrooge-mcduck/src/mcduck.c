#include "header/mcduck.h"

Duck create_duck(char* name, char* firstname, char* surname){
    Duck duck = malloc(sizeof(struct duck)); 
    /*
    duck->name = name;
    duck->firstname = firstname; 
    duck->surname = surname;
    */
    duck->name = strdup(name);  
    duck->firstname = strdup(firstname); 
    duck->surname = strdup(surname);
    if(duck == NULL) exit(1);  
    return duck; 
}

void display_duck(void* md) {
    Duck tmp = (Duck)md;
    strcmp(tmp->surname,"") == 0 ? printf("%s %s\t", tmp->firstname, tmp->name) : 
    printf("%s \"%s\" %s\n", tmp->firstname, tmp->surname, tmp->name);
}

bool is_same(void *m, void *m1) {
    Duck tmp = (Duck)m;
    Duck tmp1 = (Duck)m1;
    return (strcmp(tmp->name, tmp1->name) == 0 
        && strcmp(tmp->firstname, tmp1->firstname) == 0 
        && strcmp(tmp->surname, tmp1->surname) == 0);
}
