#include <iostream>
using namespace std;

class InputRestrictedDeque
{
private:
    int *arr;
    int front;
    int rear;
    int capacity;
    int count;

public:
    InputRestrictedDeque(int cap = 5)
    {
        arr = new int[cap]{};
        capacity = cap;
        rear = -1;
        count = front = 0;
    }
    ~InputRestrictedDeque()
    {
        delete[] arr;
    }

    bool insertRear(int val)
    {
        if (isFull())
        {
            return false;
        }

        rear = (rear + 1) % capacity;
        return true;
    }
    bool deleteFront()
    {
        if (isEmpty())
        {
            return false;
            // throw(std::underflow_error("Deque is Empty"));
        }
        front = (front + 1) % capacity;
        count--;
        return true;
    }
    bool deleteRear()
    {
        if (isEmpty())
        {
            return false;
            // throw(std::underflow_error("Deque is Empty"));
        }

        rear = (rear - 1 + capacity) % capacity;
        count--;
        return true;
    }
    int getFront() const
    {
        if (isEmpty())
        {
            throw(std::underflow_error("Deque is Empty"));
        }

        return arr[front];
    }
    int getRear() const
    {
        if (isEmpty())
        {
            throw(std::underflow_error("Deque is Empty"));
        }

        return arr[rear];
    }
    bool isEmpty() const
    {
        return count == 0;
    }
    bool isFull() const
    {
        return count == capacity;
    }
    void display() const
    {
        if (isEmpty())
        {
            throw(std::underflow_error("Deque is Empty"));
        }
        int pointer = front;
        for (int i = 0; i < count; i++)
        {
            std::cout << arr[pointer] << " ";
            pointer = (pointer + 1) % capacity;
        }
    }
};
