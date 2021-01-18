#include <stdio.h>

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *middleNode(ListNode *head) {
        // 中间结点为中间第二个结点
        ListNode *low = head, *fast = head;
        while (fast->next){
            if (low->next){
                low = low->next;
                if (fast->next){
                    if (fast->next->next)
                        fast = fast->next->next;
                    else
                        fast = fast->next;
                }
            }
        }
        return low;
//        //中间结点为中间第一个结点
//        ListNode *low = head, *fast = head;
//        while (fast->next){
//            if (low->next){
//                if (fast->next->next)
//                    fast = fast->next->next;
//                else{
//                    fast = fast->next;
//                    return low;
//                }
//                low = low->next;
//            }
//        }
//        return low;
    }


};