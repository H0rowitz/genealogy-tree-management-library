#include "header/mcduck.h"
#include "header/node.h"
#include "header/tree.h"

bool isRootMember(generic_type member) {
    return ( (member->nbChildren > 0) 
    && 
        (member->children[0]->parents[0]->parents[0] == NULL 
        && member->children[0]->parents[0]->parents[1] == NULL)
    ); 
}

int main(int argc, char* argv[]) {
    Duck root_A = createDuck("A", ",", ",");
    Duck root_B = createDuck("B", ",", ",");
    Duck enfant_C = createDuck("enfant_AB_C", ",", ",");
    Duck enfant_D = createDuck("enfant_AB_D", ",", ",");

    Duck femme_E = createDuck("femme_D",",",","); 
    Duck enfant_F = createDuck("enfant_ED_F", ",", ",");
    Duck enfant_G = createDuck("enfant_ED_G", ",", ",");

    Duck femme_H = createDuck("femme_G", ",", ",");
    Duck enfant_I = createDuck("enfant_GH_I", ",", ",");
    
    Tree tree = initTree(root_A); 

    _the_wedding_present(tree, root_A, root_B); 
    _addChild(tree, root_A, root_B, enfant_C); 
    _addSibling(tree, enfant_C, enfant_D); 

    _the_wedding_present(tree, enfant_D, femme_E); 
    _addChild(tree, enfant_D, femme_E, enfant_F); 
    _addSibling(tree, enfant_F, enfant_G); 

    _the_wedding_present(tree, enfant_G, femme_H); 
    _addChild(tree, enfant_G, femme_H, enfant_I); 

    displayAttributsNodes(tree); 

    printf("\n==SHOW PART==\n"); 
    _show(tree, root_A); 

    printf("\n==SEARCH PART==\n");
    _search(tree, root_B, is_same, enfant_C); 

    printf("\n==GLOBAL SEARCH PART==\n");
    _globalSearch(tree, root_A, isRootMember, is_same, enfant_C); 

    _delete_from_node(tree, root_A); 

    return 0;
}
