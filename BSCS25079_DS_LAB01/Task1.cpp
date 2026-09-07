#include <iostream>
#include "Vector.h"
using namespace std;

int main()
{
    Vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    cout << "Forward Traversal using Iterator: ";
    for (Vector<int>::Iterator it = vec.begin(); it != vec.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    // Testing pointer arithmetic operators
    Vector<int>::Iterator it = vec.begin();
    Vector<int>::Iterator offsetIt = it + 2;
    cout << "Element at index 2 (via iterator addition): " << *offsetIt << endl;
    cout << "Distance (end - begin): " << (vec.end() - vec.begin()) << endl;

    return 0;
}
