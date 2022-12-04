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

enum Mode
{
    partial,
    full
};

std::stringstream dataPreprocess(const std::string data)
{
    std::stringstream tmp;
    std::string tmps{data};
    std::replace(tmps.begin(), tmps.end(), '-', ' ');
    std::replace(tmps.begin(), tmps.end(), ',', ' ');
    tmp << tmps;
    return tmp;
}

bool fullyContained(std::vector<int> data)
{
    if (data.size() != 4)
        return 0;
    if (data.at(3) >= data.at(1) && data.at(2) <= data.at(0))
    {
        return 1;
    }
    else if (data.at(3) <= data.at(1) && data.at(2) >= data.at(0))
    {
        return 1;
    }
    return 0;
}

bool partiallyContained(std::vector<int> data)
{
    if (data.size() != 4)
        return 0;
    if (data.at(3) >= data.at(0) && data.at(2) <= data.at(1))
    {
        return 1;
    }
    return 0;
}

bool checkContained(const std::string data, Mode mode)
{

    std::stringstream datastream{dataPreprocess(data)};
    std::string tmp;
    int tmpint;
    std::vector<int> numholder;
    while (!datastream.eof())
    {
        datastream >> tmp;
        if (std::stringstream(tmp) >> tmpint)
        {
            numholder.push_back(tmpint);
        }
    }

    if (mode == Mode::full)
    {
        return fullyContained(numholder);
    }
    if (mode == Mode::partial)
    {
        return partiallyContained(numholder);
    }

    return 0;
}

int main()
{
    std::ifstream items("inputday4.txt");
    std::string data;
    std::uint64_t total{0};
    std::vector<std::string> tmp;
    while (getline(items, data))
    {
        total += checkContained(data, Mode::partial);
    }
    std::cout << total << std::endl;
    return 0;
}