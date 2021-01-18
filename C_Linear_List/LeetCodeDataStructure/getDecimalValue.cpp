#include <stdio.h>

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    int getDecimalValue(ListNode *head) {
        int res = 0;
        while (head){
            res <<= 1;
            res += head->val;
        }
        return res;
    }
};
