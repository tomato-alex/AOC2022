#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <utility>

void xyz(std::string data, int &score, std::map<char, int> scores)
{
    if (data.at(0) - static_cast<char>(data.at(2) - 23) == -1 || data.at(0) - static_cast<char>(data.at(2) - 23) == 2)
    {
        score += 6;
    }
    else if (data.at(0) == static_cast<char>(data.at(2) - 23))
    {
        score += 3;
    }
    score += scores.at(static_cast<char>(data.at(2) - 23));
}
void wld(std::string data, int &score, std::map<char, int> scores)
{
    char play = ' ';
    switch (data.at(2))
    {
    case 'X':
        play = data.at(0) + (data.at(0) == 'A' ? 2 : -1);
        break;
    case 'Y':
        play = data.at(0);
        score += 3;
        break;
    case 'Z':
        play = data.at(0) + (data.at(0) == 'C' ? -2 : 1);
        score += 6;
        break;
    }
    score += scores.at(play);
}

int main()
{
    std::map<char, int> scores{{'A', 1}, {'B', 2}, {'C', 3}};
    std::ifstream played("day2input.txt");
    int score_xyz = 0;
    int score_wld = 0;
    std::string data;
    char play;
    while (getline(played, data))
    {
        xyz(data, score_xyz, scores);
        wld(data, score_wld, scores);
    }
    std::cout << score_xyz << " " << score_wld;
    return 0;
}