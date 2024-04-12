#include <iostream>

using namespace std;

class ListNode
{
public:
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* reverse(ListNode* head) {
    if (!head)
        return nullptr;
    ListNode* pHead = head;
    ListNode* key = head;
    while (pHead->next) {
        key = head;
        head = pHead->next;
        pHead->next = head->next;
        head->next = key;
    }
    return head;
}

int main()
{
    cout << "Hello World!\n";
}