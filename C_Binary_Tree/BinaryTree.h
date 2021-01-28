//
// Created by Rvioleck on 2021/1/28.
//

#ifndef C_BINARY_TREE_BINARYTREE_H
#define C_BINARY_TREE_BINARYTREE_H

#include
#include <stdio.h>
#include <stdlib.h>
#define ElemType char

typedef struct BiTNode{
    ElemType data;    // ������
    struct BiTNode *lchild, *rchild;   // ���Һ���
}BiTNode, *BiTree;

void InitTree(BiTree &tree){
    tree->lchild = NULL;
    tree->rchild = NULL;
}

void visit(BiTree tree){
    if (tree){
        printf("%d->", tree->data);
    }
}

void PreOrder(BiTree tree){
    if (tree != NULL){
        visit(tree);             // ���ʸ��ڵ�
        PreOrder(tree->lchild);  // ����������
        PreOrder(tree->rchild);  // ����������
    }
}

void InOrder(BiTree tree){
    if (tree != NULL){
        InOrder(tree->lchild);
        visit(tree);
        InOrder(tree->rchild);
    }
}

void InOrder2(BiTree tree){

}

void PostOrder(BiTree tree){
    if (tree != NULL){
        PostOrder(tree->lchild);
        PostOrder(tree->rchild);
        visit(tree);
    }
}


#endif //C_BINARY_TREE_BINARYTREE_H
