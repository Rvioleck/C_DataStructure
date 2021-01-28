//
// Created by Rvioleck on 2021/1/23.
//

#ifndef C_LINEAR_LIST_LINKSTACK_H
#define C_LINEAR_LIST_LINKSTACK_H

#include <cstdlib>
#include <cstdio>

#define ElemType int

typedef struct LNode{
    ElemType data;
    struct LNode *next;
} *LinkStack;

bool InitStack(LinkStack &S){
    S = (LNode*)malloc(sizeof(LNode));
    if (S == nullptr) // 分配内存失败
        return false;
    S->next = nullptr;
    return true;
}

bool Push(LinkStack &S, ElemType x){
    LNode *e = (LNode*)malloc(sizeof(LNode));
    e->data = x;
    e->next = S->next;
    S->next = e;
    return true;
}

bool Pop(LinkStack &S, ElemType &x){
    if (!S->next)
        return false;
    x = S->next->data;
    S->next = S->next->next;
    return true;
}

void Show(LinkStack &S){
    if (S->next){
        Show(S->next);
    }
    if (S){
        printf("%d->", S->data);
    }
}

void ShowStack(LinkStack &S){
    S = S->next;
    printf("From the bottom to the top: ");
    Show(S);
    printf("NULL\n");
}


#endif //C_LINEAR_LIST_LINKSTACK_H
