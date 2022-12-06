#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <set>
#include <sstream>
#include <chrono>
#include <deque>

std::uint64_t part1()
{
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    std::ifstream items("inputday7.txt");
    std::string data;
    while (getline(items, data))
    {
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: "
              << duration.count() << " microseconds" << std::endl;

    return 0;
}