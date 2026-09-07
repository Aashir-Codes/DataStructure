
template <typename T>
class Stack_Array
{

private:
    int size;
    int capacity;
    T *arr;

    void resize(int cap)
    {
        T *temp = new T[cap]{};

        for (int i = 0; i < size; i++)
        {
            temp[i] = arr[i];
        }
        capacity = cap;
        delete[] arr;
        arr = temp;
    }

public:
    Stack_Array(int _capacity = 1)
    {
        capacity = _capacity;
        size = 0;
        arr = new T[capacity]{};
    }
    void push(T val)
    {
        if (size == capacity)
        {
            resize(capacity * 2);
        }

        arr[size++] = val;
    }
    T top()
    {
        if (size == 0)
            throw std::runtime_error("Stack is empty");
        return arr[size - 1];
    }
    void pop()
    {
        if (size == 0)
            throw std::runtime_error("Stack is empty");
        size--;
    }

    ~Stack_Array()
    {
        delete[] arr;
    }
};