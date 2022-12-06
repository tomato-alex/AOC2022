#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <chrono>

bool checkRepetitions2(const int limit, const int start, const std::string str)
{
    int hash[26] = {false};

    for (int i = start; i < start + limit; ++i)
    {
        int k = (int)(str.at(i) - 'a');
        if (hash[k])
        {
            return true;
        }
        hash[k] = true;
    }
    return false;
}

std::uint64_t noRepeatAfter(const std::string str, const int limit)
{
    for (std::uint64_t i{0}; i < str.size() - limit; ++i)
    {
        if (!checkRepetitions2(limit, i, str))
        {
            return (i + limit);
        }
    }
    return 0;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    std::ifstream items("inputday6.txt");
    std::string data;
    while (getline(items, data))
    {
        std::cout << noRepeatAfter(data, 4) << std::endl;
        std::cout << noRepeatAfter(data, 14) << std::endl;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: "
              << duration.count() << " microseconds" << std::endl;

    return 0;
}