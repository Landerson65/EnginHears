//
// Included Files
//
#include "F28x_Project.h"
#include "math.h"
#include "F2837xS_dma.h"
//
// Function Prototypes
//
interrupt void AdcISR(void);
extern void DelayUs(Uint16);
//
// Defines
#define pi 3.14159265
//
// Globals

float32 Vref = 3.0;
float32 Vmea = 0.0;
Uint32 count = 0;
float32 Vcmd = 2.1;
float32 Vfilt = 2.0;
float32 Vufilt = 2.1;
Uint32 t = 0;

float32 first = 1000.0;
float32 second = 1500.0;
float32 third = 2550.0;
float32 fourth = 5000.0;
float32 T = 1.0/25000.0;
float32 gain = 0.0;
float32 g = 50.0;
float32 firstC;
float32 secondC;
float32 secondC2;
float32 thirdC;
float32 thirdC2;
float32 fifthC;
float32 fifthC2;
float32 fs = 25000.0;
int k = 0;
float32 kk = 0.0;
float32 gainArray[100];


void main(void)
{
    DINT; //Disable Interrupts
    EALLOW; //Macro for enabling writing to protected registers
    WdRegs.WDCR.all = 0b0000000001101000;//Setting bit 6 to 1 disables the watchdog. to write successfully, bits 3-5 must be 1,0,1, respectively
    //setting clock rate manually: [2.7.6.2] modified for class
    ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 0;// INTOSC2 fosc = 10 MHz
    ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 0; //Bypass PLL until Steady State is Achieved
    ClkCfgRegs.SYSCLKDIVSEL.all = 0b0;//Want division by 1
    ClkCfgRegs.SYSPLLMULT.all = 20; // want 200MHz, multiply by 20
    while(ClkCfgRegs.SYSPLLSTS.bit.LOCKS != 1); // Do NOTHING until LOCKS is 1, meaning Steady State is achieved
    ClkCfgRegs.SYSCLKDIVSEL.all = 0+1; // Add 1 to SYSCLKDIVSEL Register before switching to PLL, so as to prevent issues w/current
    ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 1; //Switch to Phase Locked Loop (PLL)
    ClkCfgRegs.SYSCLKDIVSEL.all = 0; //Set DIVSEL back to normal

    //Set the Timer scale factor [2.15.2.3]
    CpuTimer0Regs.TCR.bit.TSS = 0x1; //stop the timer by writing 1
    CpuTimer0Regs.TCR.bit.TRB = 0x1; //load the timer by writing 1
    CpuTimer0Regs.TCR.bit.TIE = 0x1; //enable interrupt by writing 1. Every timer period sends an interrupt.
    CpuTimer0Regs.PRD.all = 7999; // set the scale factor to 8000 (PRD + 1) ftmr = 25kHz

    //Enable and register ADC interrupts with the PIE system
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1; //Set ENPIE to 1 to enable peripheral interrupts
    IER = 0b1; //Enabling proper group for CPU-Level Interrupts [CPU Instruction Set 3.2.2]
    PieVectTable.ADCA1_INT = &AdcISR; //Putting the address of the ISR into the Vector Table [See Lab 3 Sec. 2.2.1]
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1; // use Table 2-2 in Tech Ref Manual to find ADCA4 PIE Designation

    //Initialize DAC Registers
    CpuSysRegs.PCLKCR16.bit.DAC_A = 1; //Turn on DAC Clock
    asm(" NOP"); asm(" NOP"); //2 NOPs for Delay
    DacaRegs.DACCTL.bit.DACREFSEL = 1; //Select DAC Module ref voltage VREFHI [11.4.2.2]
    DacaRegs.DACOUTEN.bit.DACOUTEN = 1; //Enable DAC module output on bit 0
    DacaRegs.DACVALS.all = 4096.0*Vcmd/Vref; // Set Initial Value to 4096 * (Vcmd/Vref); Vcmd = Vin at t=0;
    //For Pin J 3-9 (DACB)
    CpuSysRegs.PCLKCR16.bit.DAC_B = 1; //Turn on DAC Clock
     asm(" NOP"); asm(" NOP"); //2 NOPs for Delay
    DacbRegs.DACCTL.bit.DACREFSEL = 1;
    DacbRegs.DACOUTEN.bit.DACOUTEN = 1;
    DacbRegs.DACVALS.all = 4096.0*Vfilt/Vref;


    //Initialize ADC Registers
    CpuSysRegs.PCLKCR13.bit.ADC_A = 0b1; //turn ON ADC module clock signal [2.15.11.17]
    asm(" NOP"); asm(" NOP");
    AdcaRegs.ADCCTL2.bit.PRESCALE = 0b0110; //set internal clock frequency to 1/4 fclk,cpu [10.4.2.2]
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1; //power up analog power supply [10.4.2.1]
    DelayUs(500);
    //configure the ADC conversions [10.4.2.18]
    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 0x1; //define trigger source as CPU1 Timer0 (see definition above)
    AdcaRegs.ADCSOC1CTL.bit.CHSEL = 0x4; //define input pin for ADCIN4 (J7-9)
    AdcaRegs.ADCSOC1CTL.bit.ACQPS = 39;  //System Clock is 5ns wide. ADC ACq. time is 200ns. This is 40 clock cycles, meaning this value is 39 [Table 10-31]

   //For Pin J7-4 (ADCINA2):

    AdcaRegs.ADCSOC2CTL.bit.TRIGSEL = 0x1; //define trigger source as CPU1 Timer0 (see definition above)
    AdcaRegs.ADCSOC2CTL.bit.CHSEL = 0x2; //define input pin for (J7-4)
    AdcaRegs.ADCSOC2CTL.bit.ACQPS = 39;  //System Clock is 5ns wide. ADC ACq. time is 200ns. This is 40 clock cycles, meaning this value is 39 [Table 10-31]

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
    Vmea = AdcaResultRegs.ADCRESULT1 * Vref / 4096; //read from J7-4

    //TODO: take fft of input array

    //filter function
    //set gain for first stage of frequencies
    firstC = 0.3 * (g - 1.0) / first;
    if(k/100.0 <= 1500/25000.0)
    {
        gain = firstC * k/ (100.0*T) + 1.0;
        gainArray[k]= gain;
        gainArray[99-k] = gain;
    }

    //set gain for third stage of frequencies
    secondC = firstC*first +1.0;
    secondC2 = (second-first)/5.0;
    thirdC = 1.0 + (secondC-1.0)*exp(-second/secondC2);
    thirdC2 = (third-second)/5.0;
    if(k/100.0 <= third/25000.0 & k> 6){

         gain = g + (thirdC-g)*exp(-((k/(100.0*T)-second))/thirdC2);
         if(k ==0){
            kk = gain;
         }
         gainArray[k]= gain;
         gainArray[99-k] = gain;
    }
    //set gain for fourth stage of frequencies
    if(k/100.0 <= fourth/25000.0 & k > 10){
           gain = g;
           gainArray[k]= gain;
           gainArray[99-k] = gain;
      }
    //set gain for fifth stage of frequencies
    fifthC = g;
    fifthC2 = (25000.0/2.0-fourth)/5.0;
    if(k/100.0 <= .5 & k > 20){
           gain = 1.0 + (fifthC-1.0)*exp(-((k/(100.0*T))-fourth)/fifthC2);
           gainArray[k]= gain;
           gainArray[99-k] = gain;
      }

    //TODO: Apply filter to fft
    //TODO: ifft

    //write to J3-9
    DacbRegs.DACVALS.all = 4096.0*Vufilt/Vref;

    t++;
    count++;
    k++;
    }
    if (t == 100) {
        t = 0;
        k = 0;
        count = 0;
    }

    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //Clears Interrupt Flag Bit, signifying interrupt job is done on this routine cycle

}

//
// End of file
//
