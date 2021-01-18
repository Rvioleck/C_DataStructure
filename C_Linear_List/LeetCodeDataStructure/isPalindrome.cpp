#include <stdio.h>

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *middleNode(ListNode *head) {
        // 中间结点为中间第一个结点
        ListNode *low = head, *fast = head;
        while (fast->next){
            if (low->next){
                if (fast->next->next)
                    fast = fast->next->next;
                else{
                    fast = fast->next;
                    return low;
                }
                low = low->next;
            }
        }
        return low;
    }

    bool isPalindrome(ListNode *head) {
        ListNode *mid = middleNode(head);
        ListNode *pre = NULL;
        ListNode *cur = mid->next;
        while (cur){
            ListNode *next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        while (pre){
            if(pre->val != head->val){
                return false;
            }else{
                pre = pre->next;
                head = head->next;
            }
        }
        return true;
    }
};