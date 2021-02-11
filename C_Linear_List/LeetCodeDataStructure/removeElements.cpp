//
// Created by Rvioleck on 2021/2/9.
//

#include <iostream>

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *removeElements(ListNode *head, int val) {
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        ListNode *cur = head, *pre = dummy;
        while (cur){
            if (cur->val == val){
                pre->next = cur->next;
            } else {
                pre = pre->next;
            }
            cur = cur->next;
        }
        return dummy->next;
    }
};