#ifndef _RANDOMENGINE_H_
#define _RANDOMENGINE_H_

#include <signal.h>  	/* Interrupts */
#include "Serial.hpp"
#include "EntropyPool.hpp"
#include "PE_Extractor.hpp"
#include "PE_Debiaser.hpp"

class RandomEngine {
	private:
		bool running;
		Serial& connection;
		EntropyPool& entropy_pool;
		EntropyPool tmp_entropy_pool;
		PE_Extractor extractor{};
		PE_Debiaser debiaser{};
	public:
		RandomEngine() = delete;
		RandomEngine(Serial &serial, EntropyPool &pool);
		~RandomEngine() = default;
		void run();
		void stop();
		void start();
		void draw();
};

#endif
