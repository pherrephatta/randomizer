#include "EntropyPool.hpp"

EntropyPool::~EntropyPool() {
	if (pool_ptr != nullptr) {
		free(pool_ptr);
	}
}

EntropyPool::EntropyPool(size_t size) {
	pool_size = size;
	if (pool_ptr != nullptr) {
		free(pool_ptr);
	}
	pool_ptr = malloc(pool_size);
	if (pool_ptr == nullptr) {
		printf("Error: %s\n", strerror(errno));
		throw std::runtime_error("Failed to allocate TTY port buffer memory!");
	}

	printf("Finished loading entropy pool.\n");
}

// Move?
EntropyPool::EntropyPool(EntropyPool* pool) {
	copy(pool);
}

void EntropyPool::read_bytes(byte* data, size_t size) {
	size_t pos{};
	while((pos < size) && (pos < pool_size)) {
		data[pos] = ((byte*)pool_ptr)[pos];
		++pos;
	}
	pool_ready = false;
}

int EntropyPool::add_bytes(byte data) {
	if (!pool_ready && pool_ptr_pos < pool_size) {
		byte* crt_ptr = (byte*) pool_ptr;
		crt_ptr[pool_ptr_pos] = data;
		++pool_ptr_pos;
		return 0;
	}
	//TODO: Pool is full mechanism or add randomly for all cases
	else {
		pool_ready = true;
		pool_ptr_pos = 0;
		//printf("Pool is full, resetting...\n");
		return 1;
	}
	//TODO: errors
	return -1;
}

int EntropyPool::add_bytes(byte* data, size_t size) {
	for (size_t i{}; i < size; ++i) {
		add_bytes(data[i]);
	}
	//TODO: errors
	return 0;
}

int EntropyPool::copy(EntropyPool* pool) {
	return copy((byte*) pool->get_start(), pool->get_size());
}

int EntropyPool::copy(byte* data, size_t size) {
	if (pool_ptr != nullptr) {
		free(pool_ptr);
	}
	pool_size = size;
	pool_ready = false;
	pool_ptr = malloc(size);
	if (pool_ptr != nullptr) {
		memcpy(pool_ptr, data, size);
		return 0;
	}
	else {
		//TODO: errors
		return -1;
	}
}

void EntropyPool::draw() {
	byte* crt_ptr = (byte*) pool_ptr;
	printf("\nSize of pool: %d\n", (int) pool_size);
	for (size_t i{}; i < pool_size; ++i) {
		printf("%02X", crt_ptr[i]);
	}
}

size_t EntropyPool::get_pos() {
	return pool_ptr_pos;
}

size_t EntropyPool::get_size() {
	return pool_size;
}

const void* EntropyPool::get_start() {
	return pool_ptr;
}

bool EntropyPool::get_state() {
	return pool_ready;
}

void EntropyPool::set_state(bool state) {
	pool_ready = state;
}
