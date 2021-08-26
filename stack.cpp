class MyQueue {
public:
    /** Initialize your data structure here. */
    stack<int> _stack1;
    stack<int> _stack2;
    int _size;
    MyQueue() {
        _size = 0;
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        _size++;
        _stack1.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        _size--;
        if(_stack2.empty()){
            while(!_stack1.empty()){
                int top = _stack1.top();
                _stack2.push(top);
                _stack1.pop();
                }
        }
        int top = _stack2.top();
        _stack2.pop();
        return top;
    }
    
    /** Get the front element. */
    int peek() {
        int res = this->pop(); //every class has a this pointer that points to the address of itself. 
        //use the pop function to avoid replicating the code --> 好习惯
        _stack2.push(res);
        _size++;
        return res;
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return _size == 0;
    }
};

//225. 用队列实现栈
/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */


class MyStack {
public:
    /** Initialize your data structure here. */
    queue<int> _queue1;
    queue<int> _queue2;
    MyStack() {
    }
    
    /** Push element x onto stack. */
    void push(int x) {
        _queue1.push(x);
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int count = _queue1.size() - 1;
        while(count > 0){
            count--;
            int top = _queue1.front();
            _queue2.push(top);
            _queue1.pop();
        }
        int res = _queue1.front();
        _queue1.pop();
        while(!_queue2.empty()){
            int back = _queue2.front();
            _queue1.push(back);
            _queue2.pop();
        }
        return res;
    }
    
    /** Get the top element. */
    int top() {
        return _queue1.back();
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return _queue1.size() == 0; 
    }
};
