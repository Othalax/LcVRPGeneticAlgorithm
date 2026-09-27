# LCVRP Genetic Algorithm Solver

## Table of contents

- [Description](#description)
- [Technologies](#technologies)
- [Installation and build](#installation-and-build)
- [Project structure](#project-structure)

## Description

A command-line tool designed to solve the **Limited Capacitated Vehicle Routing Problem (LcVRP)** using a Genetic Algorithm. This project optimizes delivery routes by simulating evolutionary processes—such as tournament selection, single-point crossover, and uniform mutation — to minimize total travel distance while respecting vehicle capacity constraints. It supports standard datasets and calculates distances using both Euclidean (`EUC_2D`) and explicit weight matrices.


## Technologies

- **C++**: Core logic and object-oriented architecture.
- **STL (Standard Template Library)**: Utilized for data management via `std::vector` and `std::pair`.
- **Mersenne Twister (MT19937)**: High-quality pseudo-random number generation for genetic diversity and population initialization.

## Installation and build

The project was made using C++ 11. Example files with problem data are located in `data\lcvrp` folder.


### Build

```bash
cmake -B build -G "Ninja"
cmake --build build
```

### Run

```bash
.\build\LcVRPGeneticAlgorithm.exe
```

## Project structure

```bash
├── include/
│   ├── Interface.h          # I/O: header for managing user parameters and program flow
│   ├── ProblemLoader.hpp    # Parser: header for loading .lcvrp files and generating initial permutations
│   ├── ProblemData.hpp      # Data Model: header for distance calculations and constraints logic
│   ├── GeneticAlgorithm.h   # Engine: header for population loop and stagnation handling
│   ├── Individual.h         # Phenotype: header for solution representation, crossover, and mutation
│   └── Evaluator.hpp        # Genotype: header for route construction and capacity validation
└── src/
    ├── main.cpp             # Entry point: initializes the GA execution
    ├── Interface.cpp        # I/O: manages user parameters and program flow implementation
    ├── ProblemLoader.cpp    # Parser: reads .lcvrp files and generates initial permutations
    ├── ProblemData.cpp      # Data Model: handles distance calculations and constraints implementation
    ├── GeneticAlgorithm.cpp # Engine: manages the population loop and stagnation logic implementation
    ├── Individual.cpp       # Phenotype: handles crossover and mutation operations implementation
    └── Evaluator.cpp        # Genotype: builds routes and validates capacity constraints implementation
```