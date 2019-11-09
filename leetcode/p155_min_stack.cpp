//
// Created by 付旭炜 on 2019/11/9.
//

/// ```
/// class MinStack {
///    int min = Integer.MAX_VALUE;
///    Stack<Integer> stack = new Stack<Integer>();
///    public void push(int x) {
///        // only push the old minimum value when the current
///        // minimum value changes after pushing the new value x
///        if(x <= min){
///            stack.push(min);
///            min=x;
///        }
///        stack.push(x);
///    }
///
///    public void pop() {
///        // if pop operation could result in the changing of the current minimum value,
///        // pop twice and change the current minimum value to the last minimum value.
///        if(stack.pop() == min) min=stack.pop();
///    }
///
///    public int top() {
///        return stack.peek();
///    }
///
///    public int getMin() {
///        return min;
///    }
///}
///```

class MinStack {
private:
    stack<int> s1;
    stack<int> s2;
public:
    void push(int x) {
        s1.push(x);
        if (s2.empty() || x <= getMin())  s2.push(x);
    }
    void pop() {
        if (s1.top() == getMin())  s2.pop();
        s1.pop();
    }
    int top() {
        return s1.top();
    }
    int getMin() {
        return s2.top();
    }
};