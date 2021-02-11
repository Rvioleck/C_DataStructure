//
// Created by Rvioleck on 2021/2/6.
//

#include "BinarySearch.h"

int BinarySearch(SeqList L, ElemType key){
    int low = 1, high = L.TableLen, mid;
    while (low <= high){
        mid = (low + high) / 2;
        if (L.elem[mid] == key){
            return mid;
        } else if (L.elem[mid] > key){
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return 0;
}

int BinarySearchRecurse(SeqList L, ElemType key, int low, int high){
    if (low > high)
        return 0;
    int mid = (low + high) / 2;
    if (L.elem[mid] == key){
        return mid;
    } else if (L.elem[mid] > key){
        return BinarySearchRecurse(L, key, low, mid - 1);
    } else {
        return BinarySearchRecurse(L, key, mid + 1, high);
    }
}

int SeqSrch(SeqList &L, ElemType key){
    for (int i = 1; i <= L.TableLen; ++i) {
        if (L.elem[i] == key){
            if (i != 1){
                ElemType temp = L.elem[i];
                L.elem[i] = L.elem[i - 1];
                L.elem[i - 1] = temp;
                return i - 1;
            }
            return 1;
        }
    }
    return 0;
}

int SeqSrch(LinkList &L, ElemType key){
    int i = 0;
    LNode *cur = L->next, *pre = L;
    while (cur){
        i++;
        if (cur->data == key){
            if (pre != L){
                ElemType temp = pre->data;
                pre->data = cur->data;
                cur->data = temp;
                return i - 1;
            }
            return 1;
        }
        cur = cur->next;
        pre = pre->next;
    }
    return 0;
}

int main(){
    SeqList l;
    CreateSeqList(l);
    PrintSeqList(l);
    cout<<SeqSrch(l, '1')<<endl;
    PrintSeqList(l);

    LinkList L;
    TailInsert(L);
    ShowList(L);
    cout<<SeqSrch(L, '1')<<endl;
    ShowList(L);

//    cout<<BinarySearch(l, 'a')<<endl;
//    cout<<BinarySearchRecurse(l, 'a', 1, l.TableLen);
}