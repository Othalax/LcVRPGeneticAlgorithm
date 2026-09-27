#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP

#include "ProblemData.hpp"

#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <stdexcept>

class Evaluator {
  public:
    Evaluator(const ProblemData& problem_data, int num_groups);

    double Evaluate(std::vector<std::vector<int>> fenotype);

    [[nodiscard]] int GetSolutionSize() const {
        return numCustomers;
    }
    [[nodiscard]] static int GetLowerBound() {
        return 0;
    }
    [[nodiscard]] int GetUpperBound() const {
        return numGroups - 1;
    }
    [[nodiscard]] int GetNumGroups() const {
        return numGroups;
    }
    [[nodiscard]] std::vector<int> getPermutation() const {
        return problemData.getPermutation();
    }

  private:
    ProblemData problemData;
    int numGroups;
    int numCustomers;
    std::vector<std::vector<int>> routesBuffer;

    double CalculateRouteCost(const std::vector<int>& route);
    bool ValidateConstraints();
};

#endif // EVALUATOR_HPP
