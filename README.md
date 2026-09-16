# elevator-optimization-4-algorithms
C project for solving an elevator stop optimization problem using recursion, brute force, memoization, and dynamic programming.

## Overview
This repository contains an academic project for the course Introduction to Programming from the first semester.
The project focuses on finding the optimal elevator stops in order to minimize the total number of floors passengers need to walk.
Each passenger has a destination floor, while the elevator can make a limited number of stops. The goal is to determine the stop configuration that minimizes the total walking cost.

## Project
The problem is solved using four different algorithmic approaches:
- Recursive solution (liftrec)
- Brute-force solution (liftbf)
- Recursive solution with memoization (liftmem)
- Iterative dynamic programming solution (liftdp)
The project also includes a helper function fw() used to calculate the walking cost between two elevator stops.
Each algorithm is implemented in a separate source file.

## Assignment Specification
The elevator starts from the ground floor and can make at most `nst` stops.
There are `nrid` passengers, and each passenger has a destination floor stored in the array `dests`.Each passenger exits the elevator at the stop that is closest to their destination and then walks the remaining distance using the stairs.

Moving one floor using the stairs has a cost of `1`.The goal is to determine the elevator stops that minimize the total walking cost of all passengers.

The highest passenger destination is denoted as `nfl`.There is no need for the elevator to stop above `nfl`, since a stop above the highest destination cannot improve the solution.

The assignment also allows solutions with fewer than `nst` actual stops. In such cases, additional stops can conceptually be represented as stops at floor `0`.

## Cost Function

The assignment defines the function:

```text
fw(a, b)
```
`fw(a, b)` represents the total number of floors that passengers need to walk when their destination floors are above floor `a` and up to floor `b`. Each passenger uses whichever of the two stops, `a` or `b`, is closer to their destination.

Special cases:
- `a = 0` when `b` is the first elevator stop
- `b = ∞` when `a` is the final elevator stop

## Dynamic Programming Relation
The assignment defines:
```text
M(i, j)
```
where `M(i, j)` is the minimum total walking cost when the elevator makes exactly `i` stops and the highest stop is floor `j`.

### Base Case
If the elevator makes no stops:
```text
M(0, j) = fw(0, ∞)
```
In this case, all passengers walk from the ground floor to their destinations.

### Recursive Relation
For `i >= 1`:
```text
M(i, j) = min over k = 0..j { M(i-1, k)- fw(k, ∞) + fw(k, j)+ fw(j, ∞)}
```
When a new stop at floor `j` is added after a previous stop at floor `k`, the old walking cost for passengers above `k` is replaced by a new cost that takes the additional stop into account.

### Final Optimal Cost
The final minimum cost is:
```text
MinCost = min over j = 0..nfl { M(nst, j) }
```
The corresponding value of `j` gives the last stop of the optimal solution.

## Implementations
All four implementations use the same function prototype:
```c
int solve(int nrid, int nst, int *dests);
```
where:
- `nrid` is the number of passengers
- `nst` is the maximum number of elevator stops
- `dests` contains the destination floor of each passenger

Each implementation of `solve()` is placed in a separate source file.

### Recursive — `liftrec`
Uses the recursive relation directly to calculate the minimum walking cost.
It prints:
- the last elevator stop of the optimal solution
- the minimum total walking cost

### Brute Force — `liftbf`
Examines possible combinations of elevator stops and calculates the cost of each possible solution.
It prints:
- all elevator stops of the optimal solution
- the minimum total walking cost

### Recursive with Memoization — `liftmem`
Uses the recursive relation while storing previously calculated values of `M(i, j)`, so that the same states are not recalculated multiple times.
It prints:
- the last elevator stop of the optimal solution
- the minimum total walking cost

### Dynamic Programming — `liftdp`
Uses a bottom-up dynamic programming approach to calculate the values of `M(i, j)` iteratively.
It prints:
- the dynamic programming table
- all elevator stops of the optimal solution
- the minimum total walking cost

## Input
All implementations read the same input directly from standard input.
The input contains:
1. The number of passengers (`nrid`)
2. The maximum number of elevator stops (`nst`)
3. The destination floor of each passenger (`dests`)

Example:
```text
5 2
11 2 7 13 7
```

This represents:
- `5` passengers
- at most `2` elevator stops
- destination floors: `11, 2, 7, 13, 7`

## Example Output

### Recursive
```text
Last stop at floor 11
Cost is: 4
```

### Brute Force

```text
Lift stops are: 7 11
Cost is: 4
```

### Recursive with Memoization

```text
Last stop at floor 11
Cost is: 4
```

### Dynamic Programming
The dynamic programming implementation first prints the calculated `M(i, j)` table and then displays:
```text
Lift stops are: 7 11
Cost is: 4
```

## How to Compile and Run

### Compile

Compile the common source files:
```bash
gcc -c lift.c
gcc -c fw.c
```

Compile each algorithm implementation:
```bash
gcc -c liftrec.c
gcc -c liftbf.c
gcc -c liftmem.c
gcc -c liftdp.c
```

Create the executables:
```bash
gcc -o liftrec lift.o liftrec.o fw.o
gcc -o liftbf lift.o liftbf.o
gcc -o liftmem lift.o liftmem.o fw.o
gcc -o liftdp lift.o liftdp.o fw.o
```

### Run
Run one of the four implementations:
```bash
./liftrec
./liftbf
./liftmem
./liftdp
```

Then provide the input through standard input.
Example:
```text
5 2
11 2 7 13 7
```

## Tools and Technologies
- C
- GCC
- Recursion
- Brute Force
- Memoization
- Dynamic Programming
- Modular Programming
- Header Files
- Object File Linking

## What I Practiced
- Solving an optimization problem in C
- Implementing recursive algorithms
- Implementing brute-force search
- Improving recursive solutions using memoization
- Implementing bottom-up dynamic programming
- Comparing different algorithmic approaches
- Working with multidimensional arrays
- Breaking a C program into multiple source files
- Using header files and function prototypes
- Compiling source files separately
- Linking multiple object files into executables
- Reusing shared helper functions across different implementations
- Understanding performance differences between different algorithmic approaches

## Project Structure
- ├── README.md
- ├── src/
- ├──├── lift.c
- ├──├── liftrec.c
- ├──├── liftbf.c
- ├──├── liftmem.c
- ├──├── liftdp.c
- ├──├── fw.c
- ├──├── fw.h
- ├──└── solve.h
