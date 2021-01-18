//
// Created by Rvioleck on 2021/1/18.
//

#ifndef C_LINEAR_LIST_SEQUENCELISTDYNAMICALLOC_H
#define C_LINEAR_LIST_SEQUENCELISTDYNAMICALLOC_H

#endif //C_LINEAR_LIST_SEQUENCELISTDYNAMICALLOC_H


#define INITSIZE 10   // 默认的最大容量
#define ElemType int

typedef struct{
    ElemType* data; // 动态分配大小
    int maxSize;    // 顺序表当前最大容量
    int length;     // 顺序表当前长度
}sqList;

void InitList(sqList &L){
    // 用malloc申请一片连续的存储空间
    L.data = (ElemType*)malloc(INITSIZE*sizeof(ElemType));
    for (int i = 0; i < INITSIZE; i++) {
        L.data[i] = i;
    }
    L.length = 10;
    L.maxSize = INITSIZE;
}

void ShowList(sqList L){
    for (int i = 0; i < L.length; i++) {
        printf("data[%d] = %d\n", i, L.data[i]);
    }
}

void IncreaseSize(sqList &L, int len){
    // 动态扩充顺序表大小
    int *p = L.data;
    L.data = (ElemType*)malloc((L.maxSize + len)*sizeof(ElemType));
    for (int i = 0; i < L.length; i++) {
        L.data[i] = p[i];     // 将数据复制到新区域
    }
    L.maxSize += len;
    free(p);
}

void AddList(sqList &L, int elem){
    L.data[L.length] = elem;
    L.length++;
}