//
// Created by Rvioleck on 2021/1/18.
//

#ifndef C_LINEAR_LIST_LINKLISTWITHOUTHEAD_H
#define C_LINEAR_LIST_LINKLISTWITHOUTHEAD_H

#endif //C_LINEAR_LIST_LINKLISTWITHOUTHEAD_H

#include <stdio.h>
#include <cstdlib>

typedef struct LNode{
    int data;
    struct LNode* next;
}LNode, *LinkList;

bool InitList(LinkList &L){
    // 不带头结点初始化
    L = NULL; // 空表，暂时不含任何结点
    return true;
}

bool Empty(LinkList L){
    return L==NULL;
}

bool ListInsert(LinkList &L, int i, int e){
    // 按位序i插入元素e，不带头结点
    if (i < 1)
        return false;
    if (i == 1){
        LNode *s = (LNode*)malloc(sizeof(LNode));
        s->data = e;
        s->next = L;
        L = s;
        return true;
    }
    LNode *p = L;
    int j = 1;
    while (p != NULL && j != i-1){
        p = p->next;
        j++;
    }
    if (p == NULL)
        return false;
    LNode *s = (LNode*)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}

void ShowList(LinkList L){
    // 不带头结点的show
    while (L != NULL){
        printf("%d->", L->data);
        L = L->next;
    }
    printf("NULL\n");
}