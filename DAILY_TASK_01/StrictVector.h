#include <iostream>
using namespace std;
template <typename T>
class StrictVector
{
private:
    T *arr;
    int size;

public:
    StrictVector()
    {
        size = 0;
        arr = nullptr;
    }
    ~StrictVector()
    {
        delete[] arr;
    }
    void push_back(const T &val)
    {
        T *temp = new T[size + 1]{};
        for (int i = 0; i < size; i++)
        {
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
        arr[size++] = val;
    }
    void pop_back()
    {
        if (size == 0)
        {
            throw(std::underflow_error("Vector is Empty!"));
        }
        T *temp = new T[size - 1]{};
        for (int i = 0; i < size - 1; i++)
        {
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
    }
    int get_size() const { return size; }
    T &operator[](int index)
    {
        if (index < 0 or index >= size)
        {
            throw(std::out_of_range("index is out of range"));
        }

        return arr[index];
    }
};