#include "header/mcduck.h"
#include "header/node.h"
#include "header/tree.h"

int main(int argc, char* argv[]) {
    Duck root_A = create_duck("A", "name2", "name3");      
    Duck root_B = create_duck("B", ",", ",");
    Duck enfant_C = create_duck("enfant_AB_C", ",", ",");
    Duck enfant_D = create_duck("enfant_AB_D", ",", ",");
    Duck femme_C = create_duck("femme_C", ",", ",");
    Duck enfant_CC = create_duck("enfant_CC", ",", ",");

    Duck femme_E = create_duck("femme_D",",",","); 
    Duck enfant_F = create_duck("enfant_ED_F", ",", ",");
    Duck enfant_G = create_duck("enfant_ED_G", ",", ",");

    Duck femme_H = create_duck("femme_G", ",", ",");
    Duck enfant_I = create_duck("enfant_GH_I", ",", ",");

    Duck enfant_J = create_duck("enfant_AB_J", "", ""); 

    Tree tree = init_tree(root_A); 
        
    the_wedding_present(tree, root_A, root_B); 
    add_child(tree, root_A, root_B, enfant_C); 
    add_sibling(tree, enfant_C, enfant_D); 
    add_sibling(tree, enfant_D, enfant_J); 
    the_wedding_present(tree, enfant_C, femme_C);
    add_child(tree, femme_C, enfant_C, enfant_CC);

    the_wedding_present(tree, enfant_D, femme_E); 
    add_child(tree, enfant_D, femme_E, enfant_F); 
    add_sibling(tree, enfant_F, enfant_G); 

    the_wedding_present(tree, enfant_G, femme_H); 
    add_child(tree, enfant_G, femme_H, enfant_I); 

    printf("\n==STRUCTURE OF THE TREE==\n");
    display_tree_structure(tree, to_string_duck); 

    printf("\n==SHOW PART==\n"); 
    show(tree, to_string_duck, root_A); printf("\n");

    printf("\n==SEARCH PART==\n");
    Duck duck_found = search(tree, root_A, is_same, enfant_CC); 
    if (duck_found != NULL) {
        display_duck(duck_found); 
    } else {
        printf("duck not found 404");
    }
    
    printf("\n==GLOBAL SEARCH PART==\n");
    Duck duck_global_found = global_search(tree, femme_E, to_string_duck, is_root_member, is_same, enfant_G);
    if (duck_global_found != NULL) {
        display_duck(duck_global_found); 
    } else {
        printf("duck not found 404");
    }

    create_graph_viz(tree, to_string_duck);
    delete_from_node(tree, destruct, root_A); 
    
    return 0;
}
