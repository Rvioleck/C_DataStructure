#include <stdio.h>
#include "SequenceListDynamicAlloc.h"

int main(){
    sqList L;
    InitList(L);
    printf("before\n");
    ShowList(L);
    // IncreaseSize(L, 5);
    // AddMuch(L, 100);
    printf("\nafter\n");
    ShowList(L);
    return 0;
}
