
#include <iostream>
#include <exception>
using namespace std;
template <typename T>
class ExponentialVector
{
private:
    T *arr;
    int size;
    int cap;
    void resize()
    {
        T *temp = new T[cap]{};

        for (int i = 0; i < size; i++)
        {
            temp[i] = arr[i];
        }
        delete[] arr;

        arr = temp;
    }

public:
    ExponentialVector(int initialCap = 2)
    {
        size = 0;
        cap = initialCap;
        arr = new T[cap]{};
    }
    ~ExponentialVector()
    {
        delete[] arr;
    }
    void push_back(const T &val)
    {
        if (size == cap)
        {
            cap *= 2;
            resize();
        }
        arr[size] = val;
        size++;
    }
    void pop_back()
    {
        if (size == 0)
        {
            throw(std::underflow_error("Vector is Empty!"));
        }
        size--;
    }
    int get_size() const { return size; }
    int get_capacity() const { return cap; }
    T &operator[](int index)
    {
        if (index < 0 or index >= size)
        {
            throw(std::out_of_range("index is out of range"));
        }

        return arr[index];
    }
};