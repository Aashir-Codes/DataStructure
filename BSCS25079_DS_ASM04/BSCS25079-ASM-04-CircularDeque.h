#pragma omce
#include <iostream>
#include <exception>
class CircularDeque
{
private:
    int *arr;
    int front;
    int rear;
    int capacity;
    int count;

public:
    CircularDeque(int cap = 5)
    {
        capacity = cap;
        arr = new int[capacity]{};
        front = count = 0;
        rear = -1;
    }
    ~CircularDeque()
    {
        delete[] arr;
    }
    bool insertFront(int val)
    {
        if (isFull())
        {
            // throw(std::overflow_error("Deque is Full"));
            return false;
        }

        front = ((front - 1 + capacity) % capacity); // -1 + 5 % 5 =  4%5 = 0  // 5%5= 0
        arr[front] = val;
        count++;

        return true;
    }
    bool insertRear(int val)
    {
        if (isFull())
        {
            // throw(std::overflow_error("Deque is Full"));

            return false;
        }

        rear = (rear + 1) % capacity;
        arr[rear] = val;
        count++;
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