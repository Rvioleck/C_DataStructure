//
// Created by Rvioleck on 2021/1/23.
//

#include "LinkStack.h"

int main(){
    LinkStack s;
    InitStack(s);
    int x;
    Push(s, 1);
    Pop(s, x);
    Push(s, 2);

    ShowStack(s);
    printf("%d", IsEmpty(s));
}