# AOC2022

Repo for the Advent of Code 2022

#### Goals:

- Finally start utilizing github
- Practice Git
- Practice different languages
- Take part of the Faculty Discord AOC event
- Slack off during university

## Day 1

https://adventofcode.com/2022/day/1
Solution in D1 folder

#### Requirements:

- Get a list of numbers
- T1 Find the maximum
- T2 Find the top 3

#### Approach:

- Copy data from AOC day/1/input page
- Read data
- If empty line found, push the current sum into vector (initialized with 3 elements)
- Sort vector descending
- Remove last element
- After reading of data has been completed print sum and maximum

#### Possible optimizations/improvements

- Add a check if vector is of size 3, if less, dont remove last element, if more, remove until of size 3
- Import data directly from web (IDK if possible with c++, in python probably with bs4)

#### Day 1 Wrap Up

- Practiced C++ for the first time in a long while
- Tried to use modern C++ techniques (`std::reduce`)
- Took some time for adjustment
- Considering wether to use Python or JS for some future tasks

## Day 2

https://adventofcode.com/2022/day/2
Solution in D2 folder

#### Requirements:

- Get a list of inputs
- T1 compare input 1 vs input 2
- T2 create what to play depends on input 2 in relation with input 1

#### Approach:

- Copy data from AOC day/2/input page
- Read data
- For T1
  - Transform input 2 to match input 1
  - Compare input 1 and input 2
  - Compute score
- For T2
  - Check input 2
  - Create an input
  - Compute score

#### Possible optimizations/improvements

This is very low level C++, introduce abstractions but it doesn't make sense imho

#### Day 2 Wrap Up

- Practiced `std::map`
- Early morning logic ain't for me
- Made mistakes because i didn't spend time thinking beforehand
- `std::pair` threw a weird error trying to convert an rvalue to an lvalue whereas it wasn't supposed to do that in the first place, so i need to investigate

## Day 3

https://adventofcode.com/2022/day/3
Solution in D3 folder

#### Requirements:

- T1
  - Split string into substrings
  - Compare for equal character
  - Convert equal character to num (priority)
  - Sum up all priorities
- T2
  - Divide dataset into sets of 3 strings
  - Find matching char between strings of that set
  - Convert char to num (priority)
  - Sum up all priorities

#### Approach:

- 2 Functions
- Divide string using `std::string::substr()`
- Loop through first substring
- If match convert char to priority and break loop
- Sum up

#### Possible optimizations/improvements

- Pass the entire dataset to the function
- Redo the substr to be faster
- Divide the functions into more subfunctions to remove code repetition

#### Day 3 Wrap Up

- Practiced `std::string` methods and working with strings
- Today I found the solution relatively fast, but a bug was keeping me back
- Thinking before doing saved me a lot of time

## Day 4

https://adventofcode.com/2022/day/4
Solution in D4 folder

#### Requirements:

- Process list of data
- Separate ranges
- Compare ranges to see if they are
  - Partially Contained
  - Fully Contained

#### Approach:

- Read data, remove all unnecessary punctuation
- Convert each row to `std::stringstream`
- Input all the numbers into a data structure (in my case `std::vector`)
- Depending on the `Mode` (`Mode::partial` or `Mode::full`) check if either list is fully or partially contained

#### Possible optimizations/improvements

- Idk if stringstream is optimal
- A lot of variables are used, maybe reduce amount?

#### Day 4 Wrap Up

- Used Enums
- Divided code into more functions to reduce repetition
- Completed challenge relatively quickly
- Logical thinking is getting better
- Wrote down approach on paper before coding it
- Have a reason to wake up and not stare at my phone for half an hour before I get up

## Day <x>

https://adventofcode.com/2022/day/<x>
Solution in D<x> folder

#### Requirements:

- list

#### Approach:

- list

#### Possible optimizations/improvements

- list

#### Day <x> Wrap Up

- list
