#include "PE_Debiaser.hpp"

PE_Debiaser::PE_Debiaser() {
	init();
}

void PE_Debiaser::init() {
	// algos.push_back([](void* ptr, size_t size)->void{});
	algos_avail.push_back(Algorithm(amls, "amls"));
//	algos_apply.push_back(&algos_avail[0]);
}

//TODO: Should be repeatable
void PE_Debiaser::amls(byte* ptr, size_t size) {
	byte* tmp_ptr = (byte*) malloc(size);
	memset(tmp_ptr, 0, size);
	size_t bit_count{};
	size_t byte_pos{};
	size_t bit_pos{};
	bool b_one{};
	bool b_two{};
	for (size_t i{}; i < size; ++i) {
		for (size_t j{}; j < 8;) {
			b_one = ptr[i] & (1 << j);
			b_two = ptr[i] & (1 << (j + (j < 7 ? 1 : -6)));
			if (b_one == b_two) {
				tmp_ptr[byte_pos] |= b_one << bit_pos;
				++bit_count;
			}
			j += 2;
			bit_pos +=1;
			if (bit_pos == 8) {
				byte_pos += 1;
				bit_pos = 0;
			}
		}
	}

	if (bit_count) {
		memcpy(ptr, tmp_ptr, size);
		free(tmp_ptr);
	}
}
