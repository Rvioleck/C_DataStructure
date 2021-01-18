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
    void switchValue(ListNode *a, ListNode *b){
        int temp = b->val;
        b->val = a->val;
        a->val = temp;
    }

    ListNode *swapNodes(ListNode *head, int k) {
        ListNode *lk = head, *rk =head;
    }
};