# Projet MCDUCK-PIPOO 

## Compilation w/ makefile
```sh
$ gcc -std=c99 -Wall -pedantic src/main.c -o main.out src/mcduck.c src/node.c src/tree.c
or 
$ make -f MakeFile 
```
## Execution
```sh
$ ./main.out 
or
$ ./main
```
Create a duck
```c
Duck create_duck(char*, char*, char*);
```
Initiate the family members tree from root node
```c
Tree init_tree(void*);
```
Add a sibling  
```c
void add_sibling(Tree, void*, void*); 
```
Add a child 
```c
void add_child(Tree, void*, void*, void*);
```
Proceed to wedding two family members
```c
void the_wedding_present(Tree, void*, void*); 
```
Search for a specific duck  
```c
void* search(Tree, void*, bool(*)(void*,void*),void*);
```
Output the sub-family members
```c
void show(Tree, char*(*)(void*), void*);
```
Delete sub-family members from node 
```c
void delete_from_node(Tree, void(*)(void*), void*); 
```
Search for a node through all the tree  
```c
void* global_search(Tree, void*, char*(*)(void*), bool(*)(void*), bool(*)(void*,void*), void*); 
```

### Current output of the main() function:
```bash
==STRUCTURE OF THE TREE==
0 Name: A 	         Parents: NULL & NULL
1 Name: B 	         Parents: NULL & NULL
2 Name: enfant_AB_C 	Parents: A & B
3 Name: enfant_AB_D 	Parents: A & B
4 Name: enfant_AB_J 	Parents: A & B
5 Name: femme_C 	   Parents: NULL & NULL
6 Name: enfant_CC 	  Parents: femme_C & enfant_AB_C
7 Name: femme_D 	   Parents: NULL & NULL
8 Name: enfant_ED_F 	Parents: enfant_AB_D & femme_D
9 Name: enfant_ED_G 	Parents: enfant_AB_D & femme_D
10 Name: femme_G 	   Parents: NULL & NULL
11 Name: enfant_GH_I 	Parents: enfant_ED_G & femme_G

==SHOW PART==
A ------- B
 (enfant_AB_C ------- femme_C
   ( enfant_CC ) enfant_AB_D ------- femme_D
     ( enfant_ED_F , enfant_ED_G ------- femme_G
       ( enfant_GH_I ) )  enfant_AB_J ) 

==SEARCH PART==
enfant_CC

==GLOBAL SEARCH PART==
ROOT MEMBER: A
ROOT MEMBER: B
enfant_ED_G
```

## Graphviz rendering (w.r.t 2 root members)
![Graphviz rendering (w.r.t 2 root members)](l3-----scrooge-mcduck/images/graph.png)