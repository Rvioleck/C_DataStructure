#include <stdio.h>

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *mergeInBetween(ListNode *list1, int a, int b, ListNode *list2) {
        ListNode *p1 = list1, *p2 = list2;
        int sub = b - a + 1;
        while (--a){
            p1 = p1->next;
        }
        ListNode *q = p1->next;  // 保留list1的a+1个结点
        while (--sub){
            q = q->next;
        }
        p1->next = list2;
        while (p2->next){
            p2 = p2->next;
        }
        p2->next = q->next;
        return list1;
    }
};