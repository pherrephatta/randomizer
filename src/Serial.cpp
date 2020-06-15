#include "Serial.hpp"

/* TERMIOS STRUCT
 * --------------
 * 	tcflag_t c_iflag;		// input mode flags
 * 	tcflag_t c_oflag;		// output mode flags
 * 	tcflag_t c_cflag;		// control mode flags
 * 	tcflag_t c_lflag;		// local mode flags
 * 	cc_t c_line;			// line discipline
 * 	cc_t c_cc[NCCS];		// control characters
 */

Serial::~Serial() {
	free(buffer_ptr);
	buffer_ptr = nullptr;
	close(file_desc);
}

Serial::Serial(std::string tty_dev, size_t size) :
file_desc {open(tty_dev.c_str(), O_RDWR | O_NOCTTY | O_NDELAY)}, packet_size{size}
/* Set option flags
 * O_RDWR - Read/Write
 * O_NOCTTY - Don't become process's controlling terminal
 * O_NDELAY - Open in non-blocking mode (no waits caused by operations)
 */
{
	init_buffer();

	if (file_desc < 0) {
		printf("Error: %s\n", strerror(errno));
		throw std::runtime_error("Failed to open TTY port!");
	}

	// Create port option struct
	struct termios tty_options;

	// Get current port options
	if (tcgetattr(file_desc, &tty_options) < 0) {
		printf("Error: %s\n", strerror(errno));
		throw std::runtime_error("Failed to open TTY port!");
	}

	cfsetispeed(&tty_options, BAUD_RATE); 		// Set baud rate - input
	cfsetospeed(&tty_options, BAUD_RATE); 		// Set baud rate - output
	tty_options.c_cflag |= CREAD;				// Enable receiver
	tty_options.c_cflag |= CLOCAL;				// Local line - no change to port's owner
	tty_options.c_cflag &= ~CSIZE;				// Mask the character size bits
	tty_options.c_cflag &= ~PARENB;				// Disable parity bit
	tty_options.c_cflag &= ~CSTOPB;				// Use 1 stop bit
	tty_options.c_cflag |= CS8;					// Use 8 data bits
	tty_options.c_cflag &= ~CRTSCTS;			// Disable hardware flow control

	tty_options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); 	// Raw input mode (non-canonical)
	tty_options.c_iflag &= ~(IXON | IXOFF | IXANY); 			// Disable software flow control
	tty_options.c_oflag &= ~OPOST; 								// Raw output mode

	tty_options.c_cc[VMIN] = 1; 	// Minimum of x chars before read
	tty_options.c_cc[VTIME] = 0; 	// Wait for data (ms)

	// Set new port options
	if (tcsetattr(file_desc, TCSANOW, &tty_options) < 0) {
		close(file_desc);
		printf("Error: %s\n", strerror(errno));
		throw std::runtime_error("Failed to configure TTY port!");
	}

	// Flush non-read intput data in the buffer
	flush_buffer();

	// No blocks on reads if no data
	if (fcntl(file_desc, F_SETFL, FNDELAY) < 0) {
		close(file_desc);
		printf("Error: %s\n", strerror(errno));
		throw std::runtime_error("Failed to set read tty_options!");
	}

	printf("Finished loading serial connection.\n");
}

void Serial::init_buffer() {
	free(buffer_ptr);
	buffer_ptr = (byte*) malloc(packet_size);
	if (buffer_ptr == nullptr) {
		printf("Error: %s\n", strerror(errno));
		throw std::runtime_error("Failed to allocate TTY port buffer memory!");
	}
}

size_t Serial::bytes_in_buffer() {
	size_t nb_bytes{};
	if (ioctl(file_desc, FIONREAD, &nb_bytes) < 0) {
		close(file_desc);
		throw std::runtime_error("Failed to read buffer!");
	}
	return nb_bytes;
}

void* Serial::read_bytes() {
	init_buffer();

	if (bytes_in_buffer()) {
		while(bytes_in_buffer() < packet_size) {}
		int bytes_read = read(file_desc, buffer_ptr, packet_size);
		if (bytes_read < 0) {
			close(file_desc);
			printf("Error: %s\n", strerror(errno));
			throw std::runtime_error("Failed to read from serial!");
		}
	}
	return buffer_ptr;
}

int Serial::write_bytes(byte* msg, size_t size) {
	int bytes_written = write(file_desc, msg, size);
	if (bytes_written < 0) {
		close(file_desc);
		printf("Error: %s\n", strerror(errno));
		throw std::runtime_error("Failed to write to serial!");
	}
	return bytes_written;
}

void Serial::flush_buffer() {
	if (tcflush(file_desc, TCIFLUSH) < 0) {
		close(file_desc);
		throw std::runtime_error("Failed to flush buffer!");
	}
}

int Serial::get_file_desc() {
	return file_desc;
}

size_t Serial::get_packet_size() {
	return packet_size;
}
