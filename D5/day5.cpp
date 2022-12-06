#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <deque>

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

std::vector<int> dataPreprocess(const std::string &data)
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

void printMatrix2(const std::vector<std::deque<std::string>> &matrix)
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

int findLongest(const std::vector<std::vector<std::string>> &matrix)
{
    int longest = 0;
    for (auto i : matrix)
    {
        if (i.size() > longest)
            longest = i.size();
    }
    return longest;
}

std::vector<std::deque<std::string>> VStoVDSTransform(const std::vector<std::string> &tp)
{
    std::vector<std::vector<std::string>> inputdata;
    for (auto row : tp)
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
    int longest = findLongest(inputdata);
    for (auto i : inputdata)
    {
        while (i.size() < longest)
        {
            i.push_back("   ");
        }
    }

    std::vector<std::deque<std::string>> res(inputdata[0].size());
    for (auto &row : inputdata)
    {
        int cntr = 0;
        for (auto &cell : row)
        {
            if (cell != "   ")
            {
                res[cntr].push_back(cell);
            }
            ++cntr;
            if (cntr >= tp[0].size())
            {
                break;
            }
        }
    }
    return res;
}

std::vector<std::deque<std::string>> processMatrix2(std::vector<std::deque<std::string>> matrix, const std::vector<int> &args, Mode m)
{
    if (m == Mode::append)
    {
        int cntr = args[0];
        while (cntr-- > 0)
        {
            matrix[args[2] - 1].push_front(matrix[args[1] - 1].front());
            matrix[args[1] - 1].pop_front();
        }
    }
    if (m == Mode::keep)
    {
        int cntr = args[0];
        std::deque<std::string> tmp(cntr);
        while (cntr-- != 0)
        {
            tmp.push_back(matrix[args[1] - 1].front());
            matrix[args[1] - 1].pop_front();
        }
        while (!tmp.empty())
        {
            matrix[args[2] - 1].push_front(tmp.back());
            tmp.pop_back();
        }
    }
    return matrix;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    std::ifstream items("inputday5.txt");
    std::string data;

    std::vector<std::string> tmpinput;
    std::vector<std::deque<std::string>> inputdata2;
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
            inputdata2 = VStoVDSTransform(tmpinput);
        }
        else if (inputMode == InputMode::m2)
        {
            std::vector<int> args = dataPreprocess(data);
            inputdata2 = processMatrix2(inputdata2, args, Mode::append);
        }
    }

    printMatrix2(inputdata2);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: "
              << duration.count() << " microseconds" << std::endl;

    return 0;
}