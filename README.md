# AOC2022
Repo for the Advent of Code 2022
#### Goals:
* Finally start utilizing github
* Practice Git
* Practice different languages
* Take part of the Faculty Discord AOC event
* Slack off during university

## Day 1
https://adventofcode.com/2022/day/1
Solution in D1 folder
#### Requirements:
* Get a list of numbers
* T1 Find the maximum
* T2 Find the top 3

#### Approach:
* Copy data from AOC day/1/input page
* Read data
* If empty line found, push the current sum into vector (initialized with 3 elements)
* Sort vector descending
* Remove last element
* After reading of data has been completed print sum and maximum

#### Possible optimizations/improvements
* Add a check if vector is of size 3, if less, dont remove last element, if more, remove until of size 3
* Import data directly from web (IDK if possible with c++, in python probably with bs4)

#### Day 1 Wrap Up
* Practiced C++ for the first time in a long while
* Tried to use modern C++ techniques (`std::reduce`) 
* Took some time for adjustment
* Considering wether to use Python or JS for some future tasks
