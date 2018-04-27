# Multithreaded BFS
An implementation of parallel BFS in a graph using PThreads and Mutexes

## Motivation:
The BFS is a way to traverse a graph using a FIFO data structure such as a queue. Serial or single-threaded BFS can be too slow for huge graphs (which occur heavily in practice). Hence, Multi-threading can be used to speed up the algorithm by a factor equivalent to the number of physical threads present on a CPU.

## How to Compile:
#### Pre-requisites
- An OS supporting POSIX Threads Library (PThreads)
- Any C++ compiler with support for C++ Standard 11

#### Terminal Command
```terminal
g++ -std=c++11 main.cpp -lpthread
```

#### Output
This command will compile and link for you an executable named a.out in the same directory. Running it is as simple as typing in the following command in the terminal:

```terminal
./a.out
```

## Testing:
The program needs a file named generated.txt in the same directory as itself. This file contains definition of a graph and a few other things. Refer to the following heading for details:

#### Format of Input File
+ The first line contains two integers. Number of Nodes (<b>N</b>) and Number of Edges (<b>E</b>).
+ The next <b>N</b> lines contain a single string on each line representing the data to store at each Node.
+ The next <b>M</b> lines contain a 3 integers (<b>u</b>,<b>v</b>,<b>w</b>) on each line representing a single Edge.
  + <b>u</b> denotes the source of the Edge
  + <b>v</b> denotes the destination of the Edge
  + <b>w</b> denotes the weight of the Edge
+ The next line contains a single integer denoting the number of threads to use.
+ The next line contains a single integer denoting the nodeID to start the search from.
+ The next line contains a single string (without spaces in between) denoting the value to search for.

#### Program Description
The program executes the following steps:
1) Loads the Graph from the generated.txt file and stores it in the Graph Object.
2) Loads the search parameters from generated.txt file.
3) Starts the Parallel BFS on the Graph with the given search parameters.
4) Outputs the result whether the search found a node with matching data or not.