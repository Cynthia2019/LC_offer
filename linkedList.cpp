/*
链表题大多数都要用到dummyHead（可以不用特殊处理head）
双指针最大的用处就是把遍历两遍的任务通过遍历一遍完成。
*/

/* 
203. 移除链表元素
给你一个链表的头节点 head 和一个整数 val ，请你删除链表中所有满足 Node.val == val 的节点，并返回 新的头节点 。
*/

struct ListNode {
    int val; 
    ListNode* next; 
    ListNode(int x): val(x), next(nullptr) {}
    ListNode(int x, ListNode* next): val(x), next(next) {}
};

ListNode* removeElements(ListNode* head, int val){ 
    ListNode* dummyHead = new ListNode(0, head); 
    ListNode* curr = dummyHead; 
    while(curr->next){
        if(curr->next->val == val){
            ListNode* temp = curr->next; 
            curr->next = curr->next->next;
            delete temp; 
        }
        else {
            curr = curr->next;
        }
    }
    head = dummyHead; 
    delete dummyHead; 
    return head;
}

/*
206. 反转链表
给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。
*/
ListNode* reverseList(ListNode* head){
    ListNode* prev = nullptr; 
    ListNode* curr = head; 
    while (curr){
        ListNode* next = curr->next;
        curr->next = prev; 
        prev = curr; 
        curr = next;
    }
    return prev;
}

//24. 两两交换链表中的节点
/*
给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。

你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

思路：画图理清用虚拟头调换位置的关系。
*/
ListNode* swapPairs(ListNode* head){
    ListNode* dummyHead = new ListNode(0, head); 
    ListNode* curr = dummyHead; 
    while(curr->next && curr->next->next){
        ListNode* temp_next = curr->next; 
        ListNode* temp_next_next_next = curr->next->next->next; 
        curr->next = curr->next->next; 
        curr->next->next = temp_next; 
        curr->next->next->next = temp_next_next_next; 
    }
    head = dummyHead->next; 
    delete dummyHead;
    return head;
}
/*
19. 删除链表的倒数第 N 个结点
给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。
进阶：你能尝试使用一趟扫描实现吗？
*/
//方法1: 遍历一遍找长度，再确定具体位置
//can be improved by using a dummy head
ListNode* removeNthFromEnd(ListNode* head, int n) {
    if(!head->next){
        return nullptr;
    }
    int length = 0;
    ListNode* p = head; 
    while(p){
        p = p->next; 
        length++;
    }
    if(length == n){
        return head->next;
    }
    int gap = length - n - 1; 
    ListNode* curr = head;
    while(gap > 0){
        curr = curr->next; 
        gap--;
    }
    if(curr->next != nullptr){
        ListNode* temp = curr->next;
        curr->next = curr->next->next;
        delete temp; 
    }
    else {
        curr = nullptr;
    }
    return head;
}
//方法2: 双指针，只用遍历一遍
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode* dummyHead = new ListNode(0);
    dummyHead->next = head;
    ListNode* fast = dummyHead;
    ListNode* slow = dummyHead;
    while(n-- && fast){
        fast = fast->next;
    }
    fast = fast->next;
    while(fast){
        slow = slow->next; 
        fast = fast->next;
    }
    ListNode* temp = slow->next;
    slow->next = slow->next->next;
    delete temp; 
    head = dummyHead->next;
    return head;
}