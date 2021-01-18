#include <stdio.h>
#include <cstdlib>

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode *p = NULL;
        ListNode *res = p;
        int flag = 0;
        while(l1 || l2){
            int v1 = l1?l1->val:0;
            int v2 = l2?l2->val:0;
            if (!res){
                res = p = new ListNode((v1+v2+flag)%10);
            }
            else{
                p->next = new ListNode((v1+v2+flag)%10);
                p = p->next;
            }
            flag = (v1+v2+flag)/10;
            if (l1)
                l1 = l1->next;
            if (l2)
                l2 = l2->next;
        }
        if (flag)
            p->next = new ListNode(flag);
        return res;
    }
};