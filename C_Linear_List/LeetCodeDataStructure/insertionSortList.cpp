#include <stdio.h>

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *insertionSortList(ListNode *head) {
        if (head == NULL)
            return NULL;
        ListNode *cur = head->next;
        ListNode *finish = head;
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        while (cur){
            if (cur->val >= finish->val){
                finish->next = cur;
                finish = finish->next;
                cur = cur->next;
            }else{
                ListNode *pre = dummy;
                while (cur->val > pre->next->val){
                    pre = pre->next;
                }
                ListNode *curNext = cur->next;
                cur->next = pre->next;
                pre->next = cur;
                cur = curNext;
            }
        }
        finish->next = NULL;
        return dummy->next;
    }
};