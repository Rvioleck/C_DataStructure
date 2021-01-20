#include "LinkListWithHead.h"

LinkList deleteValueOfX_p38q2(LinkList &L, int x){
    if (!L->next){
        return L;
    }
    LNode *cur = L->next, *pre = L, *s;
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
    return L;
}

void reverseShowList_p38q3(LinkList L){
    /// 利用递归栈来逆置打印 T(n) = O(n), S(n) = O(n);
    if (L->next){
        reverseShowList_p38q3(L->next);
    }
    if (L) printf("%d->", L->data);

    /// 前插法建立新的倒序链表，后输出 T(n) = O(n), S(n) = O(n);
//    if (!L->next){
//        return;
//    }
//    LinkList rL;
//    InitList(rL);
//    LNode *cur = L->next;
//    while (cur){
//        LNode *s = (LNode*)malloc(sizeof(LNode));
//        s->data = cur->data;
//        s->next = rL->next;
//        rL->next = s;
//        cur = cur->next;
//    }
//    ShowList(rL);
}

LinkList deleteTheMinElem_p38q4(LinkList &L){
    if (!L->next)
        return L;
    LNode *cur = L->next, *pre = L;
    LNode *min = cur, *minPre;
    while (cur){
        if (cur->data < min->data){
            min = cur;
            minPre = pre;
            min->data = cur->data;
        }
        cur = cur->next;
        pre = pre->next;
    }
    minPre->next = min->next;
    free(min);
    return L;
}

LinkList reverseLinkList_p38q5(LinkList &L){
    // 对带头结点的单链表就地逆置;
    if (!L->next){
        return L;
    }
    LNode *pre = L, *cur = L->next;
    while (cur){
        LNode *next = cur->next;
        if (pre == L){
            cur->next = NULL;
        }else{
            cur->next = pre;
        }
        pre = cur;
        cur = next;
    }
    L->next = pre;
    return L;
}

LinkList ascendingByValue_p38q6(LinkList &L){
    // 插入排序对链表进行时间复杂度为0(n^2)的升序，最好的情况下为O(n)，空间复杂度为O(1)
    if (!L->next || !L->next->next)
        return L;
    LNode *cur = L->next->next, *done = L->next;
    while (cur){
        LNode *next = cur->next;
        /*
         * 此处的if-else将新插入结点分为两类
         * 也可以不区分新结点的大小，都从完成链初始开始遍历，
         * 这样的话代码更简洁，但是语句频度会稍微提高，执行效率降低，
         * 但时间复杂度仍为O(n^2)，最好的情况下页为0(n^2)
        */
        if (cur->data <= done->data){ // 小于完成链的最大值的需要遍历完成链，找到合适位置
            LNode *pre = L;
            while (pre->next->data <= cur->data){
                pre = pre->next;
            }
            cur->next = pre->next;
            pre->next = cur;
            cur = next;
            done->next = cur;
        }else{ // 大于完成链的最大值的直接跟在完成链后面
            done = cur;
            cur = next;
        }
    }
    return L;
}

LinkList deleteAllElemOfTheValueBetweenSAndT_p39q7(LinkList &L, int s, int t){
    // 删除所有值x满足s<x<t之间的元素，时间复杂度O(n)，空间复杂度O(1);
    if (!L->next)
        return L;
    LNode *cur = L->next, *pre = L;
    while (cur){
        if (cur->data > s && cur->data < t){
            pre->next = cur->next;
            free(cur);
            cur = pre->next;
        }else{
            cur = cur->next;
            pre = pre->next;
        }
    }
    return L;
}

LinkList getIntersectionNode_p39q8(LinkList L1, LinkList L2){
    // 时间复杂度O(m+n)，空间复杂度O(1)
    LNode *a = L1, *b = L2;
    while (a != b){
        a = a ? a->next : L2;
        b = b ? b->next : L1;
    }
    return a;
}

void showAscendingLinkList_p39q9(LinkList &head){
    // 插入排序
    if (!head->next)
        return;
    LNode *cur = head->next->next, *done = head->next;
    while (cur){
        LNode *next = cur->next;
        if (cur->data >= done->data){
            done = cur;
            cur = next;
        }else{
            LNode *pre = head;
            while (pre->next->data <= cur->data){
                pre = pre->next;
            }
            cur->next = pre->next;
            pre->next = cur;
            cur = next;
            done->next = cur;
        }
    }
    // 打印并且释放空间
    while (head->next){
        LNode *next = head->next;
        free(head);
        head = next;
        printf("%d->", head->data);
    }
    printf("NULL\n");
}

void

int main() {
    LinkList L;
    InitList(L);
    ListInsert(L, 1, 1);
    ListInsert(L, 2, 8);
    ListInsert(L, 3, 3);
    ListInsert(L, 4, 1);
    ListInsert(L, 5, 0);
    ListInsert(L, 6, 5);
    ShowList(L);



    /// showAscendingLinkList 调试
//    showAscendingLinkList_p39q9(L);
//    ShowList(L);

    /// getIntersectionNode 调试
//    LinkList L2;
//    InitList(L2);
//    L2->next = L->next->next;
//    ShowList(L2);
//
//    LinkList intersection;
//    InitList(intersection);
//    intersection = getIntersectionNode_p39q8(L, L2);
//    ShowList(intersection);


    /// deleteAllElemOfTheValueBetweenSAndT 调试
//    deleteAllElemOfTheValueBetweenSAndT_p39q7(L, 2, 5);
//    ShowList(L);

    /// ascendingByValue 调试
//    ascendingByValue_p38q6(L);
//    ShowList(L);

    /// reverseLinkList 调试
//    reverseLinkList_p38q5(L);
//    ShowList(L);

    /// deleteTheMinElem 调试
//    deleteTheMinElem_p38q4(L);
//    ShowList(L);

    /// reverseShowList 调试
//    if (L){
//        reverseShowList_p38q3(L->next);
//        printf("NULL\n");
//    }

    /// deleteValueOfX 调试
//    deleteValueOfX_p38q2(L, 1);
//    ShowList(L);
}

