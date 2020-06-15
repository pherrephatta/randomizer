#include "RandomEngine.hpp"

RandomEngine::RandomEngine(Serial &cnct, EntropyPool &pool) :
running{true}, connection{cnct}, entropy_pool{pool}, tmp_entropy_pool{&pool}
{
	start();
	while (running) {
		run();
	}
}

//TODO: write cmd bytes - Arduino resets after being sent message
void RandomEngine::start() {
	/* byte cmd[]{'f', 'f'};
	connection.write_bytes(cmd, sizeof(cmd)); */
}

//TODO: read keyboard signals - SDL
void RandomEngine::stop() {
	running = false;
}

void RandomEngine::run() {
	byte* packet = (byte*) connection.read_bytes();
	size_t packet_size = connection.get_packet_size();
	extractor.apply_algos(packet, packet_size);
	if (tmp_entropy_pool.get_state()) {
		debiaser.apply_algos((void*)tmp_entropy_pool.get_start(), tmp_entropy_pool.get_size());
		tmp_entropy_pool.set_state(false);
		entropy_pool.copy(&tmp_entropy_pool);
	}
	else {
		tmp_entropy_pool.add_bytes(packet, packet_size);
	}

	draw();
}

void RandomEngine::draw() {
	printf("\033[2J"); // clear screen
	printf("\n");
	extractor.print_algos_avail("Extractor");
	extractor.print_algos_used("Extractor");
	debiaser.print_algos_avail("Debiaser");
	debiaser.print_algos_used("Debiaser");
	entropy_pool.draw();
	printf("\n");
}
