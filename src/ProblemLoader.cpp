#include "ProblemLoader.hpp"

ProblemLoader::ProblemLoader(std::string filepath)
    : filepath(std::move(filepath)), useRandomPerm(true) {}

ProblemData ProblemLoader::LoadProblem() {
    ProblemData problem_data;

    ParseLcVrpFile(filepath, problem_data);

    if (useRandomPerm) {
        const int num_customers = problem_data.getNumCustomers();
        std::vector<int> permutation;
        permutation.reserve(num_customers);

        for (int i = 2; i <= num_customers + 1; ++i) {
            permutation.push_back(i);
        }

        std::mt19937 gen(RANDOM_PERMUTATION_SEED);
        shuffle(permutation.begin(), permutation.end(), gen);
        problem_data.SetPermutation(permutation);
    }

    return problem_data;
}

void ProblemLoader::ParseLcVrpFile(const std::string& file_path, ProblemData& problem_data) {
    std::ifstream file;
    try {
        file.open(file_path);
        if (!file.is_open()) {
            throw std::invalid_argument("Error: Cannot open file: " + file_path);
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << '\n';
        exit(1);
    }
    std::string token;
    std::string colon;

    while (file >> token) {
        if (token == "DIMENSION") {
            int dim{};
            file >> colon >> dim;
            problem_data.SetDimension(dim);
        } else if (token == "CAPACITY") {
            int cap{};
            file >> colon >> cap;
            problem_data.SetCapacity(cap);
        } else if (token == "EDGE_WEIGHT_TYPE") {
            std::string type;
            file >> colon >> type;
            problem_data.SetEdgeWeightType(type);
        } else if (token == "NUM_GROUPS") {
            int groups{};
            file >> colon >> groups;
            problem_data.SetNumGroups(groups);
        } else if (token == "EDGE_WEIGHT_SECTION") {
            ParseEdgeWeightSection(file, problem_data);
        } else if (token == "NODE_COORD_SECTION") {
            ParseNodeCoordSection(file, problem_data);
        } else if (token == "DEMAND_SECTION") {
            ParseDemandSection(file, problem_data);
        } else if (token == "DEPOT_SECTION") {
            ParseDepotSection(file, problem_data);
        } else if (token == "PERMUTATION") {
            file >> colon;
            const int num_cust = problem_data.getNumCustomers();
            std::vector<int> perm;
            int val{};
            for (int k = 0; k < num_cust; ++k) {
                file >> val;
                perm.push_back(val);
            }
            problem_data.SetPermutation(perm);
        }
    }

    file.close();

    if (problem_data.isDataIncomplete()) {
        throw std::invalid_argument("Error: Something wrong with the file");
    }
}

void ProblemLoader::ParseEdgeWeightSection(std::ifstream& file, ProblemData& problem_data) {
    const int dimension = problem_data.getDimension();
    std::vector<std::vector<double>> edge_weights(dimension, std::vector<double>(dimension, 0.0));

    for (int i = 1; i < dimension; ++i) {
        for (int j = 0; j < i; ++j) {
            double weight{};
            file >> weight;
            edge_weights.at(i).at(j) = weight;
            edge_weights.at(j).at(i) = weight;
        }
    }

    problem_data.SetEdgeWeights(edge_weights);
}

void ProblemLoader::ParseNodeCoordSection(std::ifstream& file, ProblemData& problem_data) {
    const int dimension = problem_data.getDimension();
    std::vector<Coordinate> coordinates(dimension);

    int id{};
    double x{};
    double y{};

    for (int i = 0; i < dimension; ++i) {
        file >> id >> x >> y;
        if (id >= 1 && id <= dimension) {
            coordinates.at(id - 1) = Coordinate(x, y);
        }
    }

    problem_data.SetCoordinates(coordinates);
}

void ProblemLoader::ParseDemandSection(std::ifstream& file, ProblemData& problem_data) {
    const int dimension = problem_data.getDimension();
    std::vector<int> demands(dimension);

    int id{};
    int demand{};
    for (int i = 0; i < dimension; ++i) {
        file >> id >> demand;
        if (id >= 1 && id <= dimension) {
            demands.at(id - 1) = demand;
        }
    }

    problem_data.SetDemands(demands);
}

void ProblemLoader::ParseDepotSection(std::ifstream& file, ProblemData& problem_data) {
    int depot{};
    file >> depot;
    problem_data.SetDepot(depot);

    int terminator{};
    file >> terminator;
}