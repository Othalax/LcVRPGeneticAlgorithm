#ifndef INTERFACE_H
#define INTERFACE_H

#include "GeneticAlgorithm.h"
#include "ProblemLoader.hpp"

class Interface {
  public:
    Interface() = default;

    static void runGeneticAlgorithm();
};

#endif // INTERFACE_H