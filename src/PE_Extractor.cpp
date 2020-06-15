#include "PE_Extractor.hpp"

PE_Extractor::PE_Extractor() {
	init();
}

void PE_Extractor::init() {
	// algos.push_back([](void* ptr, size_t size)->void{});
	algos_avail.push_back(Algorithm(exclusive_or, "exclusive_or"));
	algos_avail.push_back(Algorithm(von_newman, "von_newman"));
	algos_apply.push_back(&algos_avail[0]);
//	algos_apply.push_back(&algos_avail[1]);
}

//TODO: better von Newman?
void PE_Extractor::von_newman(byte *ptr, size_t size) {
	byte* new_pos = ptr;
	size_t bit_pos{};
	bool b_one{};
	bool b_two{};
	for (size_t i{}; i < size; ++i) {
		for (size_t j{}; j < 8;) {
			b_one = ptr[i] & (1 << j);
			b_two = ptr[i] & (1 << ++j);
			*new_pos ^= ((b_one == b_two ? !b_one : b_one) << bit_pos);
			if (++bit_pos > 7) {
				bit_pos = 0;
				++new_pos;
			}
		}
	}
}

//TODO: common operations on bits for all functions?
void PE_Extractor::exclusive_or(byte *ptr, size_t size) {
	static bool flipper{};
	for (size_t i{}; i < size; ++i) {
		for (size_t j{}; j < 8; ++j) {
			ptr[i] ^= (flipper << j);
			flipper = !flipper;
		}
	}
}
