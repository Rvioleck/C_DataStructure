//
// Created by Rvioleck on 2021/2/11.
//

#ifndef C_SORT_SELECTSORT_H
#define C_SORT_SELECTSORT_H

#include <iostream>
using namespace std;
#define ElemType int
#define MaxSize 100

typedef struct {
    ElemType data[MaxSize];
    int len;
}SeqList;

void InitSeqList(SeqList &a){
    a.len = 0;
}

void CreateSeqList(SeqList &a, const int data[], int n){
    InitSeqList(a);
    for (int i = 0; i < n; ++i) {
        a.data[i] = data[i];
        a.len++;
    }
}

void showSeqList(SeqList a){
    for (int i = 0; i < a.len; ++i) {
        cout<<a.data[i]<<" ";
    }
    cout<<endl;
}

typedef struct LNode {
    char data;
    struct LNode *next;
} LNode, *LinkList;

bool InitList(LinkList &L) {
    // ��ͷ����ʼ��
    L = (LNode *) malloc(sizeof(LNode)); // ����һ��ͷ���
    if (L == nullptr) {
        return false;
    }
    L->next = nullptr;
    return true;
}

bool isEmpty(LinkList L) {
    // �ж��Ƿ�Ϊ��
    return L->next == nullptr;
}

void ShowList(LinkList L) {
    // ��ͷ����show
    printf("The Linklist is: ");
    LNode *p = L;
    while (p->next != nullptr) {
        p = p->next;
        cout<<p->data<<" ";
    }
    printf("\n");
}

LinkList TailInsert(LinkList &L){
    // β�巨����������;
    char x;
    InitList(L);
    LNode *s, *r = L; //  rΪ��βָ��
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



#endif //C_SORT_SELECTSORT_H
