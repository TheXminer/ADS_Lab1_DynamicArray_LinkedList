#include <iostream>

using namespace std;

class ListNode
{
public:
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {}
};

int hasCycle(ListNode* head) {
	if (!head)
		return 0;
	ListNode* fast = head;
	ListNode* slow = head;
	while (fast->next && fast->next->next) {
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)
			return 1;
	}
	return 0;
}

int main()
{
    cout << "Hello World!\n";
}