
*This project has been created as part of the 42 curriculum by rexposit.*

# CPP Module 09

`CPP Module 09` is part of the CPP modules of the 42 curriculum. The project focuses on advanced STL container usage, data processing, stack-based expression evaluation and sorting algorithms.

Throughout the module, historical Bitcoin exchange rates are processed using `std::map`, mathematical expressions are evaluated using `std::stack`, and the Ford-Johnson merge-insertion sorting algorithm is implemented independently with `std::vector` and `std::deque`.

---

# Table of Contents

- [Description](#description)
- [Project Rules](#project-rules)
- [Exercises Overview](#exercises-overview)
- [STL Overview](#stl-overview)
- [Implementation](#implementation)
- [Compilation](#compilation)
- [Testing](#testing)
- [Project Structure](#project-structure)
- [What I Learned](#what-i-learned)
- [Author](#author)

---

# Description

CPP Module 09 is divided into three independent exercises, each focusing on a different application of STL containers and algorithms in CPP.

### ex00 — Bitcoin Exchange

Introduces the `BitcoinExchange` class.

The program reads historical Bitcoin exchange rates from a CSV database and processes an input file containing dates and Bitcoin amounts.

It supports:

- loading exchange rates into an ordered map;
- validating dates, including leap years;
- validating numerical values;
- finding the closest available previous exchange rate;
- calculating the corresponding Bitcoin value;
- handling invalid input and missing exchange rates.

This exercise introduces associative containers and efficient ordered searches using `std::map`.

---

### ex01 — Reverse Polish Notation

Introduces the `RPN` class.

The program evaluates mathematical expressions written in Reverse Polish Notation, where operators appear after their operands.

For example:

```text
3 4 + 2 *
```

produces:

```text
14
```

The implementation uses `std::stack<int>` to store operands and supports addition, subtraction, multiplication and division.

It also handles invalid expressions, insufficient operands and division by zero.

This exercise demonstrates how stacks simplify expression evaluation without requiring parentheses or operator precedence rules.

---

### ex02 — PmergeMe

Introduces the `PmergeMe` class.

The program sorts a sequence of positive integers using the Ford-Johnson merge-insertion sorting algorithm.

The algorithm is implemented independently using:

```cpp
std::vector<int>
std::deque<int>
```

It supports:

- positive integer validation;
- integer overflow and duplicate detection;
- recursive group pairing;
- main chain construction;
- Jacobsthal-based insertion ordering;
- partner-bounded binary searches;
- independent processing time measurements.

This exercise combines recursion, container management, algorithm optimization and performance analysis.

---

# Project Rules

The project follows the requirements of CPP Module 09.

- CPP98 standard
- Compilation with:

```bash
-Wall -Wextra -Werror -std=c++98
```

- STL containers and algorithms
- Different containers for each exercise
- Header include guards
- Orthodox Canonical Form for classes
- Exception handling for invalid input
- No external libraries
- Independent Makefiles
- Processing of at least 3,000 integers in `PmergeMe`
- Two independent sorting implementations using different containers

---

# Exercises Overview

| Exercise | Main Concept | STL Container | Executable |
|----------|--------------|---------------|------------|
| ex00 | Historical exchange-rate lookup | `std::map` | `btc` |
| ex01 | Reverse Polish Notation evaluation | `std::stack` | `RPN` |
| ex02 | Ford-Johnson merge-insertion sorting | `std::vector`, `std::deque` | `PmergeMe` |

---

# STL Overview

CPP Module 09 explores how different STL containers are suited to different problems.

```text
                       STL
                        |
           +------------+------------+
           |            |            |
           v            v            v
        std::map     std::stack   Sequence Containers
           |            |            |
           v            v        +----+----+
      Ordered keys     LIFO      |         |
           |          access     v         v
           v             |     vector    deque
     Exchange rate       v       |         |
        lookup          RPN      +----+----+
                   evaluation         |
                                      v
                                 Ford-Johnson
                                   sorting
```

`std::map` stores key-value pairs ordered by key and provides efficient searches.

`std::stack` provides last-in, first-out access, making it suitable for evaluating expressions.

`std::vector` and `std::deque` both support indexed access, but use different internal storage structures.

The final exercise compares their behavior when executing the same sorting algorithm.

---

# Implementation

## Bitcoin Exchange

Exercise 00 implements the `BitcoinExchange` class.

Historical exchange rates are stored using:

```cpp
std::map<std::string, double> database;
```

Each key represents a date in the format:

```text
YYYY-MM-DD
```

Because dates use a fixed year-month-day format, their lexicographical ordering matches their chronological ordering.

The program validates the date format, month lengths and leap years before processing each entry.

---

## Exchange Rate Lookup

The program uses:

```cpp
database.upper_bound(date);
```

This returns an iterator to the first exchange rate whose date is greater than the requested date.

Moving the iterator one position backward selects the latest available exchange rate on or before the requested date.

For example:

```text
Available rates:

2022-01-01 -> 47000
2022-01-05 -> 46000
2022-01-10 -> 42000

Requested date: 2022-01-07

Selected rate: 2022-01-05 -> 46000
```

The requested Bitcoin amount is then multiplied by the selected rate.

If no previous rate exists, the program reports an error.

---

## Reverse Polish Notation

Exercise 01 implements the `RPN` class.

Operands are stored using:

```cpp
std::stack<int> operands;
```

The expression is processed token by token.

When a digit is encountered, it is pushed onto the stack.

When an operator is encountered, two operands are removed, the operation is performed and the result is pushed back.

For example:

```text
Expression: 3 4 + 2 *

Token       Stack
-----       -----
3           [3]
4           [3, 4]
+           [7]
2           [7, 2]
*           [14]
```

The final result is:

```text
14
```

For subtraction and division, operand order matters.

The first popped value is the right operand, while the second is the left operand.

The program verifies that enough operands exist for every operation and that exactly one result remains after evaluating the expression.

---

## Ford-Johnson Merge-Insertion Sort

Exercise 02 implements the Ford-Johnson merge-insertion sorting algorithm.

The algorithm combines recursive pairing with a carefully chosen insertion order designed to minimize the number of comparisons.

Unlike a conventional merge sort, Ford-Johnson constructs an ordered main chain and inserts the remaining elements using bounded binary searches.

The implementation follows these stages:

```text
                Unsorted sequence
                       |
                       v
                  Pair groups
                       |
                       v
                Order each pair
                       |
                       v
               Recursive sorting
                       |
                       v
               Build main chain
                       |
                       v
             Collect pending groups
                       |
                       v
             Jacobsthal insertion
                       |
                       v
                Sorted sequence
```

---

## Recursive Group Pairing

The algorithm starts with groups containing one element.

Adjacent groups are compared using their final elements.

If the first group has a larger final element than the second, the complete groups are swapped.

For example:

```text
Original:

[7] [3] [9] [2] [6] [1]

After pairing:

[3] [7] [2] [9] [1] [6]
```

The algorithm recursively processes groups of increasing size:

```text
1 -> 2 -> 4 -> 8 -> 16 -> ...
```

At each level, groups are compared and exchanged as complete units.

After recursion, the algorithm reconstructs the sequence by inserting pending groups into an ordered main chain.

---

## Main Chain Construction

The algorithm separates groups into two categories:

- main chain groups;
- pending groups.

The main chain contains the groups that establish the initial sorted structure.

Pending groups are inserted afterward.

Each pending group stores its elements and, when applicable, the maximum value of its corresponding partner group.

The implementation uses dedicated structures:

```cpp
struct PendingVectorGroup
{
    std::vector<int> group;
    int              partner;
    bool             has_partner;
};
```

An equivalent structure is implemented for `std::deque`.

The partner relationship determines the upper boundary for inserting a pending group.

Elements that do not form a complete group at the current recursive level are preserved separately.

---

## Jacobsthal Insertion Order

Ford-Johnson does not insert pending groups in simple sequential order.

Instead, it uses an insertion order derived from the Jacobsthal sequence.

The Jacobsthal numbers follow:

```text
J(n) = J(n - 1) + 2 * J(n - 2)
```

Beginning with:

```text
0, 1, 1, 3, 5, 11, 21, 43, ...
```

The insertion batches process pending groups in reverse order within each interval.

Using one-based pending group positions, the order begins:

```text
2, 1, 4, 3, 10, 9, 8, 7, 6, 5, ...
```

This ordering helps control the maximum number of comparisons required during binary insertion.

The implementation calculates the Jacobsthal-based intervals directly rather than storing a separate sequence.

---

## Partner-Bounded Binary Search

Each pending group with a partner is inserted only into the portion of the main chain preceding that partner.

For example:

```text
Main chain:

[2] [5] [8] [12] [17]
             ^
          Partner

Pending group:

[6]

Search range:

[2] [5]

After insertion:

[2] [5] [6] [8] [12] [17]
```

The implementation searches using the final element of each group.

Restricting the search interval reduces comparisons while preserving the ordering established during recursive pairing.

The binary search operates on group positions rather than individual element positions.

---

## Vector and Deque Implementations

The sorting algorithm is implemented separately for:

```cpp
std::vector<int>
std::deque<int>
```

Both implementations contain their own:

```text
swap groups
binary search
insert pending groups
build main chain
recursive Ford-Johnson sort
```

Validated input values are stored independently.

Before each sorting operation, the corresponding container is initialized with the original values.

This ensures both implementations process the same unsorted sequence.

---

## Processing Time Measurements

The program measures processing time independently using:

```cpp
gettimeofday()
```

Each measurement includes:

- initialization of the corresponding sorting container;
- execution of the Ford-Johnson algorithm.

Elapsed time is calculated in microseconds:

```cpp
(end.tv_sec - start.tv_sec) * 1000000.0
    + (end.tv_usec - start.tv_usec)
```

The results are reported separately for `std::vector` and `std::deque`.

Execution times depend on the input size, container implementation, hardware and system conditions.

---

# Compilation

Each exercise is independent.

Compile any exercise by entering its directory.

### ex00 — Bitcoin Exchange

```bash
cd ex00
make
./btc input.txt
```

The program requires a `data.csv` file containing historical exchange rates in the expected format.

### ex01 — Reverse Polish Notation

```bash
cd ex01
make
./RPN "3 4 + 2 *"
```

Expected output:

```text
14
```

### ex02 — PmergeMe

```bash
cd ex02
make
./PmergeMe 1 3 4 7 5
```

Example output:

```text
Before: 1 3 4 7 5
After: 1 3 4 5 7
Time to process a range of 5 elements with std::vector --> 7 us
Time to process a range of 5 elements with std::deque --> 12 us
```

Processing times vary between executions.

Available Makefile rules:

```bash
make
make clean
make fclean
make re
```

---

# Testing

The exercises are tested with valid inputs, invalid inputs and boundary cases.

## Bitcoin Exchange Tests

The tests cover:

- valid and invalid dates;
- leap years and month boundaries;
- exact exchange rate matches;
- dates between database entries;
- negative or oversized values;
- malformed input lines;
- missing files and unavailable rates.

## RPN Tests

The tests cover:

- all four arithmetic operators;
- chained expressions;
- operand order;
- insufficient or extra operands;
- division by zero;
- invalid characters and malformed expressions.

Example:

```bash
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
```

Expected output:

```text
42
```

## PmergeMe Tests

The sorting implementations were tested with:

- already sorted and reverse-sorted sequences;
- odd and even sequence lengths;
- exhaustive small permutations;
- random and adversarial inputs;
- positive integers near `INT_MAX`;
- duplicate and invalid arguments;
- sequences containing 3,000 and 5,000 elements.

An automated Python stress tester was used during development to verify sorting correctness across thousands of cases.

Both container implementations were checked independently.

Memory usage can also be checked with:

```bash
valgrind --leak-check=full ./PmergeMe 5 4 3 2 1
```

---

# Project Structure

```text
42_cpp_module_09/
│
├── ex00/
│   ├── BitcoinExchange.hpp
│   ├── BitcoinExchange.cpp
│   ├── main.cpp
│   └── Makefile
│
├── ex01/
│   ├── RPN.hpp
│   ├── RPN.cpp
│   ├── main.cpp
│   └── Makefile
│
├── ex02/
│   ├── PmergeMe.hpp
│   ├── PmergeMe.cpp
│   ├── main.cpp
│   └── Makefile
│
└── README.md
```

---

# What I Learned

Through this module I strengthened my understanding of:

- STL container selection;
- ordered associative containers;
- `std::map` and `upper_bound`;
- file parsing and date validation;
- stack-based expression evaluation;
- Reverse Polish Notation;
- recursive sorting algorithms;
- Ford-Johnson merge-insertion sort;
- recursive group pairing;
- main chain construction;
- Jacobsthal insertion ordering;
- partner-bounded binary searches;
- implementing algorithms with different containers;
- comparing `std::vector` and `std::deque`;
- measuring execution time in microseconds;
- stress testing with exhaustive permutations and large random datasets;
- exception handling and integer overflow validation.

CPP Module 09 demonstrates how selecting appropriate STL containers and understanding their behavior can simplify complex problems.

The Ford-Johnson exercise also provided practical experience implementing and validating a comparison-efficient sorting algorithm, combining recursion, mathematical insertion sequences and container-specific operations.

---

# Author

**Raúl Expósito Campos**

42 Madrid Student

GitHub: https://github.com/raulrecrec
