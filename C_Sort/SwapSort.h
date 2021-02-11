//
// Created by Rvioleck on 2021/2/9.
//

#ifndef C_SORT_SWAPSORT_H
#define C_SORT_SWAPSORT_H

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


#endif //C_SORT_SWAPSORT_H
