#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int popSize, double crossProb, double mutProb, Evaluator& evaluator)
    : popSize(popSize), crossProb(crossProb), mutProb(mutProb), evaluator(evaluator),
    bestIndividual(), iterationsWithoutImprovement(0), rng(std::random_device{}()) {
}

void GeneticAlgorithm::initialize(int iterations)
{
    population.clear();
    int size = evaluator.GetSolutionSize();
    int lb = evaluator.GetLowerBound();
    int ub = evaluator.GetUpperBound();

    for (int i = 0; i < popSize; ++i) {
        Individual ind(size, lb, ub);

        std::uniform_int_distribution<int> dist(lb, ub);
        for (int& gene : const_cast<std::vector<int>&>(*ind.getGenotype())) 
        {
            gene = dist(rng);
        }

        ind.evaluate(evaluator);
        population.push_back(ind);

        if(ind.getFitness() < bestIndividual.getFitness())
			bestIndividual = ind;
    }

    for(int i = 0; i < iterations; ++i)
		runIteration();
}

double GeneticAlgorithm::getBestFitness() const
{
    return bestIndividual.getFitness();
}

void GeneticAlgorithm::runIteration() {
    std::vector<Individual> nextGen;
    nextGen.reserve(popSize);

    nextGen.push_back(bestIndividual);

    while (nextGen.size() < popSize) {
        Individual& p1 = population[tournament()];
        Individual& p2 = population[tournament()];

        std::uniform_real_distribution<double> dist(0.0, 1.0);
        if (dist(rng) < crossProb)
        {
            std::pair<Individual*, Individual*> children = p1.crossover(p2, rng);
            nextGen.push_back(*children.first);
            if (nextGen.size() < popSize)
                nextGen.push_back(*children.second);

            delete children.first;
            delete children.second;
        }
        else
        {
            nextGen.push_back(p1);
        }
    }

    bool improved = false;
    for (Individual& ind : nextGen) {
        ind.mutate(mutProb, rng);
        double f = ind.evaluate(evaluator);

        if (f < bestIndividual.getFitness()) {
            bestIndividual = ind;
            improved = true;
        }
    }

    if (!improved) {
        iterationsWithoutImprovement++;
        if (iterationsWithoutImprovement > 20) 
        {
			diversifyPopulation();
        }
    }
    population = std::move(nextGen);

    if (improved)
        iterationsWithoutImprovement = 0;
}

std::vector<int>* GeneticAlgorithm::getBest()
{
    return bestIndividual.getGenotype();
}

int GeneticAlgorithm::tournament() {
    std::uniform_int_distribution<int> dist(0, (int)population.size() - 1);
    int b1 = dist(rng), b2 = dist(rng);
    return (population[b1].getFitness() < population[b2].getFitness()) ? b1 : b2;
}

void GeneticAlgorithm::diversifyPopulation()
{
    Individual best = bestIndividual;
    population.clear();
    population.push_back(best);

    int size = evaluator.GetSolutionSize();
    int lb = evaluator.GetLowerBound();
    int ub = evaluator.GetUpperBound();
    std::uniform_int_distribution<int> dist(lb, ub);

    for (int i = 1; i < popSize; ++i) {
        Individual newInd(size, lb, ub);
        for (int& gene : const_cast<std::vector<int>&>(*newInd.getGenotype())) {
            gene = dist(rng);
        }
        newInd.evaluate(evaluator);
        population.push_back(newInd);
        if (newInd.getFitness() < bestIndividual.getFitness())
            bestIndividual = newInd;
    }
    iterationsWithoutImprovement = 0;
}

