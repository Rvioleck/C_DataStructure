#include "LinkListWithHead.h"
#include "SequenceListStaticAlloc.h"

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
//    if (L->next){
//        reverseShowList_p38q3(L->next);
//    }
//    if (L) printf("%d->", L->data);

    /// 前插法建立新的倒序链表，后输出 T(n) = O(n), S(n) = O(n);
    if (!L->next){
        return;
    }
    LinkList rL;
    InitList(rL);
    LNode *cur = L->next;
    while (cur){
        LNode *s = (LNode*)malloc(sizeof(LNode));
        s->data = cur->data;
        s->next = rL->next;
        rL->next = s;
        cur = cur->next;
    }
    ShowList(rL);
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

void separateOddAndEvenIndex_p39q10(LinkList L, LinkList &even, LinkList &odd){
    if (!L->next)
        return;
    int flag = 1;
    LNode *odd0 = odd, *even0 = even;
    while (L->next){
        L = L->next;
        if (flag){
            odd0->next = L;
            odd0 = odd0->next;
            flag = 0;
        }else{
            even0->next = L;
            even0 = even0->next;
            flag = 1;
        }
    }
    if (flag){
        odd0->next = NULL;
    }else{
        even0->next = NULL;
    }
}

LinkList separateOddAndEvenIndex_p39q11(LinkList &A){
    if (!A->next)
        return NULL;
    int flag = 1;
    LinkList B;
    InitList(B);
    LNode *a = A, *b = B; // 作为A和B的头结点
    LNode *cur = A->next;
    while (cur){
        if (flag){
            flag = 0;
            a->next = cur;
            a = a->next;
            cur = cur->next;
        }else{
            flag = 1;
            b->next = cur;
            b = b->next;
            cur = cur->next;
        }
    }
    a->next = NULL;
    b->next = NULL;
    return B;
}

LinkList deleteRepeatedElem_p39q12(LinkList &L){
    if (!L->next || !L->next->next)
        return L;
    LNode *cur = L->next;
    while (cur->next){
        LNode *q = cur->next;
        if (q->data == cur->data){
            cur->next = q->next;
            free(q);
        }else{
            cur = cur->next;
        }
    }
    return L;
}

LinkList mergeIntoDescending_p39q13(LinkList L1, LinkList L2){
    LNode *a = L1->next, *b = L2->next;
    L1->next = NULL;
    while (a && b){
        if (a->data <= b->data){
            LNode *next = a->next;
            a->next = L1->next;
            L1->next = a;
            a = next;
        }
        else{
            LNode *next = b->next;
            b->next = L1->next;
            L1->next = b;
            b = next;
        }
    }
    if (b)
        a = b;
    while (a){
        LNode *next = a->next;
        a->next = L1->next;
        L1->next = a;
        a = next;
    }
    free(a);
    return L1;
}

LinkList getCommonElem_p39q14(LinkList L1, LinkList L2){
    LinkList L;
    InitList(L);
    LNode *a = L1->next, *b = L2->next, *cur = L;
    while (a && b){
        if (a->data < b->data){
            a = a->next;
        }else if (a->data > b->data){
            b = b->next;
        }else{
            cur->next = a;
            cur = cur->next;
            a = a->next;
            b = b->next;
        }
    }
    cur->next = NULL;
    return L;
}

LinkList getCommonElem_p39q15(SeqList L1, SeqList L2){
    LinkList L;
    InitList(L);
    LNode *cur = L;
    int i = 0, j = 0;
    while (i < L1.length && j < L2.length){
        if (L1.data[i] < L2.data[j]){
            i++;
        }else if (L1.data[i] > L2.data[j]){
            j++;
        }else{
            LNode *s = (LNode*)malloc(sizeof(LNode));
            s->data = L1.data[i];
            cur->next = s;
            cur = cur->next;
            i++;
            j++;
        }
    }
    cur->next = NULL;
    return L;
}

bool isSubLinkList_q39q16(LinkList L1, LinkList L2){
    if (!L2->next)
        return false;
    LNode *a = L1->next, *b = L2->next;
    LNode *cur1 = L1->next, *cur2 = L2->next;
    while(a){
        if (a->data == b->data){
            cur1 = a, cur2 = b;
            while (cur1 && cur2 && cur1->data == cur2->data){
                cur1 = cur1->next;
                cur2 = cur2->next;
            }
            if (!cur2){ // 子串正常遍历到NULL，则为子串
                return true;
            }
        }else{
            a = a->next;
        }
    }
    return false;
}

LinkList connectCLinkList_p39q18(LinkList L1, LinkList L2){
    LinkList L = L1;
    LNode *cur1 = L1, *cur2 = L2;
    while (cur1->next != L1){
        cur1 = cur1->next;
    }
    cur1->next = L2->next;
    while (cur2->next != L2){
        cur2 = cur2->next;
    }
    cur2->next = L1;
    return L;
}

void printAndFreeCLinkList_p39q19(LinkList &L){
    if (L->next == L)
        return;
    LNode *min, *pre, *cur, *curPre;
    while (L->next != L){
        cur = L->next, curPre = L;
        min = cur, pre = curPre;
        while (cur != L){
            if (cur->data < min->data){
                min = cur;
                pre = curPre;
            }
            curPre = curPre->next;
            cur = cur->next;
        }
        printf("%d->", min->data);
        pre->next = pre->next->next;
        free(min);
    }
    printf("NULL\n");
    free(L);
}

int findLastKthElem_p39q21(LinkList list, int k){
    /**
     * 1)算法基本设计思想:使用快慢指针，快指针和慢指针的差值为k，两者同时向后遍历，当快指针指向表尾NULL时，慢指针指向的是倒数第k个元素
     * 2)算法详细实现步骤:将慢指针初始化指向表头结点，快指针初始化遍历k次指向第k个结点，若快指针初始化过程中变为NULL，则k值不合要求，返回0
     *   同时向后进行遍历，当快指针为NULL时，打印慢指针的值并返回1
     */
    LNode *slow = list, *fast = list; // 初始化慢指针
    while (k--){ // 初始化快指针
        if (fast){
            fast = fast->next;
        }
    }
    if (fast == NULL) // 如果快指针为NULL，则k值不合理，返回0
        return 0;
    while (fast != NULL){ // 快慢指针同时向后遍历，直到快指针为NULL
        fast = fast->next;
        slow = slow->next;
    }
    printf("%d\n", slow->data); // 此时输出慢指针的值为倒数第k个值
    return 1;
}

void delAllAbsParityElem_p39q23(LinkList &L, int n){
    if (!L->next)
        return;
    int *p = (int*)malloc(sizeof(int) * (n+1));
    for (int i = 0; i < n + 1; ++i) {
        p[i] = 0;
    }
    LNode *cur = L, *r;
    while (cur->next){
        int m = abs(cur->next->data);
        if (p[m] == 0){
            p[m] = 1;
            cur = cur->next;
        }else{
            r = cur->next;
            cur->next = r->next;
            free(r);
        }
    }
    free(p);
}

LinkList returnLoop_p39q24(LinkList L){
    if (!L->next){
        return NULL;
    }
    LNode *slow = L, *fast = L;
    while (slow != NULL || fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast){
            break;
        }
    }
    if (slow == NULL || fast->next == NULL)
        return NULL;
    LNode *p1 = L, *p2 = slow;
    while (p1 != p2){
        p1 = p1->next;
        p2 = p2->next;
    }
    return p1;
}

LinkList p39q25(LinkList L){
    LNode *slow = L, *fast = L;
    while (fast){
        if (fast->next){
            fast = fast->next->next;
        }else{
            fast = fast->next;
        }
        slow = slow->next; // 获取中点slow
    }
    LNode *mid = slow, *nex = slow->next;
    while (nex){
        LNode *nnex = nex->next;
        nex->next = slow;
        slow = nex;
        nex = nnex;
    }
    mid->next = NULL;
    int flag = 1;
    LNode *left = L->next, *right = slow, *cur = L;
    while (left && right){
        if (flag){
            cur->next = left;
            cur = cur->next;
            left = left->next;
            flag = 0;
        }else{
            cur->next = right;
            cur = cur->next;
            right = right->next;
            flag = 1;
        }
    }
    return L;
}

int main() {
    LinkList L;
    InitList(L);
    ListInsert(L, 1, 1);
    ListInsert(L, 2, 2);
    ListInsert(L, 3, 3);
    ListInsert(L, 4, 4);
    ListInsert(L, 5, 5);
    ListInsert(L, 6, 6);
    ListInsert(L, 7, 7);
    ListInsert(L, 8, 8);
    ListInsert(L, 9, 9);
    ListInsert(L, 10, 10);
    ListInsert(L, 11, 11);
    ShowList(L);
    L = p39q25(L);
    ShowList(L);

    /// delAllAbsParityElem 调试
//    delAllAbsParityElem_p39q23(L, 21);
//    ShowList(L);

    /// findLastKthElem 调试
//    printf("%d", findLastKthElem_p39q21(L, 1));

    /// printAndFreeCLinkList 调试
//    L = toCircleLinkList(L);
//    printAndFreeCLinkList_p39q19(L);

    /// connectCLinkList 调试
//    L = toCircleLinkList(L);
//    LinkList L2;
//    InitList(L2);
//    ListInsert(L2, 1, 1);
//    ListInsert(L2, 2, 3);
//    ListInsert(L2, 3, 4);
//    ListInsert(L2, 4, 5);
//    ListInsert(L2, 5, 7);
//    ListInsert(L2, 6, 8);
//    ShowList(L2);
//    L2 = toCircleLinkList(L2);
//    LinkList L3 = connectCLinkList_p39q18(L, L2);
//    ShowCList(L3);


    /// isSubLinkList 调试
//    LinkList L2;
//    InitList(L2);
//    ListInsert(L2, 1, 1);
//    ListInsert(L2, 2, 3);
//    ListInsert(L2, 3, 4);
//    ListInsert(L2, 4, 5);
//    ListInsert(L2, 5, 7);
//    ShowList(L2);
//
//    printf("%d",isSubLinkList_q39q16(L, L2));

    /// getCommonElem 数组 调试
//    SeqList L1;
//    InitList(L1);
//    ListInsert(L1, 1, 1);
//    ListInsert(L1, 2, 3);
//    ListInsert(L1, 3, 4);
//    ListInsert(L1, 4, 7);
//    ListInsert(L1, 5, 9);
//    ListInsert(L1, 6, 10);
//    ShowList(L1);
//
//    SeqList L2;
//    InitList(L2);
//    ListInsert(L2, 1, 1);
//    ListInsert(L2, 2, 2);
//    ListInsert(L2, 3, 4);
//    ListInsert(L2, 4, 6);
//    ListInsert(L2, 5, 7);
//    ListInsert(L2, 6, 10);
//    ShowList(L2);
//
//    LinkList L3 = getCommonElem_p39q15(L1, L2);
//    ShowList(L3);

    /// getCommonElem 调试
//    LinkList  L2;
//    InitList(L2);
//    ListInsert(L2, 1, 1);
//    ListInsert(L2, 2, 4);
//    ListInsert(L2, 3, 6);
//    ListInsert(L2, 4, 8);
//    ListInsert(L2, 5, 9);
//    ListInsert(L2, 6, 10);
//    ShowList(L2);
//
//    LinkList L3 = getCommonElem_p39q14(L, L2);
//    ShowList(L3);

    /// mergeIntoDescending 调试
//    LinkList L2;
//    InitList(L2);
//    ListInsert(L2, 1, 2);
//    ListInsert(L2, 2, 6);
//    ListInsert(L2, 3, 9);
//    ListInsert(L2, 4, 10);
//    ListInsert(L2, 5, 11);
//    ListInsert(L2, 6, 12);
//    ShowList(L2);
//    L = mergeIntoDescending_p39q13(L, L2);
//    ShowList(L);

    /// deleteRepeatedElem 调试
//    deleteRepeatedElem_p39q12(L);
//    ShowList(L);

    /// separateOddAndEvenIndex(LinkList &A) 单参数 调试
//    LinkList L2 = separateOddAndEvenIndex_p39q11(L);
//    ShowList(L);
//    ShowList(L2);

    /// separateOddAndEvenIndex 调试
//    LinkList even, odd;
//    InitList(even);
//    InitList(odd);
//    separateOddAndEvenIndex_p39q10(L, even, odd);
//    ShowList(even);
//    ShowList(odd);

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

