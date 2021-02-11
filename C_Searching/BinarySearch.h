//
// Created by Rvioleck on 2021/2/6.
//

#ifndef C_SEARCHING_BINARYSEARCH_H
#define C_SEARCHING_BINARYSEARCH_H

#include <iostream>
using namespace std;
#define ElemType char
#define MAXLEN 100

typedef struct{
    ElemType elem[MAXLEN];
    int TableLen;
}SeqList;

void InitSeqList(SeqList &L){
    L.TableLen = 0;
}

void CreateSeqList(SeqList &L){
    InitSeqList(L);
    ElemType data;
    cin>>data;
    int i = 1;
    while (data != '#'){
        L.elem[i++] = data;
        L.TableLen++;
        cin>>data;
    }
    L.elem[0] = L.TableLen;
}

void PrintSeqList(SeqList L){
    for (int i = 1; i <= L.TableLen; ++i) {
        cout<<L.elem[i]<<" ";
    }
    cout<<endl;
}

typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

bool InitList(LinkList &L) {
    // 带头结点初始化
    L = (LNode *) malloc(sizeof(LNode)); // 分配一个头结点
    if (L == nullptr) {
        return false;
    }
    L->next = nullptr;
    return true;
}

bool isEmpty(LinkList L) {
    // 判断是否为空
    return L->next == nullptr;
}

void ShowList(LinkList L) {
    // 带头结点的show
    printf("The Linklist is: ");
    LNode *p = L->next;
    while (p != nullptr) {
        cout<<p->data<<" ";
        p = p->next;
    }
    printf("\n");
}

LinkList TailInsert(LinkList &L){
    // 尾插法建立单链表;
    char x;
    InitList(L);
    LNode *s, *r = L; //  r为表尾指针
    cin>>x;
    while (x != '#'){
        s = (LNode*)malloc(sizeof(LNode));
        s->data = x;
        r->next = s;
        r = s;
        cin>>x;
    }
    r->next = nullptr;
    return L;
}

#endif //C_SEARCHING_BINARYSEARCH_H
