#ifndef _PE_EXTRACTOR_H_
#define _PE_EXTRACTOR_H_

#include "ProcessingEngine.hpp"
#include "byte.hpp"

class PE_Extractor : public ProcessingEngine {
	private:
		void init() override;
	public:
		PE_Extractor();
		~PE_Extractor() = default;
		static void von_newman(byte *ptr, size_t size);
		static void exclusive_or(byte *ptr, size_t size);
};

#endif
