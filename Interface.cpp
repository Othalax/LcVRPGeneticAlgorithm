#include "Interface.h"

Interface::Interface()
{
}

void Interface::runGeneticAlgorithm()
{
	std::cout << "File path: ";
	std::string filepath;
	std::cin >> filepath;
	// Example file paths:
	//data/lcvrp/Vrp-Set-P/P-n19-k2.lcvrp
	//data/lcvrp/Vrp-Set-P/P-n16-k8.lcvrp
	ProblemLoader problem_loader(filepath);
	ProblemData problem_data = problem_loader.LoadProblem();
	int num_groups = problem_data.getNumGroups();
	Evaluator evaluator(problem_data, num_groups);

	double mutProb, crossProb;
	int popSize, iterations;
	std::cout << "Mutation Probability: ";
	std::cin >> mutProb;
	if (mutProb < 0.0 || mutProb > 1.0) {
		throw std::out_of_range("Mutation probability must be between 0 and 1.");
	}
	std::cout << "Crossover Probability: ";
	std::cin >> crossProb;
	if (crossProb < 0.0 || crossProb > 1.0) {
		throw std::out_of_range("Crossover probability must be between 0 and 1.");
	}
	std::cout << "Population Size: ";
	std::cin >> popSize;
	if (popSize <= 0) {
		throw std::invalid_argument("Population size must be a positive integer.");
	}
	std::cout << "Number of Iterations: ";
	std::cin >> iterations;
	if (iterations <= 0) {
		throw std::invalid_argument("Number of iterations must be a positive integer.");
	}

	GeneticAlgorithm ga(popSize, crossProb, mutProb, evaluator);
	ga.initialize(iterations);
	std::vector<int>* best_solution = ga.getBest();
	double best_fitness = ga.getBestFitness();
	std::cout << "final best fitness: " << best_fitness << std::endl;
	std::cout << "best solution: ";
	for (int gene : *best_solution) {
		std::cout << gene << " ";
	}
}
