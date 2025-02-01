#include "reverse-group-nodes.hpp"
#include <cstdlib>
#include <iostream>
#include <ranges>
#include <span>


template<typename T>
std::ostream& operator<<(std::ostream &out, const std::span<T> s)
{
    out << "[ ";
    std::copy(s.begin(), s.end(), std::ostream_iterator<int>(out, ", "));
    out << "]";
    return out;
}


static void print(
        std::ostream &out,
        const std::vector<int> &v,
        int k,
        const char *msg = nullptr)
{
    if(msg != nullptr) { out << msg; }
    int remaining = (int)v.size();
    auto it = v.cbegin();
    for(; remaining >= k; it += k, remaining -= k)
    {
        auto view = std::span(it, k);
        out << view << " ";
    }
    if(remaining > 0)
    {
        auto view = std::span(it, remaining);
        out << view << " ";
    }
}


static void print(
        std::ostream &out,
        const ListNode *head,
        int k,
        const char *msg = nullptr)
{
    if(msg != nullptr) { out << msg; }
    std::vector<int> batch;
    batch.reserve(k);
    for(int batch_size=0; head != nullptr; head = head->next)
    {
        batch.push_back(head->val);
        if(++batch_size == k)
        {
            out << std::span(batch) << " ";
            batch.clear();
            batch_size = 0;
        }
    }
    if(!batch.empty()) { out << std::span(batch) << " "; }
}


static ListNode* make_list(int size)
{
    ListNode anchor, *tail = &anchor;
    for(int i=1; i<=size; ++i)
    {
        tail = new ListNode(i, tail, true);

    }
    return anchor.next;
}


static std::vector<int> make_k_reversed(int size, int k)
{
    std::vector<int> retval;
    retval.reserve(size);
    int batch_start = 1;
    while(true)
    {
        int batch_end = batch_start + k - 1;
        if(batch_end > size) { break; }
        for(int val = batch_end; val >= batch_start; --val)
        {
            retval.push_back(val);
        }
        batch_start += k;
    }
    for(int val = batch_start; val <= size; ++val)
    {
        retval.push_back(val);
    }
    return retval;
}


static bool are_equal(
        const ListNode *head,
        const std::vector<int> &k_reversed)
{
    auto it = k_reversed.cbegin();
    auto cend = k_reversed.cend();
    for(; head != nullptr && it != cend; head=head->next, it++)
    {
        if(head->val != *it)
        {
            std::cerr << "At index " << (it-k_reversed.cbegin())
                << ": expected " << *it
                << " but got " << head->val << "\n";
            return false;
        }
    }
    if(head != nullptr || it != cend)
    {
        std::cerr << "Size mismatch\n";
        return false;
    }
    return true;
}


int main(int argc, const char *argv[])
{

    if(argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " k list_size\n";
        return 1;
    }
    int k = strtol(argv[1], nullptr, 10);
    int size = strtol(argv[2], nullptr, 10);
    ListNode *head = make_list(size);

    std::vector<int> k_reversed = make_k_reversed(size, k);

    Solution sol;
    ListNode *reversed_list = sol.reverseKGroup(head, k);

    if(! are_equal(reversed_list, k_reversed))
    {
        print(std::cerr, k_reversed, k, "Expected: ");
        std::cerr << "\n";
        print(std::cerr, reversed_list, k, "Actual: ");
        std::cerr << "\n";
        return 2;
    }
    print(std::cout, reversed_list, k);
    std::cout << '\n';
    return 0;
}
