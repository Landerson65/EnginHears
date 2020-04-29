/** In this exercise the DMA will be configured to transfer the results directly from
       the ADC result registers to the memory buffer. ADC channel A0 will be buffered ping-pong style
       with 128 samples per buffer.
     */

int main(void)
{

   /** The DMA controller needs to be configured to buffer ADC channel A0 ping-pong style with 128
   samples per buffer. One conversion will be performed per trigger with the ADC operating in
   single sample mode.
   */

#define BURST_SIZE = 0; //1 word/burst
#define TRANSFER_SIZE = 128; //128 bursts/transfer

    //Setup DMA initialization
    InitDma(); //
    DmaRegs.DMACTRL.bit.HARDRESET = 1;  // Perform a hard reset on DMA
    asm (" nop");               // one NOP required after HARDRESET
    DmaRegs.CH1.MODE.PERINTSEL = 1; //interrupt source select is set to channel 1
    DmaRegs.CH1.MODE.PERINTE = 1; //Enable the peripheral interrupt trigger
    DmaRegs.CH1.MODE.CHINTMODE = 1; //channel interrupt generation at the start of transfer
    DmaRegs.CH1.MODE.DATASIZE = 0; //16-bit data transfers
    DmaRegs.CH1.MODE.ONESHOT = 0; //one burst per trigger
    DmaRegs.CH1.TRANSFER_SIZE = TRANSFER_SIZE;
    DmaRegs.CH1.BURST_SIZE = BURST_SIZE;
    //auto re-initialization at the end of the transfer
    DmaRegs.CH1.MODE.CHINTE = 1; //Enable the channel interrupt
    DmaClaSrcSelRegs.DMACHSRCSEL1.bit.CH1 = 1; //ADCAINT1 is the peripheral interrupt trigger source
    DmaRegs.CH1.CONTROL.ERRCLR = 1; //clear SYNCERR error
    DmaRegs.CH1.CONTROL.PERINTCLR = 1; //peripheral interrupt clear... clears event and PERINTFLG
    DmaRegs.CH1.CONTROL.RUNSTS = 1; //channel enabled to run


    //setup PIE Interrupt for DMA
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1; //Set ENPIE to 1 to enable peripheral interrupts
    IER = 0b1; //Enabling proper group for CPU-Level Interrupts
    PieVectTable.DMA_CH1_INT = &dmaISR; //Putting the address of the ISR into the Vector Table... Enable the appropriate core interrupt in the IER register?
    //change &adcISR to &dmaISR
    PieCtrlRegs.PIEIER7.bit.INTx1 = 1; // DMA ch1 PIE Designation (INT7.1)


    return 0;

}