#pragma once
#include <vector>


struct ListNode {
    const int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *other, bool insert_after_other=false): val(x)
    {
        if(insert_after_other)
        {
            next = other->next;
            other->next = this;
        }
        else // insert before "other"
        {
            next = other;
        }
    }
};


class Solution {
    public:
        ListNode* reverseKGroup(ListNode* head, int k);

    protected:
        ListNode* reverse2(ListNode *n1, ListNode *n2);
        ListNode* reverseNextK(ListNode *anchor, int k);
};
