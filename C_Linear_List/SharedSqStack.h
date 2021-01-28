//
// Created by Rvioleck on 2021/1/23.
//

#ifndef C_LINEAR_LIST_SHAREDSQSTACK_H
#define C_LINEAR_LIST_SHAREDSQSTACK_H
#define MaxSize 10
#define ElemType int

typedef struct{
    ElemType data[MaxSize];
    int top1;
    int top2;
} SharedSqStack;

void InitStack(SharedSqStack &S){
    S.top1 = -1;
    S.top2 = MaxSize;
}

bool Push1(SharedSqStack &S, int x){
    if (S.top2 - S.top1 == 1){
        return false;
    }
    S.data[++S.top1] = x;
    return true;
}

bool Push2(SharedSqStack &S, int x){
    if (S.top2 - S.top1 == 1){
        return false;
    }
    S.data[--S.top2] = x;
    return true;
}

bool Pop1(SharedSqStack &S, int &x){
    if (S.top1 == -1){
        return false;
    }
    x = S.data[S.top1--];
    return true;
}

bool Pop2(SharedSqStack &S, int &x){
    if (S.top2 == MaxSize){
        return false;
    }
    x = S.data[S.top2++];
    return true;
}


#endif //C_LINEAR_LIST_SHAREDSQSTACK_H
