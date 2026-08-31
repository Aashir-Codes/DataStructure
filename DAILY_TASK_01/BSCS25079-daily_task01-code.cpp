

#include <iostream>
#include <chrono>
#include "ExponentialVector.h"
#include "StrictVector.h"
using namespace std;
using namespace std::chrono;

#include <exception>
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
/*
   Two Approaches differ greatly interms of the complexity for example
   the time complexity of push_back and pop_back the value in exponential
   vector is O(1) amortized. which grows
   slowly as compare to the timecomplexity of push_back and pop_back the value
   in strict vector in which
   everytime a new value is added the whole array is copied and then assigned
   hence its time complexity is O(n). The getters are of O(1) constant time
   complexity.

*/
int main()
{
    const int EXP_SIZE = 1048576;
    const int STRICT_SIZE = 100000;

    auto start1 = high_resolution_clock::now();
    ExponentialVector<int> expVec;
    for (int i = 0; i < EXP_SIZE; i++) // ← changed
        expVec.push_back(i);
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<milliseconds>(stop1 - start1);
    cout << "Exponential Vector (1 MB Insertion): " << duration1.count() << " ms" << endl;

    auto start2 = high_resolution_clock::now();
    StrictVector<int> strictVec;
    for (int i = 0; i < STRICT_SIZE; i++) // ← changed
        strictVec.push_back(i);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<milliseconds>(stop2 - start2);
    cout << "Strict Resizing Vector Insertion Time: " << duration2.count() << " ms" << endl;

    return 0;
}