#ifndef __SERIAL_H__
#define __SERIAL_H__

#define BAUD_RATE B9600

#include <cstdio> 		/* Standard input/output definitions */
#include <string.h> 	/* String function definitions */
#include <unistd.h> 	/* UNIX standard function definitions */
#include <fcntl.h> 		/* File control definitions */
#include <errno.h> 		/* Error number definitions */
#include <termios.h> 	/* POSIX terminal control definitions */
#include <stdexcept> 	/* Exceptions */
#include <sys/ioctl.h> 	/* Control calls */
#include <stdlib.h>  	/* Memory, etc. */
#include "byte.hpp"

class Serial {
	private:
		int file_desc;
		size_t const packet_size;
		void* buffer_ptr {nullptr};
	public:
		Serial() = delete;
		Serial(std::string tty_dev, size_t size);
		~Serial();

		void* read_bytes();
		void init_buffer();
		int write_bytes(byte* msg, size_t size);
		size_t bytes_in_buffer();
		void flush_buffer();
		int get_file_desc();
		size_t get_packet_size();
};

#endif
