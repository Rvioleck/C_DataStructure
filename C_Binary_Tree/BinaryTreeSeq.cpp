//
// Created by Rvioleck on 2021/1/28.
//

#include "BinaryTreeSeq.h"

char latestCommonAncestor(SqBinTree tree, int i, int j){
    if (tree[i] == '#' || tree[j] == '#')
        return '#';
    while (i != j){
        if (i > j){
            i /= 2;
        }else
            j /= 2;
    }
    return tree[i];
}

int main(){
    SqBinTree tree;
    printf("%d", latestCommonAncestor(tree, 9, 16));
}