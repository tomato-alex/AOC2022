#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <set>

std::uint64_t stringSplitSortCalc(const std::string data)
{
    std::string s1 = data.substr(0, data.length() / 2);
    std::string s2 = data.substr(data.length() / 2, data.length());
    std::uint64_t total{0};
    std::sort(s1.begin(), s1.end());
    std::sort(s2.begin(), s2.end());

    std::cout << data << " = " << s1 << " " << s2;
    for (auto i : s1)
    {
        if (s2.find(i) != -1)
        {
            if (i >= 'a' && i <= 'z')
            {
                total += static_cast<int>(i - 'a') + 1;
            }
            else if (i >= 'A' && i <= 'Z')
            {
                total += static_cast<int>(i - 'A') + 27;
            }

            s1.replace(s1.find(i), 1, "_");
            s2.replace(s2.find(i), 1, "_");
            break;
        }
    }
    std::cout << " " << total;
    return total;
}

std::uint64_t elfGroups(const std::vector<std::string> sV)
{
    std::uint64_t total{0};
    for (auto i : sV.at(0))
    {
        if (sV.at(1).find(i) != std::string::npos && sV.at(2).find(i) != std::string::npos)
        {
            if (i >= 'a' && i <= 'z')
            {
                total += static_cast<int>(i - 'a') + 1;
            }
            else if (i >= 'A' && i <= 'Z')
            {
                total += static_cast<int>(i - 'A') + 27;
            }
            break;
        }
    }
    return total;
}

int main()
{
    std::ifstream items("inputday3.txt");
    std::string data;
    std::uint64_t total{0};
    std::vector<std::string> tmp;
    while (getline(items, data))
    {
        tmp.push_back(data);
        if (tmp.size() == 3)
        {
            total += elfGroups(tmp);
            tmp.clear();
        }
    }
    // total = Part2(tmp);
    std::cout << total << std::endl;
    return 0;
}