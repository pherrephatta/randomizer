#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <stdlib.h>  	/* Using size_t */
#include <string> 	 	/* Using strings */
#include "byte.hpp"

using algo_t = void(*)(byte* ptr, size_t size);

class Algorithm {
	private:
		std::string name{};
		algo_t funct {nullptr};
	public:
		Algorithm() = delete;
		Algorithm(algo_t funct, std::string name);
		~Algorithm() = default;
		std::string get_name();
		algo_t get_funct();
};

#endif
