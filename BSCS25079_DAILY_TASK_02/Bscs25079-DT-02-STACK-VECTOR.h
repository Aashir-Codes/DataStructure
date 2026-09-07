#include <vector>
template <typename T>
class Stack_Vector
{

private:
    std::vector<T> data;

public:
    Stack_Vector()
    {
    }
    Stack_Vector(int _capacity)
    {
        data.reserve(_capacity);
    }
    void push(T val)
    {
        data.push_back(val);
    }
    T top()
    {
        if (data.empty())
            throw std::runtime_error("Stack is empty");
        return data.back();
    }
    void pop()
    {
        if (data.empty())
            throw std::runtime_error("Stack is empty");
        data.pop_back();
    }
};