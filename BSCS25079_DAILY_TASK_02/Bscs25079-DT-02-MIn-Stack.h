#include <stack>

template <typename T>
class MinStack
{
    std::stack<T> data;
    std::stack<T> min;

public:
    MinStack() {}

    void push(T val)
    {
        if (min.empty() || min.top() >= val)
        {
            min.push(val);
        }

        data.push(val);
    }

    T top()
    {
        if (data.empty())
            throw std::runtime_error("Stack is empty");
        return data.top();
    }

    T get_min()
    {
        if (min.empty())
            throw std::runtime_error("Stack is empty");
        return min.top();
    }

    void pop()
    {
        if (data.empty())
            throw std::runtime_error("Stack is empty");
        if (data.top() == min.top())
        {
            min.pop();
        }
        data.pop();
    }
};