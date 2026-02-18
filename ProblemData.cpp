#include "ProblemData.hpp"



ProblemData::ProblemData()
    : dimension(0),
    capacity(0),
    edgeWeightType(""),
    depot(1),
    numGroups(0){}

int ProblemData::getDimension() const 
{
    return dimension;
}

int ProblemData::getCapacity() const
{
    return capacity;
}
std::string ProblemData::getEdgeWeightType() const
{
    return edgeWeightType;
}
int ProblemData::getDepot() const
{
    return depot;
}
int ProblemData::getNumCustomers() const
{
    return dimension -1;
}
int ProblemData::getNumGroups() const
{
    return numGroups;
}
const std::vector<int>& ProblemData::getDemands() const
{
    return demands;
}
const std::vector<int>& ProblemData::getPermutation() const
{
    return permutation;
}
void ProblemData::SetDimension(int _dimension)
{
	dimension = _dimension;
    coordinates.resize(dimension);
    demands.resize(dimension);
}
void ProblemData::SetCapacity(int _capacity)
{
    capacity = _capacity;
}
void ProblemData::SetEdgeWeightType(const std::string& _type)
{
    edgeWeightType = _type;
}
void ProblemData::SetDepot(int _depot)
{
    depot = _depot;
}
void ProblemData::SetNumGroups(int _numGroups)
{
    numGroups = _numGroups;
}
void ProblemData::SetCoordinates(const std::vector<Coordinate>& _coordinates)
{
    coordinates = _coordinates;
}
void ProblemData::SetDemands(const std::vector<int>& _demands)
{
    demands = _demands;
}
void ProblemData::SetPermutation(const std::vector<int>& _permutation)
{
    permutation = _permutation;
}
void ProblemData::SetEdgeWeights(const std::vector<std::vector<double>>& _edgeWeights)
{
    edgeWeights = _edgeWeights;
}
double ProblemData::CalculateDistance(int i, int j) const {
    if (i < 0 || i >= dimension || j < 0 || j >= dimension) {
        return std::numeric_limits<double>::infinity();
    }
    if (i == j) 
        return 0.0;
    if (edgeWeightType == "EUC_2D") {
        if (coordinates.size() != dimension) 
        {
            return std::numeric_limits<double>::infinity();
        }
        double dx = coordinates[i].x - coordinates[j].x;
        double dy = coordinates[i].y - coordinates[j].y;
        return sqrt(dx * dx + dy * dy);
    }
    else if (edgeWeightType == "EXPLICIT") {
        if (edgeWeights.empty() || i >= edgeWeights.size() || j >= edgeWeights[i].size()) 
        {
            return std::numeric_limits<double>::infinity();
        }
        if (i > j) 
            return edgeWeights[i][j];
        else 
            return edgeWeights[j][i];
    }
    return std::numeric_limits<double>::infinity();
}

bool ProblemData::isDataIncomplete()
{
    return dimension == 0 || capacity == 0 || edgeWeightType == "" ||
        numGroups == 0 || (coordinates.size() != dimension && edgeWeights.size() != dimension) || demands.empty();
}

