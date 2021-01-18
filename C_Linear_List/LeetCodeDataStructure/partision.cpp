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
    ListNode *partition(ListNode *head, int x) {
        ListNode *large = new ListNode(0);
        ListNode *small = new ListNode(0);
        ListNode *lq = large;
        ListNode *sq = small;
        while (head){
            if(head->val >= x){
                lq->next = head;
                lq = lq->next;
            }else{
                sq->next = head;
                sq = sq->next;
            }
            head = head->next;
        }
        lq->next = NULL;
        sq->next = large->next;
        return small->next;
    }
};

