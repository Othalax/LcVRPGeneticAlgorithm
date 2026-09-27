#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int popSize, double crossProb, double mutProb,
                                   Evaluator evaluator)
    : popSize(popSize), crossProb(crossProb), mutProb(mutProb), evaluator(std::move(evaluator)),
      iterationsWithoutImprovement(0), rng(std::random_device{}()) {}

void GeneticAlgorithm::initialize(int iterations) {
    population.clear();
    const int size = evaluator.GetSolutionSize();
    const int lb = Evaluator::GetLowerBound();
    const int ub = evaluator.GetUpperBound();

    for (int i = 0; i < popSize; ++i) {
        Individual ind(size, lb, ub);

        std::uniform_int_distribution<int> dist(lb, ub);
        for (int& gene : const_cast<std::vector<int>&>(*ind.getGenotype())) {
            gene = dist(rng);
        }

        ind.evaluate(evaluator);
        population.push_back(ind);

        if (ind.getFitness() < bestIndividual.getFitness()) {
            bestIndividual = ind;
        }
    }

    for (int i = 0; i < iterations; ++i) {
        runIteration();
    }
}

[[nodiscard]] double GeneticAlgorithm::getBestFitness() const {
    return bestIndividual.getFitness();
}

void GeneticAlgorithm::runIteration() {
    std::vector<Individual> nextGen;
    nextGen.reserve(popSize);

    nextGen.push_back(bestIndividual);

    while (nextGen.size() < popSize) {
        const Individual& p1 = population.at(tournament());
        const Individual& p2 = population.at(tournament());

        std::uniform_real_distribution<double> dist(0.0, 1.0);
        if (dist(rng) < crossProb) {
            const std::pair<Individual, Individual> children = p1.crossover(p2, rng);
            nextGen.push_back(children.first);
            if (nextGen.size() < popSize) {
                nextGen.push_back(children.second);
            }
        } else {
            nextGen.push_back(p1);
        }
    }

    bool improved = false;
    for (Individual& ind : nextGen) {
        ind.mutate(mutProb, rng);
        const double f = ind.evaluate(evaluator);

        if (f < bestIndividual.getFitness()) {
            bestIndividual = ind;
            improved = true;
        }
    }

    if (!improved) {
        iterationsWithoutImprovement++;
        if (iterationsWithoutImprovement > 20) {
            diversifyPopulation();
        }
    }
    population = std::move(nextGen);

    if (improved) {
        iterationsWithoutImprovement = 0;
    }
}

std::vector<int>* GeneticAlgorithm::getBest() {
    return bestIndividual.getGenotype();
}

int GeneticAlgorithm::tournament() {
    std::uniform_int_distribution<int> dist(0, static_cast<int>(population.size()) - 1);
    const int b1 = dist(rng);
    const int b2 = dist(rng);
    return (population.at(b1).getFitness() < population.at(b2).getFitness()) ? b1 : b2;
}

void GeneticAlgorithm::diversifyPopulation() {
    const Individual best = bestIndividual;
    population.clear();
    population.push_back(best);

    const int size = evaluator.GetSolutionSize();
    const int lb = Evaluator::GetLowerBound();
    const int ub = evaluator.GetUpperBound();
    std::uniform_int_distribution<int> dist(lb, ub);

    for (int i = 1; i < popSize; ++i) {
        Individual newInd(size, lb, ub);
        for (int& gene : const_cast<std::vector<int>&>(*newInd.getGenotype())) {
            gene = dist(rng);
        }
        newInd.evaluate(evaluator);
        population.push_back(newInd);
        if (newInd.getFitness() < bestIndividual.getFitness()) {
            bestIndividual = newInd;
        }
    }
    iterationsWithoutImprovement = 0;
}
