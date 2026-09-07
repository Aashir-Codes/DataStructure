#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include "Vector.h"

using namespace std;

void Task1()
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
}

void Task2()
{
    std::vector<int> vec;

    for (int i = 0; i < 5; i++)
    {
        vec.push_back(rand() % 50);
    }

    int key = rand() % 5;
    int target = vec[key];
    bool exists = (std::find(vec.begin(), vec.end(), target) != vec.end());
    std::cout << "1. Exists: " << std::boolalpha << exists << "\n";
    std::sort(vec.begin(), vec.end());

    int max_val = *std::max_element(vec.begin(), vec.end());
    int min_val = *std::min_element(vec.begin(), vec.end());
    std::cout << "3. Max: " << max_val << ", Min: " << min_val << "\n";

    int sum = std::accumulate(vec.begin(), vec.end(), 0);
    double average = vec.empty() ? 0.0 : static_cast<double>(sum) / vec.size();
    std::cout << "4. Sum: " << sum << ", Average: " << average << "\n";

    int frequency = std::count(vec.begin(), vec.end(), target);
    std::cout << "5. Count of " << target << ": " << frequency << "\n";

    std::reverse(vec.begin(), vec.end());

    std::sort(vec.begin(), vec.end());
    bool found_bs = std::binary_search(vec.begin(), vec.end(), target);
    std::cout << "7. Binary Search found " << target << ": " << std::boolalpha << found_bs << "\n";
}

int main()
{
    Task1();
    Task2();
}
