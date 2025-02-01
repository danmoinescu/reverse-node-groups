#include "reverse-group-nodes.hpp"
#include <algorithm>
#ifdef DEBUG
#include <iostream>
#endif


ListNode* Solution::reverse2(ListNode *n1, ListNode *n2)
{
    /* Make n2->next = n1, return the previous n2->next.
       Precondition: neither n1 nor n2 are null.
    */
    ListNode *n3 = n2->next;
    n2->next = n1;
#ifdef DEBUG
    std::cout << " " << n2->val << " -> " << n1->val
        << "; next: " << (n3==nullptr? -1 : n3->val) << "\n";
#endif
    return n3;
}


ListNode* Solution::reverseNextK(ListNode *anchor, int k)
{
    /* For instance, if k==4, transform the node sequence:
           H -> 1 -> 2 -> 3 -> 4 -> T
       into:
                /---------------->-\
           H    1 <- 2 <- 3 <- 4    T
           \->----------------/
    */
    if(anchor == nullptr || anchor->next == nullptr)
    {
        return nullptr;
    }
    ListNode *first = anchor->next, *current = first;
    ListNode *next = current->next, *tail;
    int remaining;
    for(remaining=k-1; remaining>0; --remaining) // k-1 "swaps"
    {
        if(next == nullptr) { break; }
        tail = reverse2(current, next);
        current = next;
        next = tail;
    }
    if(remaining>0) // not enough nodes: undo
    {
        next = current->next;
        current->next = nullptr;
        while(current != first)
        {
            tail = reverse2(current, next);
            current = next;
            next = tail;
        }
        first = nullptr;
    }
    else
    {
        anchor->next = current;
        first->next = tail;
    }
#ifdef DEBUG
    std::cout << "After reverseNextK: [ ";
    int i = 1;
    for(current = anchor->next; (i<=k) && (current != nullptr); ++i, current = current->next)
    {
        std::cout << current->val << " ";
    }
    std::cout << "]; next: ";
    if(tail != nullptr)
    {
        std::cout << tail->val << "\n";
    }
    else
    {
        std::cout << "null\n";
    }
#endif

    return first;
}


ListNode* Solution::reverseKGroup(ListNode* head, int k)
{
    if(k == 1) { return head; }

    ListNode anchor, *batch_anchor = &anchor;
    anchor.next = head;
    while(batch_anchor != nullptr)
    {
        batch_anchor = reverseNextK(batch_anchor, k);
    }
    return anchor.next;
}
