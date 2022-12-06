#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <chrono>
#include <deque>

bool checkRepetitions(std::deque<char> chdeque, int limit)
{
    if (chdeque.size() < limit)
    {
        return false;
    }
    int hash[256] = {0};

    for (int i = 0; i < chdeque.size(); ++i)
    {
        int k = (int)chdeque.at(i);
        ++hash[k];
        if (hash[k] > 1)
        {
            return true;
        }
    }
    return false;
}

std::uint64_t noRepeatAfter(std::string str, int limit)
{
    std::deque<char> charset;

    for (std::uint64_t i{0}; i < str.size(); ++i)
    {
        charset.push_back(str.at(i));
        if (charset.size() >= limit + 1)
        {
            charset.pop_front();
            if (!checkRepetitions(charset, limit))
            {
                return (i + 1);
                break;
            }
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