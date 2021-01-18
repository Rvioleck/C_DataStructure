#include <stdio.h>
#include <cstdlib>

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *reverseList(ListNode *head) {
        ListNode *cur = NULL, *pre = head;
        while(pre != NULL){
            ListNode* nextNode = pre->next;
            pre->next = cur;
            cur = pre;
            pre = nextNode;
        }
        return cur;
    }
};