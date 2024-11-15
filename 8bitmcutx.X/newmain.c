/*
 * File:   newmain.c
 * Author: C74305
 *
 * Created on February 22, 2023, 10:14 AM
 */


// PIC18F57Q43 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FEXTOSC = OFF    // External Oscillator Selection (Oscillator not enabled)
#pragma config RSTOSC = HFINTOSC_1MHZ// Reset Oscillator Selection (HFINTOSC with HFFRQ = 4 MHz and CDIV = 4:1)

// CONFIG2
#pragma config CLKOUTEN = OFF   // Clock out Enable bit (CLKOUT function is disabled)
#pragma config PR1WAY = ON      // PRLOCKED One-Way Set Enable bit (PRLOCKED bit can be cleared and set only once)
#pragma config CSWEN = ON       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)

// CONFIG3
#pragma config MCLRE = EXTMCLR  // MCLR Enable bit (If LVP = 0, MCLR pin is MCLR; If LVP = 1, RE3 pin function is MCLR )
#pragma config PWRTS = PWRT_OFF // Power-up timer selection bits (PWRT is disabled)
#pragma config MVECEN = OFF     // Multi-vector enable bit (Interrupt contoller does not use vector table to prioritze interrupts)
#pragma config IVT1WAY = ON     // IVTLOCK bit One-way set enable bit (IVTLOCKED bit can be cleared and set only once)
#pragma config LPBOREN = OFF    // Low Power BOR Enable bit (Low-Power BOR disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled , SBOREN bit is ignored)

// CONFIG4
#pragma config BORV = VBOR_1P9  // Brown-out Reset Voltage Selection bits (Brown-out Reset Voltage (VBOR) set to 1.9V)
#pragma config ZCD = OFF        // ZCD Disable bit (ZCD module is disabled. ZCD can be enabled by setting the ZCDSEN bit of ZCDCON)
#pragma config PPS1WAY = ON     // PPSLOCK bit One-Way Set Enable bit (PPSLOCKED bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle)
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (Low voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Extended Instruction Set and Indexed Addressing Mode disabled)

// CONFIG5
#pragma config WDTCPS = WDTCPS_0// WDT Period selection bits (Divider ratio 1:32)
#pragma config WDTE = OFF       // WDT operating mode (WDT Disabled; SWDTEN is ignored)

// CONFIG6
#pragma config WDTCWS = WDTCWS_7// WDT Window Select bits (window always open (100%); software control; keyed access not required)
#pragma config WDTCCS = SC      // WDT input clock selector (Software Control)

// CONFIG7
#pragma config BBSIZE = BBSIZE_512// Boot Block Size selection bits (Boot Block size is 512 words)
#pragma config BBEN = OFF       // Boot Block enable bit (Boot block disabled)
#pragma config SAFEN = OFF      // Storage Area Flash enable bit (SAF disabled)
#pragma config DEBUG = OFF      // Background Debugger (Background Debugger disabled)

// CONFIG8
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block not Write protected)
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers not Write protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not Write protected)
#pragma config WRTSAF = OFF     // SAF Write protection bit (SAF not Write Protected)
#pragma config WRTAPP = OFF     // Application Block write protection bit (Application Block not write protected)

// CONFIG10
#pragma config CP = OFF         // PFM and Data EEPROM Code Protection bit (PFM and Data EEPROM code protection disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "uart.h"
#include "dsm.h"
#include "init.h"
#define _XTAL_FREQ 8000000


static void ADC_init(void);
uint8_t ADC(void);
void blink(void);
static void CMP(void);


int ADC_Value=0;
uint8_t ADCL=0;
uint8_t ADCH=0;
uint16_t mean=0;

void main(void) {
    init();
    UART_init();
    DSM_init();
    ADC_init();
    //CMP();
    //ADCH = ADRESH;
    
    char msg[] = "ADC value: ";
    char ADC_array[5];   
    uint16_t adcsum = 0;
    int stage = 0;
    puts("Hello world");
 
    while(1)
    {
        MD1CON0bits.EN =1;                                                      //enable DSM      
        //UART_write(0x55);                                                       //start new line
        ADCL = ADC();
        
//        for(uint8_t i = 0; i < strlen(msg); i++) 
//        {
//            UART_write(msg[i]);
//        }
        UART_write(ADCL);             
        //blink();

    }
    return;
}


static void ADC_init(void)
{
    ADPCH = 0x00 ;                                                              //connected to RC4 0b010100 channel 0
    ADCON2bits.MD = 0b001;
    ADCON0bits.FM = 1;                                                          //right justify
    ADCON0bits.CS = 1;                                                          //ADCRC Clock   Clock supplied by FOSC, divided according to ADCLK register
    ADCLKbits.ADCS = 0b0111111;                                                  //fOSC/2
    ADREFbits.PREF = 00;                                                        //vss
    ADREFbits.NREF = 0;                                                         //vdd
    ADCON1bits.DSEN = 1;
    //ADCON0bits.CONT = 1;
    //PIR2bits.ADTIF = 1;
    //ADCON3bits.SOI = 1;
//    ADACTbits.ACT = 0b111110;
    ADCON0bits.ON = 1;                                                          //enable ADC

}


uint8_t  ADC(void)
{                                                     
    ADCON0bits.GO = 1;                                                          //Start conversion  
    while (ADCON0bits.GO);                                                      //Wait for conversion done
    
    if(ADCL <= 0xDA)
        {
                    LATBbits.LATB1=0;
        }
    else
        {
                    LATBbits.LATB1=1;
        }
    
    return(ADRESL);                                             //Read result
}


static void CMP(void)
{
    T1CLK = 00011;
    T1CONbits.ON = 1;
    
    
    CM1CON0bits.C1EN = 1;
    CM1CON0bits.C1POL = 0;
    CM1CON0bits.C1SYNC = 1;
    CM1CON1bits.C1INTP = 1;
    CM1PCHbits.PCH = 0x00;                                                      //connected to CxIN0+ connected to 
    CM1NCHbits.NCH = 0x07;                                                      //connected to vss
}


void blink(void)
{
    LATFbits.LATF3 = 0; 
    LATBbits.LATB1 = 0; 
    __delay_ms(500);
    LATFbits.LATF3 = 1; 
    LATBbits.LATB1 = 1; 
    __delay_ms(500);
}