//
// Created by Rvioleck on 2021/2/1.
//

#include "Tree.h"

int getTheNumberOfLeavesInForest(CSTree tree){
    static int count = 0;
    if (tree){
        if (tree->firstChild == NULL){
            count++;
        }
        getTheNumberOfLeavesInForest(tree->firstChild);
        getTheNumberOfLeavesInForest(tree->nextSibling);
    }
    return count;
}

int getTheHeightInTree(CSTree tree){
    if (!tree)
        return 0;
    int hc = getTheHeightInTree(tree->firstChild);
    int hs = getTheHeightInTree(tree->nextSibling);
    return hc+1 > hs ? hc+1 : hs;
}

int main(){

}