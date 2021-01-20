#include "LinkListWithoutHead.h"

void deleteValueOfX_p37q1(LinkList &L, int x){
    if (!L){
        return;
    }
    LNode *cur = L->next, *pre = L, *s;
    if (pre->data == x){
        s = pre;
        L = cur;
        cur = cur->next;
        pre = pre->next;
        free(s);
    }
    while (cur){
        if (cur->data == x){
            s = cur;
            pre->next = cur->next;
        }else{
            pre = pre->next;
        }
        cur = cur->next;
        free(s);
    }
}



int main(){
    LinkList L;
    InitList(L);
    ListInsert(L, 1, 1);
    ListInsert(L, 2, 2);
    ListInsert(L, 3, 3);
    ListInsert(L, 4, 4);
    ListInsert(L, 5, 5);
    ListInsert(L, 6, 6);
    ShowList(L);

    /// deleteValueOfX 调试
//    deleteValueOfX_p37q1(L, 1);
//    ShowList(L);
}


