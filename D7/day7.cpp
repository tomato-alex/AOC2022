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
#include <unordered_map>

class DirNode
{
    std::map<std::string, DirNode *> subdirs;
    DirNode *parentdir = nullptr;
    std::uint64_t folderFileSize{0};
    std::string dirname;
    bool isDir;

public:
    DirNode(std::string name, bool dir) : dirname{name}, isDir{dir} {}

    void addSubdir(const std::string &name)
    {
        for (auto &sd : subdirs)
        {
            if (sd.first == name)
            {
                return;
            }
        }
        DirNode *tmp = new DirNode(name, true);
        tmp->parentdir = this;
        subdirs.insert(std::make_pair(name, tmp));
    }

    void addFile(std::uint64_t f)
    {
        folderFileSize += f;
    }

    std::string getName() const
    {
        return this->dirname;
    }
    DirNode *getParent() const
    {
        return this->parentdir;
    }
    std::uint64_t getFFS() const
    {
        return this->folderFileSize;
    }
    std::map<std::string, DirNode *> getSubdir() const
    {
        return this->subdirs;
    }
    std::uint64_t getTFS() const
    {
        std::uint64_t total{this->getFFS()};
        for (const auto &sd : this->getSubdir())
        {
            total += sd.second->getTFS();
        }
        return total;
    }
};

void printTree(DirNode *dir, const std::string &start, std::uint64_t &total)
{
    for (const auto &sdir : dir->getSubdir())
    {
        std::uint64_t TFS = sdir.second->getTFS();
        // std::cout << start << "Directory: " << sdir.first << " Size: " << TFS << " Subdir:\n";
        if (TFS <= 100000)
        {
            total += TFS;
        }
        printTree(sdir.second, start + "--", total);
    }
}

void getmindel(DirNode *dir, const std::uint64_t currmin, std::uint64_t &max)
{
    for (const auto &sdir : dir->getSubdir())
    {
        std::uint64_t TFS = sdir.second->getTFS();

        if (TFS >= currmin && TFS <= max)
        {
            max = TFS;
        }

        getmindel(sdir.second, currmin, max);
    }
}

int main()
{
    std::ifstream items("inputday7.txt");
    std::string data;
    std::vector<std::string> input;

    while (getline(items, data))
    {
        input.push_back(data);
    }
    input.push_back("$ cd /");

    auto start = std::chrono::high_resolution_clock::now();

    DirNode *dir = new DirNode("/", true);

    for (const auto &line : input)
    {
        std::stringstream ss{line};
        std::string ssshelper;
        std::uint64_t ssihelper;

        if (line[0] == '$')
        {
            ss >> ssshelper;
            ss >> ssshelper;
            if (ssshelper == "cd")
            {
                // std::cout << " SubCommand: " << ssshelper;
                ss >> ssshelper;
                // std::cout << " arg: " << ssshelper;
                if (ssshelper == "/")
                {
                    while (dir->getParent() != nullptr)
                    {
                        dir = dir->getParent();
                    }
                }
                else if (ssshelper == "..")
                {
                    dir = dir->getParent();
                }
                else if (dir->getSubdir().count(ssshelper))
                {
                    dir = dir->getSubdir().at(ssshelper);
                }
                // std::cout << std::endl;
            }
            continue;
        }
        else if (line.substr(0, 3) == "dir")
        {
            ss >> ssshelper;
            ss >> ssshelper;
            dir->addSubdir(ssshelper);
            continue;
        }
        if (ss >> ssihelper)
        {
            // std::cout << dir->getName();
            // std::cout << dir->getFFS() << std::endl;
            dir->addFile(ssihelper);
            // std::cout << "File added size: " << ssihelper << '\n';
            continue;
        }
    }

    std::uint64_t total{0};
    printTree(dir, "", total);
    std::cout << total << std::endl;
    std::uint64_t max = dir->getTFS();
    getmindel(dir, dir->getTFS() - 40000000, max);
    std::cout << max << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: "
              << duration.count() << " microseconds" << std::endl;

    return 0;
}