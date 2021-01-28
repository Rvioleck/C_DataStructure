//
// Created by Rvioleck on 2021/1/23.
//

#ifndef C_LINEAR_LIST_SEQUENCESTACK_H
#define C_LINEAR_LIST_SEQUENCESTACK_H

#include <stdio.h>
#include <cstdlib>
#define MaxSize 50
#define ElemType char

typedef struct{
    ElemType data[MaxSize];
    int top;
}SqStack;

void InitStack(SqStack &S){
    /// ��ʼ��
    S.top = -1;
}

bool IsEmpty(SqStack S){
    /// ��ջ��
    return S.top == -1;
}

bool Push(SqStack &S, ElemType x){
    /// ��ջ
    if (S.top == MaxSize - 1)
        return false;
    S.data[++S.top] = x;
    return true;
}

bool Pop(SqStack &S, ElemType &x){
    /// ��ջ
    if (S.top == -1)
        return false;
    x = S.data[S.top--];
    return true;
}

bool Peek(SqStack S, ElemType &x){
    /// ȡջ��Ԫ��
    if (S.top == -1)
        return false;
    x = S.data[S.top];
    return true;
}

void ShowStack(SqStack &S){
    printf("From the bottom to the top: ");
    for (int i = 0; i <= S.top ; ++i) {
        printf("%c ", S.data[i]);
    }
    printf(",s.top = %d\n", S.top);
}

#endif //C_LINEAR_LIST_SEQUENCESTACK_H
