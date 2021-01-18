#include <stdio.h>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    int kthToLast(ListNode* head, int k) {
        ListNode *slow = head, *fast = head;
        while (--k){
            fast = fast->next;
        }
        while (fast->next){
            fast = fast->next;
            slow = slow->next;
        }
        return slow->val;
    }
};