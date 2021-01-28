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
    Push(s, 4);
    Push(s, 3);
    Push(s, 6);
    Push(s, 7);
    ShowStack(s);
}