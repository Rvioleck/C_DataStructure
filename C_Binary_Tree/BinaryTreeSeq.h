//
// Created by Rvioleck on 2021/1/28.
//

#ifndef C_BINARY_TREE_BINARYTREESEQ_H
#define C_BINARY_TREE_BINARYTREESEQ_H
#include "stdio.h"
#include "stdlib.h"

#define MAXSIZE 32 // 最大结点数
#define ElemType char

typedef ElemType SqBinTree[MAXSIZE + 1];

void InitTree(SqBinTree tree){
    for (int i = 1; i <= MAXSIZE; ++i) {
        tree[i] = '#'; // 记作为空
    }
}

#endif //C_BINARY_TREE_BINARYTREESEQ_H
