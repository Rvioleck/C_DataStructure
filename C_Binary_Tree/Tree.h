//
// Created by Rvioleck on 2021/2/1.
//

#ifndef C_BINARY_TREE_TREE_H
#define C_BINARY_TREE_TREE_H
#include <iostream>
using namespace std;

#define ElemType char
#define MAX_TREE_SIZE 100

//<editor-fold desc="顺序存储——双亲表示法">
typedef struct{
    ElemType data;
    int parent;  // 双亲位置域
}PTNode;

typedef struct{
    PTNode nodes[MAX_TREE_SIZE];
    int n;    // 结点数
}PTree;
//</editor-fold>

//<editor-fold desc="顺序+链式存储——孩子表示法">
struct CTNode{
    int child; // 孩子在数组结点中的位置
    struct CTNode *next;  // 下一个孩子
};

typedef struct {
    ElemType data;
    struct CTNode* firstChild; // 第一个孩子的位置
}CTBox;

typedef struct{
    CTBox nodes[MAX_TREE_SIZE];
    int n;  // 结点数量
    int r;  // 根的位置
}CTree;
//</editor-fold>

//<editor-fold desc="链式存储——孩子兄弟表示法">
typedef struct CSNode{
    ElemType data;
    struct CSNode* firstChild, *nextSibling;
}CSNode, *CSTree;
//</editor-fold>

void PreOrder(CSTree tree){
    /// 孩子兄弟表示法的先根遍历(同于二叉树的先序遍历)
    if (tree){
        printf("%c ",tree->data);
        PreOrder(tree->firstChild);
        PreOrder(tree->nextSibling);
    }
}

void PostOrder(CSTree tree){
    /// 孩子兄弟表示法的后根遍历(同于二叉树的中序遍历)
    if (tree){
        PostOrder(tree->firstChild);
        printf("%c ",tree->data);
        PostOrder(tree->nextSibling);
    }
}

#endif //C_BINARY_TREE_TREE_H
