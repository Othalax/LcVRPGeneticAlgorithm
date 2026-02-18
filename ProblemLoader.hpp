#pragma once

#include "ProblemData.hpp"
#include <fstream>
#include <iostream>
#include <random>



class ProblemLoader {
	public:
		ProblemLoader(const std::string& filepath);

		ProblemData LoadProblem();

	private:
		std::string filepath;
		bool useRandomPerm;

		void ParseLcVrpFile(const std::string& file_path, ProblemData& problem_data);
		void ParseEdgeWeightSection(std::ifstream& file, ProblemData& problem_data);
		void ParseNodeCoordSection(std::ifstream& file, ProblemData& problem_data);
		void ParseDemandSection(std::ifstream& file, ProblemData& problem_data);
		void ParseDepotSection(std::ifstream& file, ProblemData& problem_data);
};

