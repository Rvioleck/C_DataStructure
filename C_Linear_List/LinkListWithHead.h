//
// Created by Rvioleck on 2021/1/18.
//

#ifndef C_LINEAR_LIST_LINKLISTWITHHEAD_H
#define C_LINEAR_LIST_LINKLISTWITHHEAD_H

#endif //C_LINEAR_LIST_LINKLISTWITHHEAD_H

#include <cstdio>
#include <cstdlib>

typedef struct LNode {
    int data;
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

LNode *GetElem(LinkList L, int i) {
    if (i < 0)
        return nullptr;
    LNode *p = L;
    int j = 0;
    while (j != i && p != nullptr) {
        p = p->next;
        j++;
    }
    return p;
}

bool InsertNextNode(LNode *p, char e) {
    // 后插操作：在结点p后插入元素e
    if (p == nullptr)
        return false;
    LNode *s = (LNode *) malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}

bool InsertNextNode(LNode *p, LNode *s){
    // 后插操作：在结点p后插入结点s
    if (p == nullptr || s == nullptr)
        return false;
    s->next = p->next;
    p->next = s;
    return true;
}

bool InsertPriorNode(LNode *p, char e) {
    // 前插操作：在结点p前插入元素e
    if (p == nullptr)
        return false;
    LNode *s = (LNode *) malloc(sizeof(LNode));
    s->data = p->data;
    p->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}

bool InsertPriorNode(LNode *p, LNode *s) {
    // 前插操作：在结点p前插入结点s
    if (p == nullptr || s == nullptr)
        return false;
    char tmp = s->data;
    s->data = p->data;
    p->data = tmp;
    s->next = p->next;
    p->next = s;
    return true;
}

bool ListInsert(LinkList &L, int i, char e) {
    // 按位序i插入元素e，带头结点
    if (i < 1)
        return false;
    LNode *p = GetElem(L, i - 1);
    return InsertNextNode(p, e);
}

bool ListDelete(LinkList &L, int i, char &e) {
    // 删除第i个结点，并且用e来返回删除结点
    if (i < 1)
        return false;
    LNode *p = GetElem(L, i - 1);
    if (p == nullptr || p->next == nullptr)
        return false;
    LNode *q = p->next;
    e = q->data;
    p->next = q->next;
    free(q);
    return true;
}

int GetLength(LinkList L){
    int len = 0;
    LNode *p = L;
    while (p->next != nullptr){
        len++;
        p = p->next;
    }
    return len;
}

void ShowList(LinkList L) {
    // 带头结点的show
    printf("The Linklist is: ");
    LNode *p = L;
    while (p->next != nullptr) {
        p = p->next;
        printf("%d->", p->data);
    }
    printf("NULL, the length is %d\n", GetLength(L));
}

LinkList TailInsert(LinkList &L){
    // 尾插法建立单链表;
    char x;
    InitList(L);
    LNode *s, *r = L; //  r为表尾指针
    scanf("%c", &x);
    while (x != '0'){
        s = (LNode*)malloc(sizeof(LNode));
        s->data = x;
        r->next = s;
        r = s;
        scanf("%c", &x);
    }
    r->next = nullptr;
    return L;
}

LinkList HeadInsert(LinkList &L){
    // 头插法建立单链表
    char x;
    LNode *s;
    L = (LNode*)malloc(sizeof(LNode));
    L->next = nullptr;
    scanf("%c", &x);
    while (x != '0'){
        s = (LNode*)malloc(sizeof(LNode));
        s->data = x;
        s->next = L->next;
        L->next = s;
        scanf("%c", &x);
    }
    return L;
}

void ShowCList(LinkList L){
    printf("The Linklist is: ");
    LNode *p = L;
    while (p->next != L) {
        p = p->next;
        printf("%d->", p->data);
    }
    printf("NULL\n");
}

LinkList toCircleLinkList(LinkList L){
    if (isEmpty(L)){
        L->next = L;
    }else{
        LNode *cur = L->next;
        while (cur->next){
            cur = cur->next;
        }
        cur->next = L;
    }
    return L;
}