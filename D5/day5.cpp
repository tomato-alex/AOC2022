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

// TODO convert vector of vectors to vector of deques for faster poping

enum Mode
{
    keep,
    append
};
enum InputMode
{
    m1,
    m2
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

std::vector<std::vector<std::string>> VStoVVSTransform(std::vector<std::string> tmpinput)
{
    std::vector<std::vector<std::string>> inputdata;
    for (auto row : tmpinput)
    {
        std::string shelper = "";
        std::vector<std::string> vhelper;
        int cntr = 0;

        for (auto cell : row)
        {
            if (cell != ' ' && cntr == 0)
            {
                shelper += cell;
                if (cell == ']')
                {
                    vhelper.push_back(shelper);
                    shelper = "";
                }
            }
            if (cell == ' ' && cntr == 0)
            {
                shelper = "";
                ++cntr;
            }
            if (cell == ' ' && cntr > 0)
            {
                if (cntr == 4)
                {
                    vhelper.push_back("   ");
                    cntr = 0;
                }
                ++cntr;
            }
            if (cell != ' ' && cntr > 0)
            {
                shelper += cell;
                cntr = 0;
            }
        }

        inputdata.push_back(vhelper);
    }
    inputdata.pop_back();
    int longest = 0;
    for (auto i : inputdata)
    {
        if (i.size() > longest)
        {
            longest = i.size();
        }
    }
    for (auto i : inputdata)
    {
        while (i.size() < longest)
        {
            i.push_back("   ");
        }
    }
    return inputdata;
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
    auto start = std::chrono::high_resolution_clock::now();
    std::ifstream items("inputday5.txt");
    std::string data;

    std::vector<std::string> tmpinput;
    std::vector<std::vector<std::string>> inputdata;
    InputMode inputMode = InputMode::m1;
    while (getline(items, data))
    {
        if (inputMode == InputMode::m1)
        {
            if (data != "")
            {
                tmpinput.push_back(data);
                continue;
            }

            inputMode = InputMode::m2;
            inputdata = VStoVVSTransform(tmpinput);
            inputdata = invTranspose(inputdata);
        }
        else if (inputMode == InputMode::m2)
        {
            // std::cout << "Im here!\n";
            std::vector<int> args = dataPreprocess(data);
            inputdata = processMatrix(inputdata, args, Mode::append);
        }
    }

    printMatrix(inputdata);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: "
              << duration.count() << " microseconds" << std::endl;

    return 0;
}