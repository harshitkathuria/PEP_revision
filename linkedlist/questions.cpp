#include<iostream>
#include<vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

//leetcode  876
ListNode* middleNode(ListNode* head) {

    ListNode* slow = head;
    ListNode* fast = head;

    while(fast != nullptr && fast->next != nullptr && fast->next->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;
    }        

    return slow;
}

//leetcode 206
ListNode* reverseList(ListNode* head) {

    ListNode* prev = nullptr;
    ListNode* curr = head;
    ListNode* forw = head;        

    while(forw != nullptr){
        forw = curr->next;
        curr->next = prev;

        prev = curr;
        curr = forw;
    }
    return prev;
}

bool isPalindrome(ListNode* head) {

    if(head == nullptr || head->next == nullptr){
        return true;
    }
    
    ListNode* mid = middleNode(head);
    ListNode* first = head;
    ListNode* sec = reverseList(mid);

    while(sec != nullptr && first != nullptr){
        if(first->val != sec->val){
            return false;
        }

        first = first->next;
        sec = sec->next;
    }        
    return true;
}

bool hasCycle(ListNode *head) {

    if(head == nullptr || head->next == nullptr || head->next->next == nullptr){
        return false;
    }


    ListNode* slow = head;
    ListNode* fast = head;

    while(fast != nullptr && fast->next != nullptr && fast->next->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;

        if(slow == fast){
            break;
        }
    }      

    return slow == fast;
}

ListNode *detectCycle(ListNode *head) {
    if(head == nullptr || head->next == nullptr || head->next->next == nullptr){
        return nullptr;
    }

    ListNode* slow = head;
    ListNode* fast = head;

    while(fast != nullptr && fast->next != nullptr && fast->next->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;

        if(slow == fast)
            break;
    }
    
    if(slow != fast){
        return nullptr;
    }
    
    slow = head;
    while(slow != fast){
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {

    if(headA == nullptr || headB == nullptr){
        return nullptr;
    }        

    ListNode* curr = headA;

    while (curr->next != nullptr){
        curr = curr->next;
    }
    
    curr->next = headB; //creating cycle
    ListNode* ans = detectCycle(headA);
    curr->next = nullptr;
    
    return ans;
}

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {

    if(l1 == nullptr || l2 == nullptr){
        return l1 == nullptr? l2 : l1;
    }        

    ListNode* head = new ListNode(-1);  //dummy;
    ListNode* curr = head;

    while(l1 != nullptr && l2 != nullptr){
        if(l1->val <= l2->val){
            curr->next = l1;
            l1 = l1->next;
        }
        else{
            curr->next = l2;
            l2 = l2->next;
        }
        curr = curr->next;
    }

    if(l1 != nullptr){
        curr->next = l1;
    }
    if(l2 != nullptr){
        curr->next = l2;
    }

    return head->next;
}

ListNode* sortList(ListNode* head) {

    if(head == nullptr || head->next == nullptr){
        return head;
    }

    ListNode* mid = middleNode(head);
    ListNode* nhead = mid->next;
    mid->next = nullptr;

    ListNode* a = sortList(head);
    ListNode* b = sortList(nhead);

    return mergeTwoLists(head, nhead);
}

// ListNode* mergeKLists(vector<ListNode*>& lists) {

//     ListNode* a = lists[0];

//     for(int i = 0; i < lists.size() - 1; i++){
//         mergeTwoLists(a, lists[i + 1]);
//     }

//     return a;
// }

ListNode* mergeKLists_(vector<ListNode*>& lists, int si, int ei){
    if(si == ei){   //ek list
        return lists[si];
    }

    if(si + 1 == ei){   //merge two list
        return mergeTwoLists(lists[si], lists[ei]);
    }

    int mid = (si + ei) / 2;

    ListNode* a = mergeKLists_(lists, si, mid);     //si se mid tak ki list is sorted now
    ListNode* b = mergeKLists_(lists, mid + 1, ei);     //mid + 1 se ei tak ki list is sorted now

    return mergeTwoLists(a, b);
}

ListNode* mergeKLists(vector<ListNode*>& lists) {

    if(lists.size() == 0){
        return nullptr;
    }        

    return mergeKLists_(lists, 0, lists.size() - 1); 
}

void reorderList(ListNode* head) {

    ListNode* mid = middleNode(head);
    ListNode* b = mid->next;

    b = reverseList(b);

    ListNode* l1 = head;
    ListNode* l2 = b;

    ListNode* curr = l1;
    ListNode* temp1;
    ListNode* temp2;
    while(l1 != nullptr && l2 != nullptr){

        temp1 = curr->next;
        curr->next = l2;
        temp2 = l2->next;
        l2->next = temp1;
        curr = temp1;
        l2 = temp2;
    }

    if(l1 != nullptr){
        curr->next = l1;
    }
    if(l2 != nullptr){
        curr->next = l2;
    }
}