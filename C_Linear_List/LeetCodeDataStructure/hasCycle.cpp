#include <stdio.h>

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        while (fast->next){
            if (fast->next->next){
                slow = slow->next;
                fast = fast->next;
            }else
                fast = fast->next;
            if (fast == slow)
                return true;
        }
        return false;
    }
};