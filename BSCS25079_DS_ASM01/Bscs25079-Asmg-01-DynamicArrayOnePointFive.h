#pragma once

using namespace std;

template <typename T>
class DynamicArrayOnePointFive
{
private:
    T *data;
    int size;
    int capacity;
    void resize()
    {
        T *temp = new T[capacity]{};
        for (int i = 0; i < size; i++)
        {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
    }

public:
    // constructors - can be more than 1
    DynamicArrayOnePointFive()
    {
        size = 0;
        capacity = 2;
        data = new T[capacity]{};
    }

    // function for insertion
    void push_back(T value)
    {
        if (size == capacity)
        {
            capacity = (capacity * 3) / 2;
            resize();
        }
        data[size++] = value;
    }

    // operators for update/read
    T operator[](int index) const // read-only access
    {
        return data[index];
    }
    T &operator[](int index) // writable access
    {
        return data[index];
    }

    // implement helper functions: get_size, print array, etc, and other utility functions
    friend std::ostream &operator<<(ostream &out, const DynamicArrayOnePointFive<T> &other)
    {
        // implement printing elements here

        out << "[ ";

        for (int i = 0; i < other.size; i++)
        {
            out << other.data[i] << " ";
        }
        out << "]" << std::endl;

        return out;
    }

    int get_size() const { return size; }
    // destructor
    ~DynamicArrayOnePointFive()
    {
        delete[] data;
    }
};
