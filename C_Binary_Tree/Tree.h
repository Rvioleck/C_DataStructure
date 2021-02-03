//
// Created by Rvioleck on 2021/2/1.
//

#ifndef C_BINARY_TREE_TREE_H
#define C_BINARY_TREE_TREE_H
#include <iostream>
using namespace std;

#define ElemType char
#define MAX_TREE_SIZE 100

//<editor-fold desc="˳��洢����˫�ױ�ʾ��">
typedef struct{
    ElemType data;
    int parent;  // ˫��λ����
}PTNode;

typedef struct{
    PTNode nodes[MAX_TREE_SIZE];
    int n;    // �����
}PTree;
//</editor-fold>

//<editor-fold desc="˳��+��ʽ�洢�������ӱ�ʾ��">
struct CTNode{
    int child; // �������������е�λ��
    struct CTNode *next;  // ��һ������
};

typedef struct {
    ElemType data;
    struct CTNode* firstChild; // ��һ�����ӵ�λ��
}CTBox;

typedef struct{
    CTBox nodes[MAX_TREE_SIZE];
    int n;  // �������
    int r;  // ����λ��
}CTree;
//</editor-fold>

//<editor-fold desc="��ʽ�洢���������ֵܱ�ʾ��">
typedef struct CSNode{
    ElemType data;
    struct CSNode* firstChild, *nextSibling;
}CSNode, *CSTree;
//</editor-fold>

void PreOrder(CSTree tree){
    /// �����ֵܱ�ʾ�����ȸ�����(ͬ�ڶ��������������)
    if (tree){
        printf("%c ",tree->data);
        PreOrder(tree->firstChild);
        PreOrder(tree->nextSibling);
    }
}

void PostOrder(CSTree tree){
    /// �����ֵܱ�ʾ���ĺ������(ͬ�ڶ��������������)
    if (tree){
        PostOrder(tree->firstChild);
        printf("%c ",tree->data);
        PostOrder(tree->nextSibling);
    }
}

#endif //C_BINARY_TREE_TREE_H
