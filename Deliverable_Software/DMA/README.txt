DMA Setup
Team: EnginHears 
Project: Low-Cost Bone-Conduction Hearing Aid
4/29/2020

There are multiple files associated with this project, which have been consolidated into 3 sets

1.  adc_soc_continuous_dma_cpu01.c
2.  buffdac_sine_dma_cpu01.c
3.  DMA_custom_setup.c

**HOW TO RUN*******************************************************************

To run, open up the adc_soc_continuous_dma folder in Code Composer Studio with target device 
TMS320F28377S selected. The main file to run is adc_soc_continuous_dma_cpu01.c.

**CURRENT STATUS**************************************************************

Due to COVID-19 and the lack of F28377s microcontrollers, the DMA setup has not been tested. This document
discusses relevent example files to set up DMA, as well as the final desired set-up below.

The team wants DMA to conduct ACD and DAC via the hardware. 
The peripheral interrupt trigger source is ADCAINT1.
Set up PIE for DMA (PIE INT 7.1)
There will be 3 buffers that are length 128 samples.
The buffers will be used to store ADC samples, filter computations, and DAC output.
The buffers will rotate location in the dmaISR.


**NEXT STEPS******************************************************************

1. Edit the adc_soc_continuous_dma to have the following characteristics
       -Fs = 25,000 Hz
       -Buffer size 128
       -Remove initialization associated with ADC Interrupt and EPWM source
       -Use the DMA_custom_setup.c values as desired reference

2. Once this is working, integrate it into the LOCO BOCO initialization files to get ADC
   working and buffers rotating in the dmaISR.

3. Extend DMA to work on the DAC, using the previous DMA initialization and buffdac_sine_dma_cpu01.c
   as reference.

**adc_soc_continuous_dma_cpu01.c**********************************************

An example script from C2000Ware with supporting folder files that sets up two ADC channels to convert simultaneously. The
results will be transferred by the DMA into a buffer in RAM.

This file contains the desired DMA initialization as well as dmaISR and memory storage.

**buffdac_sine_dma_cpu01.c****************************************************

An example script from C2000Ware with supporting folder files that generates a sine wave on the buffered DAC output using the DMA 
to transfer sine values stored in a sine table in GSRAM to DACVALS, DACOUTA/ADCINA0.

This script is for DAC initialization reference only. However, try to follow the adc_soc_continuous_dma.c format whenever possible.

**DMA_custom_setup.c*********************************************************

This file does not compile. These HAL variable values are for reference only for desired final values.

