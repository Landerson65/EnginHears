// Initialization Integration Test Code
// Project: Low-Cost Bone Conduction Hearing Aid
// Performed on 2/29/2020

//This script initializes the board for ADC on pin J7-4, performs a notch filter with cutoff frequency fc = 4000 Hz, and outputs DAc on pin J3-9
//Fs = 25kHz




// Included Files
#include "F28x_Project.h"
#include "math.h"

//
// Function Prototypes
interrupt void AdcISR(void);
extern void DelayUs(Uint16);

//
// Defines
#define pi 3.14159265
//
// Variables
float32 Vref = 3.0;
float32 Vmea = 0.0;
float32 myInput[400]; //Number of samples is 400
float32 myOutput[400];
Uint32 count = 0;
float32 Vcmd = 2.1;
float32 Vfilt = 2.0;
float32 Vufilt = 2.1;
Uint32 t = 0;

float32 Vinprevious1 = 0.0;
float32 Vinprevious2 = 0.0;
float32 Voutprevious1 = 0.0;
float32 Voutprevious2 = 0.0;

float32 A= .2513272;
float32 B= 0.97;

float32 a1;
float32 a2;
float32 b1;
float32 b2;

void main(void)
{
    //notch filter calculations
    a1 = -2 *B*cos(A);
    a2 = B*B;
    b1 = -2*cos(A);
    b2 = 1;

    DINT; //Disable Interrupts
    EALLOW; //Macro for enabling writing to protected registers
    WdRegs.WDCR.all = 0b0000000001101000;//Setting bit 6 to 1 disables the watchdog. to write successfully, bits 3-5 must be 1,0,1, respectively
    //setting clock rate manually
    ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 0;// INTOSC2 fosc = 10 MHz
    ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 0; //Bypass PLL until Steady State is Achieved
    ClkCfgRegs.SYSCLKDIVSEL.all = 0b0;//Want division by 1
    ClkCfgRegs.SYSPLLMULT.all = 20; // want 200MHz, multiply by 20 fcpu = 200 Mhz
    while(ClkCfgRegs.SYSPLLSTS.bit.LOCKS != 1); // Do NOTHING until LOCKS is 1, meaning Steady State is achieved
    ClkCfgRegs.SYSCLKDIVSEL.all = 0+1; // Add 1 to SYSCLKDIVSEL Register before switching to PLL, so as to prevent issues w/current
    ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 1; //Switch to Phase Locked Loop (PLL)
    ClkCfgRegs.SYSCLKDIVSEL.all = 0; //Set DIVSEL back to normal

    //Set the Timer scale factor
    CpuTimer0Regs.TCR.bit.TSS = 0x1; //stop the timer by writing 1
    CpuTimer0Regs.TCR.bit.TRB = 0x1; //load the timer by writing 1
    CpuTimer0Regs.TCR.bit.TIE = 0x1; //enable interrupt by writing 1. Every timer period sends an interrupt.
    CpuTimer0Regs.PRD.all = 7999; // set the scale factor to 2000 (PRD + 1) ftmr = 25 khz

    //Enable and register ADC interrupts with the PIE system
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1; //Set ENPIE to 1 to enable peripheral interrupts
    IER = 0b1; //Enabling proper group for CPU-Level Interrupts
    PieVectTable.ADCA1_INT = &AdcISR; //Putting the address of the ISR into the Vector Table
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1; // use Table 2-2 in Tech Ref Manual to find ADCA4 PIE Designation

    //Initialize DAC Registers
    CpuSysRegs.PCLKCR16.bit.DAC_A = 1; //Turn on DAC Clock
    asm(" NOP"); asm(" NOP"); //2 NOPs for Delay
    DacaRegs.DACCTL.bit.DACREFSEL = 1; //Select DAC Module ref voltage VREFHI
    DacaRegs.DACOUTEN.bit.DACOUTEN = 1; //Enable DAC module output on bit 0
    DacaRegs.DACVALS.all = 4096.0*Vcmd/Vref; // Set Initial Value to 4096 * (Vcmd/Vref); Vcmd = Vin at t=0;
    //For Pin J 3-9 (DACB)
    CpuSysRegs.PCLKCR16.bit.DAC_B = 1; //Turn on DAC Clock
     asm(" NOP"); asm(" NOP"); //2 NOPs for Delay
    DacbRegs.DACCTL.bit.DACREFSEL = 1;
    DacbRegs.DACOUTEN.bit.DACOUTEN = 1;
    DacbRegs.DACVALS.all = 4096.0*Vfilt/Vref;


    //Initialize ADC Registers
    CpuSysRegs.PCLKCR13.bit.ADC_A = 0b1; //turn ON ADC module clock signal
    asm(" NOP"); asm(" NOP");
    AdcaRegs.ADCCTL2.bit.PRESCALE = 0b0110; //set internal clock frequency to 1/4 fclk,cpu
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1; //power up analog power supply
    DelayUs(500);
    //configure the ADC conversions [10.4.2.18]
    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 0x1; //define trigger source as CPU1 Timer0 (see definition above)
    AdcaRegs.ADCSOC1CTL.bit.CHSEL = 0x4; //define input pin for ADCIN4 (J7-9)
    AdcaRegs.ADCSOC1CTL.bit.ACQPS = 39;  //System Clock is 5ns wide. ADC ACq. time is 200ns. This is 40 clock cycles, meaning this value is 39

   //For Pin J7-4 (ADCINA2):
    AdcaRegs.ADCSOC2CTL.bit.TRIGSEL = 0x1; //define trigger source as CPU1 Timer0 (see definition above)
    AdcaRegs.ADCSOC2CTL.bit.CHSEL = 0x2; //define input pin for (J7-4)
    AdcaRegs.ADCSOC2CTL.bit.ACQPS = 39;  //System Clock is 5ns wide. ADC ACq. time is 200ns. This is 40 clock cycles, meaning this value is 39

    //configure and enable the interrupts
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 0b1; //ADC Interrupt Pulse Position occurs at EOC [10.4.2.1]
    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0x2; //Set trigger for ADCINT2 to EOC2 [10.4.2.9]
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 0b1; //enable ADCINT1 at EOC


    CpuTimer0Regs.TCR.bit.TSS = 0x0; //start the timer by writing 0
    WdRegs.WDCR.all = 0b0000000000101000; // writing 0 to bit 6, enabling watchdog timer
    EDIS;//Macro for disabling writing to protected registers
    EINT;   //Globally enable CPU interrupts
    while(1) {
        EALLOW; //SERVICING THE TIMER
        WdRegs.WDKEY.all = 0x0055;
        WdRegs.WDKEY.all = 0x00AA; //disabling counter
        EDIS;
    }
}

interrupt void AdcISR(void) {
    PieCtrlRegs.PIEACK.all = M_INT1; //Use the M_1NT10 macro for Interrupt group 1, writing to the PIEACK Register
    if (t < 100) {
    DacaRegs.DACVALS.all = 4096.0*Vcmd/Vref;
    //write to DAC
    Vufilt = AdcaResultRegs.ADCRESULT2 * Vref / 4096; //Measured input voltage from unsigned integer value read (after ADC completes SOC1 conversion)

    Vmea = AdcaResultRegs.ADCRESULT1 * Vref / 4096; //read from J7-9

    //transfer function
    Vfilt = Vufilt + b1*Vinprevious1 + b2*Vinprevious2 - a1 *Voutprevious1 - a2 * Voutprevious2;

    //update values
    Vinprevious2 = Vinprevious1;
    Vinprevious1 = Vufilt;
    Voutprevious2 = Voutprevious1;
    Voutprevious1 = Vfilt;

    //write to J3-9
    //DacbRegs.DACVALS.all = 4096.0*Vfilt/Vref; //for testing with filter
    DacbRegs.DACVALS.all = 4096.0*Vufilt/Vref;  //for testing without filter

    if (count<400){
    myOutput[count] = Vmea;
    //myInput[count] = Vcmd;  //change to Vcmd for generated signal demo... ONLY HAVE ONE OF THESE NEXT TWO LINES RUNNING
    myInput[count] = Vufilt; //change to Vufilt for microphone demo... ONLY HAVE ONE OF THESE NEXT TWO LINES RUNNING
    }
    t++;
    count++;
    Vcmd = 1.5 + 0.5*cos(2.0*pi*1000.0*(float32)(t)/100000) + 0.1*cos(2.0*pi*4000.0*(float32)(t)/100000);
    }
    if (t == 100) {
        t = 0;
    }
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //Clears Interrupt Flag Bit, signifying interrupt job is done on this routine cycle

}

//
// End of file
//