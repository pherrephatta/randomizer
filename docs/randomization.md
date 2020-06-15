```
ooooooooo.                               .o8                              
`888   `Y88.                            "888                              
 888   .d88'  .oooo.   ooo. .oo.    .oooo888   .ooooo.  ooo. .oo.  .oo.   
 888ooo88P'  `P  )88b  `888P"Y88b  d88' `888  d88' `88b `888P"Y88bP"Y88b  
 888`88b.     .oP"888   888   888  888   888  888   888  888   888   888  
 888  `88b.  d8(  888   888   888  888   888  888   888  888   888   888  
o888o  o888o `Y888""8o o888o o888o `Y8bod88P" `Y8bod8P' o888o o888o o888o 

"Anybody who contemplates arithmetic methods for the generation of random numbers is in a state of sin"
- John von Neumann
```

"The Art of Electronics", pp.974-988
"Art of Programming", Vol.2, Ch.3

## Introduction
(Pseudo-)random sequence and noise generation offers an interesting mix of analog and digital tehniques. It's surprisingle easy to generate one by standard deterministic means, e.g. logic elements like shift registers. However, if generation is based solely on software, the results will depend on the state of the machine at the outset of the process, which is insecure, i.e. the state can be reversed. Random physical sources such as quantum effects (e.g. the action of a photon incident upon a beam splitter), or chaotic systems (e.g. weather) are sampled and conditioned and are thought to provide truly random) streams.

## Word-bank
`ADC` Analog-to-digital converter
`Microprocessor Development Board` printed circuit board with a microprocessor and minimal support logic needed to learn to program it

## Entropy
[Entropy and Sources](https://hackaday.com/2017/11/02/what-is-entropy-and-how-do-i-get-more-of-it/)
Entropy is a measure of the number of possible choices from which our secret value could have been drawn, and it’s a way to measure hardness-to-guess, strength of passwords, etc.

`cat /proc/sys/kernel/random/entropy_avail` can be used to verify how much entropy is available on a Linux machine, or `watch -n 1 cat /proc/sys/kernel/random/entropy_avail` to see it in real time. The main difference to the end-user is that /dev/random will wait to deliver numbers until it has enough entropy, while /dev/urandom is a free-running PRNG that’s already been seeded from /dev/random

## Pseudo Random Generator
Most popular PRBS generator is the linear feedback shift register (LFSR). A shift register of length `m` is clocked at some fixed rate `f0`. A XOR gate generates the serial inpul signal from the XOR combination of the `n`th bit and the last bit (`m`th) of the register. Such a circuit goes through a set of states defined by the set of bits in the register after each clock pulse, eventually repeating itself after `K` clock pulses, where `K = 2^m - 1` or the possible combinations of `m` bits minus the state where all bits are 0s. Bit positions that affect the next state are called the _Taps_.

## Methods
### Avalanche breakdown noise in a PN junction
https://www.io.com/~ritter/RES/NOISE.HTM
http://www.avtechpulse.com/faq.html/

`Thermal or Johnson Noise`: 
"What is the source of Johnson noise? In an ordinary resistor, it is a summation of the effects of the very short current pulses of many electrons as they travel between collisions, each pulse individually having a flat spectrum. In this case the noise is a manifestation of the Brownian movement of the electrons in the resistor." 

This type of noise is fundamental and cannot be eliminated but it can be reduced by reducing the resistance or by cooling it. Carbon-composition resistors may give more noise than expected; this added noise is from device fabrication, varies widely in production, and is not necessarily "white." Thus, carbon-film or wirewound resistors are more satisfactory thermal noise sources.

`Shot Noise`:
Shot noise typically results from the flow of electrons through a highly-charged field like a vacuum tube or semiconductor junction. Shot noise is fundamental, so no true zener can be noiseless, and any especially "noisy" zener must be producing something beyond shot noise. We should seek the lowest-noise zeners for noise sources. Since zener noise levels will vary with temperature, some form of automatic gain control (AGC) may be necessary.  

`Avalanche Breakdown`:
The avalanche process occurs when carriers in the transition region are accelerated by the electric field to energies sufficient to create mobile or free electron-hole pairs via collisions with bound electrons, i.e. when the electric field is strong enough, the mobile electron or hole may be accelerated to high enough speeds to knock other bound electrons free, creating more free charge carriers, increasing the current and leading to further "knocking out" processes and creating an avalanche. In this way, large portions of a normally insulating crystal can begin to conduct. The voltage at which the breakdown occurs is called the breakdown voltage.

Some diodes are designed to have a very well controlled avalanche breakdown characteristic; these can be used as white noise generators. If you aren't looking for something particularly fancy, a normal avalanche zener diode (not a tunneling zener diode) will work quite well as a noise source when biased in breakdown.

### Uninitialized RAM
[Embedded RAM](https://hackaday.com/2015/06/29/true-random-number-generator-for-a-true-hacker/)
[Zombie RAM](https://hackaday.com/2014/03/06/the-mystery-of-zombie-ram/)

Works but once the random number generator is biased towards a predictable set of values the resulting crypto falls apart, e.g. pegging the CPU or RAM at 100%.

### Post-Production Analog Processing
It will be necessary to greatly amplify the noise in a linear broadband manner, e.g. a circuit which uses avalanche noise in a reverse-biased PN junction, the emitter-base junction of the first transistor. The second transistor amplifies it. The first two ALS04 inverters are biased into a linear region where they act like op amps, and they amplify it further. The third inverter amplifies it some more, and clips it to TTL levels.

To generate 128 really random bits, collect 1000 or 2000 bits from this circuit, and hash them using MD5 or SHA. A hash ratio of 10:1 or 20:1 should be adequate to thwart any electromagnetic attack intended to influence or predetermine the final 128 bits.

In order to tell /dev/random how many bits of entropy, there is an ioctl, RNDADDENTROPY, and then a pointer to a structure which looks like this:

```
struct rand_pool_info {
	int	entropy_count;
	int	buf_size;
	__u32	buf[MAX_ENT_BUF_SIZE];
};
```

**Note** this ioctl requires root access. The basic idea is that you have a user-mode daemon that receives the input from the hwrand device driver, does whatever whitening, entropy characterization is necessary (which may potentially be CPU intensive, and so should be done in user-mode), and then uses this ioctl to feedthe data into the /dev/random entropy pool.

A tool exists to do this easily, `rngd`. It reseeds the entropy pool as it gets low and can take an arbitrary filename for input into `/dev/random`, e.g. `rngd -r /dev/urandom`, but you can't use a file as the _only_ source of entropy.  

### Detection and Conversion to Uniform Distribution
If we can detect individual noise pulses, we can assume that the number of pulses which arrive in a particular time is Poisson distributed. By increasing the detection amplitude until few pulses are detected (on average) and counting the pulses in a given time, we can get a Poisson distribution of pulse-count values. Then we can output the parity of the current count to get one (almost) uniformly distributed random bit.
