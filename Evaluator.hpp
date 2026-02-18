#pragma once

#include "ProblemData.hpp"
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <iostream>



class Evaluator {
	public:
		Evaluator(const ProblemData& problem_data, int num_groups);

		double Evaluate(std::vector<std::vector<int>> fenotype);

		int GetSolutionSize() const { return numCustomers; }
		int GetLowerBound() const { return 0; } 
		int GetUpperBound() const { return numGroups - 1; }
		int GetNumGroups() const { return numGroups; }
		std::vector<int> getPermutation() const { return problemData.getPermutation(); }

	private:
		const ProblemData& problemData;
		int numGroups;
		int numCustomers;
		std::vector<std::vector<int>> routesBuffer;

		double CalculateRouteCost(const std::vector<int>& route);
		bool ValidateConstraints();
};

