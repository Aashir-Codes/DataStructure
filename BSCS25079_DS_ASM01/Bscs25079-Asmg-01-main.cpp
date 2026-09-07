#include <chrono>
#include <fstream>
#include "Bscs25079-Asmg-01-DynamicArray.h"
#include "Bscs25079-Asmg-01-DynamicArrayDouble.h"
#include "Bscs25079-Asmg-01-DynamicArrayOnePointFive.h"

using namespace std;
using namespace std::chrono;

void generateDataFile(const std::string &filename)
{
    std::ofstream file(filename);
    int count = 524288;

    for (int i = 1; i <= count; i++)
    {
        file << i << "\n";
    }
    file.close();
}
void runExperiment(const std::string &dataFile)
{
    // --- DynamicArray (+1 growth) ---
    {
        DynamicArray<int> arr;
        std::ifstream file(dataFile);
        int val;

        auto start = high_resolution_clock::now();
        while (file >> val)
            arr.push_back(val);
        auto end = high_resolution_clock::now();

        double ms = duration<double, std::milli>(end - start).count();
        std::cout << "DynamicArray (+1):    " << ms << " ms\n";

        // Save to output file (NOT printing all elements, just a summary)
        std::ofstream out("OutputDynamicArray.txt");
        out << "Elements loaded: " << 524288 << "\n";
        out << "Time taken: " << ms << " ms\n";
    }

    // --- DynamicArrayDouble (2x growth) ---
    {
        DynamicArrayDouble<int> arr;
        std::ifstream file(dataFile);
        int val;

        auto start = std::chrono::high_resolution_clock::now();
        while (file >> val)
            arr.push_back(val);
        auto end = std::chrono::high_resolution_clock::now();

        double ms = std::chrono::duration<double, std::milli>(end - start).count();
        std::cout << "DynamicArrayDouble (2x): " << ms << " ms\n";

        std::ofstream out("OutputDynamicArrayDouble.txt");
        out << "Elements loaded: " << 524288 << "\n";
        out << "Time taken: " << ms << " ms\n";
    }

    // --- DynamicArrayOnePointFive (1.5x growth) ---
    {
        DynamicArrayOnePointFive<int> arr;
        std::ifstream file(dataFile);
        int val;

        auto start = std::chrono::high_resolution_clock::now();
        while (file >> val)
            arr.push_back(val);
        auto end = std::chrono::high_resolution_clock::now();

        double ms = std::chrono::duration<double, std::milli>(end - start).count();
        std::cout << "DynamicArrayOnePointFive (1.5x): " << ms << " ms\n";

        std::ofstream out("ArrayOnePointFive.txt");
        out << "Elements loaded: " << 524288 << "\n";
        out << "Time taken: " << ms << " ms\n";
    }
}

int main()
{
    generateDataFile("data.txt");
    runExperiment("data.txt");
    return 0;
}