#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

int main()
{
    int currsum = 0;
    std::vector<int> top3{{0, 0, 0}};
    std::string data;
    std::ifstream calories("day1input.txt");

    while (getline(calories, data))
    {
        if (data == "")
        {
            top3.push_back(currsum);
            std::sort(top3.begin(), top3.end(), std::greater<int>());
            top3.pop_back();
            currsum = 0;
        }
        else
        {
            currsum += std::stoi(data);
        }
    }
    currsum = std::reduce(top3.begin(), top3.end());
    std::cout << currsum << std::endl;    // sum of all
    std::cout << top3.at(0) << std::endl; // top element
    return 0;
}