#ifndef _PROCESSINGENGINE_H_
#define _PROCESSINGENGINE_H_

#include <vector>
#include <string>
#include "EntropyPool.hpp"
#include "Algorithm.hpp"
#include "byte.hpp"

class ProcessingEngine {
	private:
		virtual void init() = 0;
		std::string class_name{};
	protected:
		// std::vector<std::function<void(byte* ptr, size_t size)>> algos;
		std::vector<Algorithm> algos_avail;
		std::vector<Algorithm*> algos_apply;
	public:
		ProcessingEngine();
		~ProcessingEngine() = default;
		void apply_algos(void* ptr, size_t size);
		void print_algos_used(std::string title);
		void print_algos_avail(std::string title);
};

#endif
