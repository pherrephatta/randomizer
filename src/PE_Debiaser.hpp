#ifndef _PE_CYPHER_H
#define _PE_CYPHER_H

#include "ProcessingEngine.hpp"
#include "byte.hpp"

class PE_Debiaser : public ProcessingEngine {
	private:
		void init() override;
	public:
		PE_Debiaser();
		~PE_Debiaser() = default;
		static void amls(byte* ptr, size_t size);
};

#endif
