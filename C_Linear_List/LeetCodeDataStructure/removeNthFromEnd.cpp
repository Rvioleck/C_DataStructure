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
    ListNode *removeNthFromEnd(ListNode *head, int n){
        ListNode *fast=head, *slow=head;
        while (--n){
            fast = fast->next;
        }
        if (fast == NULL)
            return head->next;
        while (fast->next != NULL){
            fast = fast->next;
            slow = slow->next;
        }
        slow->next = slow->next->next;
        return head;
    }
//    ListNode *removeNthFromEnd(ListNode *head, int n) {
//        ListNode* p = head;
//        int len = 0;
//        while (p!=NULL){
//            len++;
//            p = p->next;
//        }
//        p = head;
//        len = len - n;
//        if (len == 0){
//            return head->next;
//        }
//        if (p->next == NULL)
//            return NULL;
//        while (--len){
//            p = p->next;
//        }
//        p->next = p->next->next;
//        return head;
//    }
};
