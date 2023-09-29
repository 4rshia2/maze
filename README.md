# Maze
## Overview
This C++ program solves a maze using a B-Tree data structure to find the path with the lowest penalty. It takes an input matrix representing the maze, where 0 indicates no path and -1 in the output matrix represents the path to the exit.
# Getting Started
To run this program, you'll need a C++ compiler. Follow these steps to get started:

Clone this repository to your local machine.
```
git clone https://github.com/4rshia2/maze.git
```
Compile the code.
```
g++ -o maze_solver maze_solver.cpp
```
Run the program with the desired input.
```
./maze_solver
```
## Usage
1.When running the program, you will be prompted to enter the number of rows (m) and columns (n) for the maze.

2.Then, you will be asked to input the maze. Enter the penalty values for each path in the maze, where 0 indicates no path.

3.The program will find the path with the lowest penalty using Dijkstra's algorithm and B-Tree data structure.

4.The output will be displayed, showing the path to the exit with -1 values and the maze matrix with the lowest penalty path.

## Algorithm
The program uses Dijkstra's algorithm to find the lowest penalty path in the maze. It constructs an adjacency matrix from the maze, creates a B-Tree to manage the distances, and iteratively finds the optimal path.
