#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "Evaluator.hpp"

#include <random>

class Individual {
  public:
    Individual();
    Individual(int size, int lb, int ub);
    Individual(const Individual& other);
    Individual(Individual&& other) noexcept = default;
    ~Individual();

    Individual& operator=(const Individual& other);
    Individual& operator=(Individual&& other) noexcept = default;

    double evaluate(Evaluator& evaluator);
    void mutate(double mutProb, std::mt19937& rng);
    std::pair<Individual, Individual> crossover(const Individual& other, std::mt19937& rng) const;

    [[nodiscard]] double getFitness() const;
    void setFitness(double fit);
    std::vector<int>* getGenotype();

  private:
    void buildRoutes(const int* solution, Evaluator& evaluator);

    std::vector<std::vector<int>> routesBuffer;
    std::vector<int> genotype;
    double fitness;
    int lowerBound;
    int upperBound;
};

#endif // INDIVIDUAL_H
