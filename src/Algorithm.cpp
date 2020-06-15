#include "Algorithm.hpp"

Algorithm::Algorithm(algo_t funct, std::string name) {
	this->funct = funct;
	this->name = name;
}

std::string Algorithm::get_name() {
	return name;
}

algo_t Algorithm::get_funct() {
	return funct;
}
