#include "ProcessingEngine.hpp"

ProcessingEngine::ProcessingEngine() {
	class_name = typeid(*this).name();
	class_name.erase(class_name.begin(), class_name.begin() + 2);
}

void ProcessingEngine::apply_algos(void* ptr, size_t size) {
	byte* tmp_ptr = (byte*)	ptr;
	for (Algorithm* fct : algos_apply) {
		(fct->get_funct())(tmp_ptr, size);
	}
}

void ProcessingEngine::print_algos_used(std::string title) {
	printf("%s algorithms used:", title.c_str());
	for (Algorithm* fct : algos_apply) {
		printf(" %s", fct->get_name().c_str());
	}
	printf("\n");
}

void ProcessingEngine::print_algos_avail(std::string title) {
	printf("%s algorithms available:", title.c_str());
	for (Algorithm fct : algos_avail) {
		printf(" %s", fct.get_name().c_str());
	}
	printf("\n");
}
