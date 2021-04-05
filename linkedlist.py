'''
18. 删除链表的节点

给定单向链表的头指针和一个要删除的节点的值，定义一个函数删除该节点。

返回删除后的链表的头节点。
'''
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None
class Solution:
    def deleteNode(self, head: ListNode, val: int) -> ListNode:
        if head == None:
            return head
        if head.val == val:
            return head.next
        prevNode = ListNode(0,head)#dummyHead
        currNode = head
        while currNode != None: 
            if currNode.val == val: 
                prevNode.next = currNode.next
                currNode.next = None
                return head
            prevNode =  currNode
            currNode = currNode.next
        return head

'''
22. 链表中倒数第 k 个节点
输入一个链表，输出该链表中倒数第k个节点。为了符合大多数人的习惯，本题从1开始计数，即链表的尾节点是倒数第1个节点。
'''
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def getKthFromEnd(self, head: ListNode, k: int) -> ListNode:
        length = 0 
        pointer = head
        while pointer != None: 
            length+=1
            pointer = pointer.next
        if k == length:
            return head
        for i in range(length-k):
            head = head.next
        return head
        
'''
25. 输入两个递增排序的链表，合并这两个链表并使新链表中的节点仍然是递增排序的。
'''
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

#Solution 1: use pointers 
class Solution:
    def mergeTwoLists(self, l1: ListNode, l2: ListNode) -> ListNode:
        pointer1 = l1
        pointer2 = l2 
        l3 = ListNode(0)
        pointer3 = l3
        while pointer1 != None and pointer2 != None: 
            if pointer1.val < pointer2.val:
                pointer3.next = pointer1
                pointer1 = pointer1.next
            else: 
                pointer3.next = pointer2
                pointer2 = pointer2.next
            pointer3 = pointer3.next
        while pointer1: 
            pointer3.next = pointer1
            pointer1 = pointer1.next
            pointer3 = pointer3.next
        while pointer2:
            pointer3.next = pointer2
            pointer2 = pointer2.next
            pointer3 = pointer3.next
        return l3.next


#Solution 2: recursion
class Solution:
    def mergeTwoLists(self, l1: ListNode, l2: ListNode) -> ListNode:
        if l1 == None: 
            return l2 
        if l2 == None:
            return l1 
        if l1.val < l2.val:
            l1.next = mergeTwoLists(l1.next, l2)
            return l1
        else: 
            l2.next = mergeTwoLists(l1, l2.next)
            return l2 

'''
52. 两个链表的第一个公共节点
输入两个链表，找出它们的第一个公共节点。
'''
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> ListNode:
        if headA == None or headB == None: 
            return None
        currA = headA
        currB = headB
        while currA != currB:
            currA =  currA.next if currA != None else headB
            currB = currB.next if currB != None else headA
        return currA

#如果一直这样跑，两个pointer终究会在公共点相遇；如果相遇点为None，则没有公共点
#A+B的长度=B+A的长度，所以把currA转到headB上是相当于遍历了A+B，而currB转到headA上则是遍历了B+A
#所以如果一遍A+B都没有相遇，则两个指针会同时到达A+B的尾节点，也就是None