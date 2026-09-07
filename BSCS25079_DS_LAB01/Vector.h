#include <iostream>
#include <cmath>
using namespace std;

template <typename T>
class Vector
{
private:
    T *arr;  // dynamically allocated storage
    int cap; // current capacity
    int len; // number of elements currently stored
    void reallocate(int newCap)
    {
        T *temp = new T[newCap];
        for (int i = 0; i < len; i++)
        {
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
        cap = newCap;
    }

public:
    Vector()
    {
        cap = 1;
        len = 0;
        arr = new T[cap];
    }
    Vector(const Vector<T> &other)
    {
        cap = other.cap;
        arr = new T[cap];

        for (int i = 0; i < other.len; i++)
        {
            arr[i] = other.arr[i];
        }
        len = other.len;
    }
    ~Vector()
    {
        delete[] arr;
    }

    void push_back(const T &val)
    {
        if (len == cap)
            reallocate(cap * 2);
        arr[len++] = val;
    }
    void pop_back()
    {
        if (len > 0)
            len--;
    }
    T &operator[](int index)
    {
        if (index < 0 || index >= len)
            throw std::out_of_range("Index out of range");
        return arr[index];
    }
    int size() const
    {
        return len;
    }
    int capacity() const
    {
        return cap;
    }
    bool empty() const
    {
        return len == 0;
    }

    // ---- Iterator support ----
    class Iterator
    {
    private:
        T *ptr;

    public:
        Iterator(T *p = nullptr)
        {
            ptr = p;
        }

        T &operator*() const
        {
            return *ptr;
        }
        Iterator &operator++() // prefix ++it
        {
            ++ptr;
            return *this;
        }
        Iterator operator++(int) // postfix it++
        {
            Vector<T>::Iterator temp = *this;
            ++ptr;
            return temp;
        }
        Iterator &operator--() // prefix --it
        {
            --ptr;
            return *this;
        }

        Iterator operator--(int)
        {
            Vector<T>::Iterator temp = *this;
            --ptr;
            return temp;
        }

        Iterator operator+(int n) const
        {
            Vector<T>::Iterator temp{ptr + n};
            return temp;
        }
        Iterator operator-(int n) const
        {

            Vector<T>::Iterator temp{ptr - n};
            return temp;
        }
        int operator-(const Iterator &other) const // distance between two iterators
        {
            return ptr - other.ptr;
        }
        bool operator==(const Iterator &other) const
        {
            return this->ptr == other.ptr;
        }
        bool operator!=(const Iterator &other) const
        {
            return !(*this == other);
        }
        bool operator<(const Iterator &other) const
        {
            return this->ptr < other.ptr;
        }
    };

    Iterator begin()
    {
        return Vector<T>::Iterator{arr};
    }
    Iterator end()
    {
        Vector<T>::Iterator temp(arr + len);

        return temp;
    }
};
