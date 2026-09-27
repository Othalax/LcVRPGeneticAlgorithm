#include "Evaluator.hpp"

Evaluator::Evaluator(const ProblemData& problem_data, int num_groups)
    : problemData(problem_data), numGroups(num_groups),
      numCustomers(problem_data.getNumCustomers()) {
    routesBuffer.resize(numGroups);
    try {
        if (!ValidateConstraints()) {
            throw std::runtime_error(
                "Problem is impossible to solve - client's demand is bigger than capacity");
        }
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
    }
}

double Evaluator::Evaluate(std::vector<std::vector<int>> fenotype) {
    routesBuffer = std::move(fenotype);

    double total_cost = 0.0;
    for (const std::vector<int>& route : routesBuffer) {
        const double route_cost = CalculateRouteCost(route);

        if (route_cost >= std::numeric_limits<double>::infinity()) {
            return std::numeric_limits<double>::infinity();
        }

        total_cost += route_cost;
    }

    return total_cost;
}

bool Evaluator::ValidateConstraints() {
    const int depot_idx = problemData.getDepot() - 1;
    const std::vector<int>& demands = problemData.getDemands();
    const int capacity = problemData.getCapacity();

    for (int i = 0; i < problemData.getDimension(); ++i) {
        if (i != depot_idx) {
            if (demands.at(i) > capacity) {
                return false;
            }
        }
    }

    return true;
}

double Evaluator::CalculateRouteCost(const std::vector<int>& route) {
    if (route.empty()) {
        return 0.0;
    }

    double route_total_cost = 0.0;
    const int depot_idx = problemData.getDepot() - 1;
    const int capacity = problemData.getCapacity();
    const std::vector<int>& demands = problemData.getDemands();

    int current_load = 0;
    double current_subtour_dist = 0.0;
    int last_idx = depot_idx;

    for (const int customer_id : route) {
        const int cust_idx = customer_id - 1;
        const int demand = demands.at(cust_idx);

        double d_last_to_cust = problemData.CalculateDistance(last_idx, cust_idx);

        const bool capacity_exceeded = (current_load + demand > capacity);
        if (capacity_exceeded) {
            route_total_cost +=
                (current_subtour_dist + problemData.CalculateDistance(last_idx, depot_idx));

            current_load = 0;
            current_subtour_dist = 0.0;

            d_last_to_cust = problemData.CalculateDistance(depot_idx, cust_idx);
        }
        current_subtour_dist += d_last_to_cust;
        current_load += demand;
        last_idx = cust_idx;
    }

    route_total_cost += (current_subtour_dist + problemData.CalculateDistance(last_idx, depot_idx));

    return route_total_cost;
}
