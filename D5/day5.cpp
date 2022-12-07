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
    while (ss >> sshelper)
    {
        if (std::stringstream(sshelper) >> tmpint)
        {
            args.push_back(tmpint);
        }
    }
    return args;
}

void printMatrix2(const std::vector<std::deque<std::string>> &matrix)
{
    for (const auto &i : matrix)
    {
        for (const auto &j : i)
        {
            std::cout << j;
        }
        std::cout << std::endl;
    }
}

int findLongest(const std::vector<std::vector<std::string>> &matrix)
{
    int longest = matrix[0].size();
    for (const auto &i : matrix)
    {
        if (i.size() > longest)
            longest = i.size();
    }
    return longest;
}

std::vector<std::deque<std::string>> VStoVDSTransform(const std::vector<std::string> &tp)
{
    std::vector<std::deque<std::string>> res(tp[0].size() / 4 + 1);

    std::string shelper = "";
    for (auto &row : tp)
    {
        int wordcntr = 0;
        for (int i{0}; i < tp[0].size(); i += 4)
        {
            shelper = row.substr(i, 3);
            if (shelper != "   ")
            {
                res[wordcntr].push_back(shelper);
            }
            ++wordcntr;
        }
    }

    return res;
}

std::vector<std::deque<std::string>> processMatrix2(std::vector<std::deque<std::string>> matrix, const std::vector<int> &args, Mode m)
{
    // Initialize counter and temporary deque
    int cntr = args[0];

    // Process based on mode
    if (m == Mode::append)
    {
        // Append elements from source row to destination row
        while (cntr-- > 0)
        {
            matrix[args[2] - 1].push_front(matrix[args[1] - 1].front());
            matrix[args[1] - 1].pop_front();
        }
    }
    else if (m == Mode::keep)
    {
        // Move elements from source row to destination row
        while (cntr-- > 0)
        {
            matrix[args[2] - 1].push_front(matrix[args[1] - 1].front());
            matrix[args[1] - 1].pop_front();
        }
    }

    // Return updated matrix
    return matrix;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    std::ifstream items("inputday5.txt");
    std::string data;

    std::vector<std::deque<std::string>> hardcodedinp{
        {"J", "Z", "G", "V", "T", "D", "B", "N"},
        {"F", "P", "W", "D", "M", "R", "S"},
        {"Z", "S", "R", "C", "V"},
        {"G", "H", "P", "Z", "J", "T", "R"},
        {"F", "Q", "Z", "D", "N", "J", "C", "T"},
        {"M", "F", "S", "G", "W", "P", "V", "N"},
        {"Q", "P", "B", "V", "C", "G"},
        {"N", "P", "B", "Z"},
        {"J", "P", "W"}};

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
            tmpinput.pop_back();
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