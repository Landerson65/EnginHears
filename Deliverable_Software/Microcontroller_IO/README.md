This folder houses the initialization code needed to make the microcontroller operational.

'watchdog_cpu01.c' is the main file that has the I/O initializations and the general layout
for the filter implementation. The gain calculation is included in this file, but requires
the addition of an FFT/iFFT and DMA to be operational.
