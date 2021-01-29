//
// Created by Rvioleck on 2021/1/24.
//

#ifndef C_LINEAR_LIST_CIRCLEQUEUE_H
#define C_LINEAR_LIST_CIRCLEQUEUE_H

#include "stdio.h"
#include "stdlib.h"

#define MaxSize 20
#define ElemType int

typedef struct{
    ElemType data[MaxSize];
    int tag;
    int front;
    int rear;
} CQueue;

void InitQueue(CQueue &Q){
    Q.tag = 0;
    Q.front = 0;
    Q.rear = 0;
}

bool EnQueue(CQueue &Q, ElemType x){
    if (Q.tag == 1 && Q.front == Q.rear)
        return false;
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear+1)%MaxSize;
    Q.tag = 1; // 可能满，tag置1
    return true;
}

bool DeQueue(CQueue &Q, ElemType &x){
    if (Q.tag == 0 && Q.front == Q.rear)
        return false;
    x = Q.data[Q.front];
    Q.front = (Q.front+1)%MaxSize;
    Q.tag = 0;  // 可能空，tag置0
    return true;
}

bool IsEmpty(CQueue Q){
    return Q.front == Q.rear && Q.tag == 0;
}

void ShowQueue(CQueue Q){
    if (Q.tag == 1 && Q.front == Q.rear){
        int i = Q.front;
        do{
            printf("%d ", Q.data[i]);
            ++i, i%=MaxSize;
        }while(i != Q.rear);
    }
    printf("\n");
    printf("q.front = %d, q.rear = %d, q.tag = %d\n", Q.front, Q.rear, Q.tag);
}

#endif //C_LINEAR_LIST_CIRCLEQUEUE_H
