//
// Created by Rvioleck on 2021/2/8.
//


#include <cstdlib>

struct ListNode {
    int val;
    struct ListNode *next;
};


struct ListNode* removeDuplicateNodes(struct ListNode* head){
    ListNode *p = head;
    while(p){
        if (p->next){
            ListNode *cur = p->next;
            ListNode *pre = p;
            while (cur){
                if (cur->val == p->val){
                    pre->next = cur->next;
                    free(cur);
                    cur = pre->next;
                } else {
                    pre = pre->next;
                    cur = cur->next;
                }
            }
        }
        p = p->next;
    }
    return head;
}