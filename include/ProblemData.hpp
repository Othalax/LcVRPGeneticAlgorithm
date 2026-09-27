#ifndef PROBLEMDATA_HPP
#define PROBLEMDATA_HPP

#include <cmath>
#include <string>
#include <vector>

constexpr unsigned int RANDOM_PERMUTATION_SEED = 42;
struct Coordinate {
    double x;
    double y;

    Coordinate() : x(0.0), y(0.0) {}
    Coordinate(double x, double y) : x(x), y(y) {}
};

class ProblemData {
  public:
    ProblemData();

    [[nodiscard]] int getDimension() const;
    [[nodiscard]] int getCapacity() const;
    [[nodiscard]] std::string getEdgeWeightType() const;
    [[nodiscard]] int getDepot() const;
    [[nodiscard]] int getNumCustomers() const;
    [[nodiscard]] int getNumGroups() const;
    [[nodiscard]] const std::vector<int>& getDemands() const;
    [[nodiscard]] const std::vector<int>& getPermutation() const;

    void SetDimension(int _dimension);
    void SetCapacity(int _capacity);
    void SetEdgeWeightType(const std::string& _type);
    void SetDepot(int _depot);
    void SetNumGroups(int _numGroups);
    void SetCoordinates(const std::vector<Coordinate>& _coordinates);
    void SetDemands(const std::vector<int>& _demands);
    void SetPermutation(const std::vector<int>& _permutation);
    void SetEdgeWeights(const std::vector<std::vector<double>>& _edgeWeights);

    [[nodiscard]] double CalculateDistance(int i, int j) const;
    bool isDataIncomplete();

  private:
    std::string name;
    int dimension;
    int capacity;
    std::string edgeWeightType;
    int depot;
    int numGroups;

    std::vector<Coordinate> coordinates;
    std::vector<int> demands;
    std::vector<int> permutation;
    std::vector<std::vector<double>> edgeWeights;
};

#endif // PROBLEMDATA_HPP
