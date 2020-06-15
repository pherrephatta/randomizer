# Arduino
## References
- [Functions](https://www.arduino.cc/reference/en/#functions)
- [Variables](https://www.arduino.cc/reference/en/#functions)
- [Struture](https://www.arduino.cc/reference/en/#functions)
- [Arduino Uno Pins](https://roboticsbackend.com/arduino-uno-pins-a-complete-practical-guide/)
- [Arduino SPI](https://www.arduino.cc/en/reference/SPI)
- [Arduino SPI with EEPROM](https://www.arduino.cc/en/Tutorial/SPIEEPROM)
- [Arduino Interrupts](http://www.gammon.com.au/interrupts)

## Pinouts
[Source](http://busyducks.com/ascii-art-arduinos)

```
// Arduino UNO
                                      +-----+
         +----[PWR]-------------------| USB |--+
         |                            +-----+  |
         |         GND/RST2  [ ][ ]            |
         |       MOSI2/SCK2  [ ][ ]  A5/SCL[ ] |   C5 
         |          5V/MISO2 [ ][ ]  A4/SDA[ ] |   C4 
         |                             AREF[ ] |
         |                              GND[ ] |
         | [ ]N/C                    SCK/13[ ] |   B5
         | [ ]IOREF                 MISO/12[ ] |   .
         | [ ]RST                   MOSI/11[ ]~|   .
         | [ ]3V3    +---+               10[ ]~|   .
         | [ ]5v    -| A |-               9[ ]~|   .
         | [ ]GND   -| R |-               8[ ] |   B0
         | [ ]GND   -| D |-                    |
         | [ ]Vin   -| U |-               7[ ] |   D7
         |          -| I |-               6[ ]~|   .
         | [ ]A0    -| N |-               5[ ]~|   .
         | [ ]A1    -| O |-               4[ ] |   .
         | [ ]A2     +---+           INT1/3[ ]~|   .
         | [ ]A3                     INT0/2[ ] |   .
         | [ ]A4/SDA  RST SCK MISO     TX>1[ ] |   .
         | [ ]A5/SCL  [ ] [ ] [ ]      RX<0[ ] |   D0
         |            [ ] [ ] [ ]              |
         |  UNO_R3    GND MOSI 5V  ____________/
          \_______________________/
```

```
// Arduino MEGA

	                                  +-----+
         +----[PWR]-------------------| USB |--+
         |                            +-----+  |
         |           GND/RST2  [ ] [ ]         |
         |         MOSI2/SCK2  [ ] [ ]  SCL[ ] |   D0
         |            5V/MISO2 [ ] [ ]  SDA[ ] |   D1
         |                             AREF[ ] |
         |                              GND[ ] |
         | [ ]N/C                        13[ ]~|   B7
         | [ ]IOREF                      12[ ]~|   B6
         | [ ]RST                        11[ ]~|   B5
         | [ ]3V3      +----------+      10[ ]~|   B4
         | [ ]5v       | ARDUINO  |       9[ ]~|   H6
         | [ ]GND      |   MEGA   |       8[ ]~|   H5
         | [ ]GND      +----------+            |
         | [ ]Vin                         7[ ]~|   H4
         |                                6[ ]~|   H3
         | [ ]A0                          5[ ]~|   E3
         | [ ]A1                          4[ ]~|   G5
         | [ ]A2                     INT5/3[ ]~|   E5
         | [ ]A3                     INT4/2[ ]~|   E4
         | [ ]A4                       TX>1[ ]~|   E1
         | [ ]A5                       RX<0[ ]~|   E0
         | [ ]A6                               |   
         | [ ]A7                     TX3/14[ ] |   J1
         |                           RX3/15[ ] |   J0
         | [ ]A8                     TX2/16[ ] |   H1         
         | [ ]A9                     RX2/17[ ] |   H0
         | [ ]A10               TX1/INT3/18[ ] |   D3         
         | [ ]A11               RX1/INT2/19[ ] |   D2
         | [ ]A12           I2C-SDA/INT1/20[ ] |   D1         
         | [ ]A13           I2C-SCL/INT0/21[ ] |   D0
         | [ ]A14                              |            
         | [ ]A15                              |   Ports:
         |                RST SCK MISO         |    22=A0  23=A1   
         |         ICSP   [ ] [ ] [ ]          |    24=A2  25=A3   
         |                [ ] [ ] [ ]          |    26=A4  27=A5   
         |                GND MOSI 5V          |    28=A6  29=A7   
         | G                                   |    30=C7  31=C6   
         | N 5 5 4 4 4 4 4 3 3 3 3 3 2 2 2 2 5 |    32=C5  33=C4   
         | D 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 V |    34=C3  35=C2   
         |         ~ ~                         |    36=C1  37=C0   
         | @ # # # # # # # # # # # # # # # # @ |    38=D7  39=G2    
         | @ # # # # # # # # # # # # # # # # @ |    40=G1  41=G0   
         |           ~                         |    42=L7  43=L6   
         | G 5 5 4 4 4 4 4 3 3 3 3 3 2 2 2 2 5 |    44=L5  45=L4   
         | N 3 1 9 7 5 3 1 9 7 5 3 1 9 7 5 3 V |    46=L3  47=L2   
         | D                                   |    48=L1  49=L0    SPI:
         |                                     |    50=B3  51=B2     50=MISO 51=MOSI
         |     2560                ____________/    52=B1  53=B0     52=SCK  53=SS 
          \_______________________/         

```

```
// Arduino NANO

                      +-----+
         +------------| USB |------------+
         |            +-----+            |
    B5   | [ ]D13/SCK        MISO/D12[ ] |   B4
         | [ ]3.3V           MOSI/D11[ ]~|   B3
         | [ ]V.ref     ___    SS/D10[ ]~|   B2
    C0   | [ ]A0       / N \       D9[ ]~|   B1
    C1   | [ ]A1      /  A  \      D8[ ] |   B0
    C2   | [ ]A2      \  N  /      D7[ ] |   D7
    C3   | [ ]A3       \_0_/       D6[ ]~|   D6
    C4   | [ ]A4/SDA               D5[ ]~|   D5
    C5   | [ ]A5/SCL               D4[ ] |   D4
         | [ ]A6              INT1/D3[ ]~|   D3
         | [ ]A7              INT0/D2[ ] |   D2
         | [ ]5V                  GND[ ] |     
    C6   | [ ]RST                 RST[ ] |   C6
         | [ ]GND   5V MOSI GND   TX1[ ] |   D0
         | [ ]Vin   [ ] [ ] [ ]   RX1[ ] |   D1
         |          [ ] [ ] [ ]          |
         |          MISO SCK RST         |
         | NANO-V3                       |
         +-------------------------------+
```

## Raspberry Pi and Arduino SPI with WiringPi
[Source](https://roboticsbackend.com/raspberry-pi-master-arduino-uno-slave-spi-communication-with-wiringpi/)

The Raspberry Pi will be configured as a master, and the Arduino as a slave. We’ll use the C++ language and the WiringPi library, more specifically the WiringPiSPI sub-part of the library.

## Serial Peripheral Interface
- Master In Slave Out (MISO) - The Slave line for sending data to the master,
- Master Out Slave In (MOSI) - The Master line for sending data to the peripherals,
- Serial Clock (SCK) - The clock pulses which synchronize data transmission generated by the master, and
- Slave Select pin - allocated on each device which the master can use to enable and disable specific devices and avoid false transmissions due to line noise. 

### Registers
All SPI settings are determined by the Arduino SPI Control Register (SPCR). A register is just a byte of microcontroller memory that can be read from or written to. Registers generally serve three purposes, control, data and status. 

```
SPCR
| 7    | 6    | 5    | 4    | 3    | 2    | 1    | 0    |
| SPIE | SPE  | DORD | MSTR | CPOL | CPHA | SPR1 | SPR0 |

SPIE - Enables the SPI interrupt when 1
SPE - Enables the SPI when 1
DORD - Sends data least Significant Bit First when 1, most Significant Bit first when 0
MSTR - Sets the Arduino in master mode when 1, slave mode when 0
CPOL - Sets the data clock to be idle when high if set to 1, idle when low if set to 0
CPHA - Samples data on the falling edge of the data clock when 1, rising edge when 0
SPR1 and SPR0 - Sets the SPI speed, 00 is fastest (4MHz) 11 is slowest (250KHz)
```

Data registers simply hold bytes. For example, the SPI data register (SPDR) holds the byte which is about to be shifted out the MOSI line, and the data which has just been shifted in the MISO line. 

Status registers change their state based on various microcontroller conditions. For example, the seventh bit of the SPI status register (SPSR) gets set to 1 when a value is shifted in or out of the SPI. 

## Serial UART
[Source](https://ns-electric.com/knowledge-base/intro-to-arduino-uart-serial-communication/)
https://www.cmrr.umn.edu/~strupp/serial.html#CONTENTS
https://www.tldp.org/HOWTO/Serial-HOWTO.html
https://www.tldp.org/HOWTO/Serial-Programming-HOWTO/
https://linux.die.net/man/3/termios

`Serial.begin(baud_rate, [configuration])` to initialize the serial module.
Default configuration is `SERIAL_8N1`, which is 8 bits of data with No parity and 1 stop bit. This configuration parameter can be changed to 5-8 data bits; No parity, Even parity, or Odd parity, and 1 or 2 stop bits.

The rate at which individual bits of data are sent is called the baud rate. One of the most common baud rates for UART (the closest thing to default) is 9600 bits per second (bps). Other common baud rates are 300, 600, 1200, 2400, 4800, 19200, 38400, 57600, 74880, and 115200 bps.

`Serial.write()` to send one byte at a time.
`Serial.print()` to send more than one byte at a time.
`Serial.println()` to send more than one byte and add carriage return.

`Serial.read()` returns first byte of the serial buffer, or -1 if none.
`Serial.available()` to see the number of available bytes.
`Serial.peak()` returns the first byte without removing it.
`Serial.flush()` clear the serial buffer.
`Serial.parseInt()` output an integer by parsing integers present in the buffer.
