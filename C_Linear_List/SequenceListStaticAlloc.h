//
// Created by Rvioleck on 2021/1/18.
//
#include <stdio.h>
#ifndef C_LINEAR_LIST_SEQUENCELIST_H
#define C_LINEAR_LIST_SEQUENCELIST_H

#endif //C_LINEAR_LIST_SEQUENCELIST_H

#define MAXSIZE 100
#define ElemType int

typedef struct {
    ElemType data[MAXSIZE]; // 静态分配内存大小
    int length;
} SeqList;

void InitList(SeqList &L) {
    L.length = 0;
}

void ShowList(SeqList L) {
    for (int i = 0; i < L.length; i++) {
        printf("data[%d] = %d\n", i, L.data[i]);
    }
    printf("\n");
}

bool ListInsert(SeqList &L, int i, ElemType e) {
    if (L.length >= MAXSIZE || i < 1 || i > L.length + 1) {
        return false;
    } else {
        for (int j = L.length; j >= i; j--) {
            L.data[j] = L.data[j - 1];
        }
        L.data[i - 1] = e;
        L.length++;
        return true;
    }
}

bool ListDelete(SeqList &L, int i, ElemType &e) {
    if (L.length >= MAXSIZE || i > L.length || i < 1) {
        return false;
    } else {
        e = L.data[i - 1];
        for (int j = i; j < L.length; j++) {
            L.data[j - 1] = L.data[j];
        }
        L.length--;
        return true;
    }
}

bool GetElem(SeqList L, int i, ElemType &e){
    if (i > L.length || i < 1) {
        return false;
    } else {
        e = L.data[i - 1];
        return true;
    }
}

bool LocateElem(SeqList L, ElemType e, int &i){
    for (int j = 0; j < L.length; ++j) {
        if (e == L.data[j]){
            i = j + 1;
            return true;
        }
    }
    return false;
}

