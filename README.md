## Randomizer

*Usage:* `randomizer [*dev_path] [packet_size] [pool_size]`

Takes input from an Arduino Nano which probes a noise-generating circuit.

### Arguments

- dev_path			path to arduino serial port device file
- packet_size		size of buffer when receiving packets
- pool_size			size of the entropy pool

### To do

- Extraction and decorrelation should be performed on the temporary pool and not on raw data,
i.e. the temp pool should be reduced to a single value and then pushed to the final pool
- Change pools to vectors of boolean?
- Binary file stream for final pool?
- Fix communication with Arduino device (sending commands)
- Serial: SPI connection instead of UART
- Add cyphers and hashing on final pool
- SDL_events for keyboard read
- SDL_widgets for GUI
