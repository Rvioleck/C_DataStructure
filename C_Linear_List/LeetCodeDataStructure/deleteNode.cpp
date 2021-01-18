#include <stdio.h>

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        ListNode *dummy = new ListNode(0);
        ListNode *p = dummy;
        p->next = head;
        while (p->next->val != val){
            p = p->next;
        }
        p->next = p->next->next;
        return dummy->next;
    }

    void deleteNode(ListNode *node) {
        if (!node->next){
            node = NULL;
        }else{
            int temp = node->val;
            node->val = node->next->val;
            node->next->val = temp;
            node->next = node->next->next;
        }
    }
};