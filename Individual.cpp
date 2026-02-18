#include "Individual.h"


Individual::Individual() 
    : fitness(std::numeric_limits<double>::infinity()), lowerBound(0), upperBound(0) {}

Individual::Individual(int size, int lb, int ub)
    : genotype(size), fitness(-1.0), lowerBound(lb), upperBound(ub) {}

Individual::Individual(const Individual& other)
    : genotype(other.genotype), fitness(other.fitness),
    lowerBound(other.lowerBound), upperBound(other.upperBound) {}

Individual& Individual::operator=(const Individual& other)
{
    if (this != &other) {
        genotype = other.genotype;
        fitness = other.fitness;
        lowerBound = other.lowerBound;
        upperBound = other.upperBound;
    }
    return *this;
}

double Individual::evaluate(Evaluator& evaluator) 
{
    routesBuffer.resize(evaluator.GetNumGroups());
	buildRoutes(genotype.data(), evaluator);
    fitness = evaluator.Evaluate(routesBuffer);
    return fitness;
}

void Individual::buildRoutes(const int* solution, Evaluator& evaluator) {
    for (std::vector<int>& route : routesBuffer) {
        route.clear();
    }

    const std::vector<int>& permutation = evaluator.getPermutation();

    for (int customer_id : permutation) {
        int sol_idx = customer_id - 2;

        if (sol_idx >= 0 && sol_idx < evaluator.GetSolutionSize()) {
            int group = solution[sol_idx];
            routesBuffer[group].push_back(customer_id);
        }
    }
}

void Individual::mutate(double mutProb, std::mt19937& rng) {
    std::uniform_real_distribution<double> probDist(0.0, 1.0);
    std::uniform_int_distribution<int> valDist(lowerBound, upperBound);

    for (int& gene : genotype) 
    {
        if (probDist(rng) < mutProb) 
        {
            gene = valDist(rng);
        }
    }
}

std::pair<Individual*, Individual*> Individual::crossover(const Individual& other, std::mt19937& rng) const 
{
    std::uniform_int_distribution<size_t> dist(1, genotype.size() - 1);
    size_t splitPoint = dist(rng);

    Individual* child1 = new Individual(genotype.size(), lowerBound, upperBound);
    Individual* child2 = new Individual(genotype.size(), lowerBound, upperBound);

    for (size_t i = 0; i < genotype.size(); ++i) 
    {
        if (i < splitPoint) 
        {
            child1->genotype[i] = this->genotype[i];
            child2->genotype[i] = other.genotype[i];
        }
        else 
        {
            child1->genotype[i] = other.genotype[i];
            child2->genotype[i] = this->genotype[i];
        }
    }
    return { child1, child2 };
}

double Individual::getFitness() const
{
    return fitness;
}

void Individual::setFitness(double fit)
{
	fitness = fit;
}

std::vector<int>* Individual::getGenotype()
{
	return &genotype;
}
