

#include <iostream>
#include <chrono>
#include "ExponentialVector.h"
#include "StrictVector.h"
using namespace std;
using namespace std::chrono;

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