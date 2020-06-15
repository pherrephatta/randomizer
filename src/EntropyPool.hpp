#ifndef _ENTROPYPOOL_H_
#define _ENTROPYPOOL_H_

#include <cstdio> 		/* Standard input/output definitions */
#include <stdlib.h>  	/* Memory alloc, etc. */
#include <errno.h> 		/* Error number definitions */
#include <stdexcept> 	/* Exceptions */
#include <string.h> 	/* String function definitions */
#include "byte.hpp"

class EntropyPool {
	private:
		void* pool_ptr{nullptr};
		size_t pool_ptr_pos{};
		size_t pool_size{};
		bool pool_ready{};
	public:
		EntropyPool(size_t size);
		EntropyPool(EntropyPool& pool) = default;
		EntropyPool(EntropyPool* pool);
		~EntropyPool();
		int add_bytes(byte data);
		int add_bytes(byte* data, size_t size);
		void read_bytes(byte* data, size_t size);
		void draw();
		size_t get_size();
		size_t get_pos();
		const void* get_start();
		bool get_state();
		void set_state(bool state);
		int copy(EntropyPool* pool);
		int copy(byte* data, size_t size);
};

#endif
