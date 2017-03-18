struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr && l2 == nullptr) return nullptr;
        int carry = 0;
        ListNode* res;
        ListNode** next = &res;
        while (l1 && l2) {
            int cur = l1->val + l2->val + carry;
            *next = new ListNode(cur % 10);
            next = &((*next)->next);
            carry = cur / 10;
            l1 = l1->next;
            l2 = l2->next;
        }
        while (l1) {
            int cur = l1->val + carry;
            *next = new ListNode(cur % 10);
            next = &((*next)->next);
            carry = cur / 10;
            l1 = l1->next;
        }
        while (l2) {
            int cur = l2->val + carry;
            *next = new ListNode(cur % 10);
            next = &((*next)->next);
            carry = cur / 10;
            l2 = l2->next;
        }
        if (carry) {
            *next = new ListNode(carry);
        }
        return res;
    }
};

int main() {
    return 0;
}
