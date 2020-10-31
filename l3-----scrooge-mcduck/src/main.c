#include "header/mcduck.h"
#include "header/node.h"
#include "header/tree.h"

bool isRootMember(gen_t member) {
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
    
    the_wedding_present(tree, root_A, root_B); 
    addChild(tree, root_A, root_B, enfant_C); 
    addSibling(tree, enfant_C, enfant_D); 

    the_wedding_present(tree, enfant_D, femme_E); 
    addChild(tree, enfant_D, femme_E, enfant_F); 
    addSibling(tree, enfant_F, enfant_G); 

    the_wedding_present(tree, enfant_G, femme_H); 
    addChild(tree, enfant_G, femme_H, enfant_I); 

    printf("\n==STRUCTURE OF THE TREE==\n");
    displayTreeStructure(tree); 

    printf("\n==SHOW PART==\n"); 
    show(tree, root_A); printf("\n");

    printf("\n==SEARCH PART==\n");
    search(tree, root_B, is_same, enfant_C); 

    printf("\n==GLOBAL SEARCH PART==\n");
    globalSearch(tree, enfant_I, isRootMember, is_same, enfant_C); 
    
    createGraphViz(tree);
    
    delete_from_node(tree, root_A); 

    return 0;
}
