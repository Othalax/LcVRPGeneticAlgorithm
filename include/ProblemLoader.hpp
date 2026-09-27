#ifndef PROBLEMLOADER_HPP
#define PROBLEMLOADER_HPP

#include "ProblemData.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>

class ProblemLoader {
  public:
    explicit ProblemLoader(std::string filepath);

    ProblemData LoadProblem();

  private:
    std::string filepath;
    bool useRandomPerm;

    static void ParseLcVrpFile(const std::string& file_path, ProblemData& problem_data);
    static void ParseEdgeWeightSection(std::ifstream& file, ProblemData& problem_data);
    static void ParseNodeCoordSection(std::ifstream& file, ProblemData& problem_data);
    static void ParseDemandSection(std::ifstream& file, ProblemData& problem_data);
    static void ParseDepotSection(std::ifstream& file, ProblemData& problem_data);
};

#endif // PROBLEMLOADER_HPP