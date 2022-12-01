# AOC2022
Repo for the Advent of Code 2022

# Day 1
https://adventofcode.com/2022/day/1
Solution in D1 folder
### Requirements:
* Get a list of numbers
* T1 Find the maximum
* T2 Find the top 3

### Approach:
* Copy data from AOC day/1/input page
* Read data
* If empty line found, push the current sum into vector (initialized with 3 elements)
* Sort vector descending
* Remove last element
* After reading of data has been completed print sum and maximum

### Possible optimizations/improvements
* Add a check if vector is of size 3, if less, dont remove last element, if more, remove until of size 3
* Import data directly from web (IDK if possible with c++, in python probably with bs4)
