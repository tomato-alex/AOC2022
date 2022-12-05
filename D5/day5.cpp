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
    keep,
    append
};

std::vector<int> dataPreprocess(const std::string data)
{
    std::vector<int> args;
    int tmpint;
    std::stringstream ss{data};
    std::string sshelper;
    while (!ss.eof())
    {
        ss >> sshelper;
        if (std::stringstream(sshelper) >> tmpint)
        {
            args.push_back(tmpint);
        }
    }
    return args;
}

std::vector<std::vector<std::string>> invTranspose(std::vector<std::vector<std::string>> tp)
{
    std::vector<std::vector<std::string>> invtmp;
    for (int i = tp.size() - 1; i >= 0; --i)
    {
        invtmp.push_back(tp.at(i));
    }
    int rows = invtmp.size();
    if (rows == 0)
        return {{}};
    int cols = invtmp[0].size();
    std::vector<std::vector<std::string>> r(cols, std::vector<std::string>(rows));
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            r[j][i] = invtmp[i][j];
        }
    }
    return r;
}

void printMatrix(std::vector<std::vector<std::string>> matrix)
{
    for (auto i : matrix)
    {
        for (auto j : i)
        {
            std::cout << j;
        }
        std::cout << std::endl;
    }
}

int findLongest(std::vector<std::vector<std::string>> matrix)
{
    int longest = 0;
    for (auto i : matrix)
    {
        if (i.size() > longest)
            longest = i.size();
    }
    return longest;
}
std::vector<std::vector<std::string>> processMatrix(std::vector<std::vector<std::string>> inverseds, std::vector<int> args, Mode m)
{
    std::vector<std::string> tmp{};
    for (int i = inverseds.at(args.at(1) - 1).size() - 1; i >= 0; --i)
    {
        if (inverseds.at(args.at(1) - 1).at(i) != "   ")
        {
            tmp.push_back(inverseds.at(args.at(1) - 1).at(i));
            inverseds.at(args.at(1) - 1).at(i) = "   ";
            --args.at(0);
        }
        if (args.at(0) == 0)
        {
            break;
        }
    }
    for (int i = inverseds.at(args.at(2) - 1).size() - 1; i >= 0; --i)
    {
        if (inverseds.at(args.at(2) - 1).at(i) != "   ")
        {
            break;
        }
        inverseds.at(args.at(2) - 1).pop_back();
    }
    if (Mode::keep)
    {
        reverse(tmp.begin(), tmp.end());
    }
    for (auto i : tmp)
    {
        inverseds.at(args.at(2) - 1).push_back(i);
    }
    int longest = findLongest(inverseds);
    for (auto i : inverseds)
    {
        while (i.size() < longest)
        {
            i.push_back("   ");
        }
    }
    return inverseds;
}

int main()
{
    std::ifstream items("inputday5.txt");
    std::string data;

    std::vector<std::vector<std::string>> dataset{
        {"[J]", "   ", "   ", "   ", "[F]", "[M]", "   ", "   ", "   "},
        {"[Z]", "[F]", "   ", "[G]", "[Q]", "[F]", "   ", "   ", "   "},
        {"[G]", "[P]", "   ", "[H]", "[Z]", "[S]", "[Q]", "   ", "   "},
        {"[V]", "[W]", "[Z]", "[P]", "[D]", "[G]", "[P]", "   ", "   "},
        {"[T]", "[D]", "[S]", "[Z]", "[N]", "[W]", "[B]", "[N]", "   "},
        {"[D]", "[M]", "[R]", "[J]", "[J]", "[P]", "[V]", "[P]", "[J]"},
        {"[B]", "[R]", "[C]", "[T]", "[C]", "[V]", "[C]", "[B]", "[P]"},
        {"[N]", "[S]", "[V]", "[R]", "[T]", "[N]", "[G]", "[Z]", "[W]"}};

    std::vector<std::vector<std::string>> inverseds{invTranspose(dataset)};

    printMatrix(inverseds);

    while (getline(items, data))
    {
        std::vector<int> args = dataPreprocess(data);
        inverseds = processMatrix(inverseds, args, Mode::append);
    }

    printMatrix(inverseds);
    return 0;
}