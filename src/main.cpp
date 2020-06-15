#include "Serial.hpp"
#include "EntropyPool.hpp"
#include "RandomEngine.hpp"

#define PACKET_SIZE 32
#define POOL_SIZE 1024

int main(int argc, char** argv) {
	signal(SIGINT, exit);
	if (argc < 4) {
		printf("Usage: randomizer [dev_path] [packet_size] [pool_size]\n");
		return 1;
	}
	std::string tty_id {argv[1]};
	Serial connection {tty_id,(size_t) atoi(argv[2])};
	EntropyPool entropy_pool {(size_t) atoi(argv[3])};
	RandomEngine random_engine {connection, entropy_pool};

	return 0;
}
