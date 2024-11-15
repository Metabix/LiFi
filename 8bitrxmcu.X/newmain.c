/*
 * File:   newmain.c
 * Author: C74305
 *
 * Created on February 24, 2023, 4:30 PM
 */



// PIC18F47Q10 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config FEXTOSC = OFF    // External Oscillator mode Selection bits (Oscillator not enabled)
#pragma config RSTOSC = HFINTOSC_1MHZ// Power-up default value for COSC bits (HFINTOSC with HFFRQ = 4 MHz and CDIV = 4:1)

// CONFIG1H
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled)
#pragma config CSWEN = ON       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)

// CONFIG2L
#pragma config MCLRE = EXTMCLR  // Master Clear Enable bit (MCLR pin (RE3) is MCLR)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (Power up timer disabled)
#pragma config LPBOREN = OFF    // Low-power BOR enable bit (Low power BOR is disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled , SBOREN bit is ignored)

// CONFIG2H
#pragma config BORV = VBOR_190  // Brown Out Reset Voltage selection bits (Brown-out Reset Voltage (VBOR) set to 1.90V)
#pragma config ZCD = OFF        // ZCD Disable bit (ZCD disabled. ZCD can be enabled by setting the ZCDSEN bit of ZCDCON)
#pragma config PPS1WAY = ON     // PPSLOCK bit One-Way Set Enable bit (PPSLOCK bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle)
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Extended Instruction Set and Indexed Addressing Mode disabled)

// CONFIG3L
#pragma config WDTCPS = WDTCPS_31// WDT Period Select bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = OFF       // WDT operating mode (WDT Disabled)

// CONFIG3H
#pragma config WDTCWS = WDTCWS_7// WDT Window Select bits (window always open (100%); software control; keyed access not required)
#pragma config WDTCCS = SC      // WDT input clock selector (Software Control)

// CONFIG4L
#pragma config WRT0 = OFF       // Write Protection Block 0 (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection Block 1 (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection Block 2 (Block 2 (008000-00BFFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection Block 3 (Block 3 (00C000-00FFFFh) not write-protected)
#pragma config WRT4 = OFF       // Write Protection Block 4 (Block 4 (010000-013FFFh) not write-protected)
#pragma config WRT5 = OFF       // Write Protection Block 5 (Block 5 (014000-017FFFh) not write-protected)
#pragma config WRT6 = OFF       // Write Protection Block 6 (Block 6 (018000-01BFFFh) not write-protected)
#pragma config WRT7 = OFF       // Write Protection Block 7 (Block 7 (01C000-01FFFFh) not write-protected)

// CONFIG4H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-30000Bh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)
#pragma config SCANE = ON       // Scanner Enable bit (Scanner module is available for use, SCANMD bit can control the module)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (Low voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored)

// CONFIG5L
#pragma config CP = OFF         // UserNVM Program Memory Code Protection bit (UserNVM code protection disabled)
#pragma config CPD = OFF        // DataNVM Memory Code Protection bit (DataNVM code protection disabled)

// CONFIG5H

// CONFIG6L
#pragma config EBTR0 = OFF      // Table Read Protection Block 0 (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection Block 1 (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection Block 2 (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection Block 3 (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR4 = OFF      // Table Read Protection Block 4 (Block 4 (010000-013FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR5 = OFF      // Table Read Protection Block 5 (Block 5 (014000-017FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR6 = OFF      // Table Read Protection Block 6 (Block 6 (018000-01BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR7 = OFF      // Table Read Protection Block 7 (Block 7 (01C000-01FFFFh) not protected from table reads executed in other blocks)

// CONFIG6H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
#include <string.h>
#define _XTAL_FREQ 8000000

static void init(void);
static void ADC_init(void);
void blink(void);
unsigned int ADC(void);
static void UART_write(uint8_t txData);

void main(void) {
    unsigned int ADC_Result;
    char msg[] = "UU";
    init();
    blink();
    ADC_init();
    while(1)
    {
       /* ADC_Result = ADC();
        for(uint8_t i = 0; i < strlen(msg); i++) 
        {
            UART_write(msg[i]);
            
        }*/
        if(ADC_Result >= 0.5)
        {
            LATBbits.LATB7 = 1;         //store the ADC value to a register
        }
        else
        {
            LATBbits.LATB7 = 0;
        }
        
    }
    return;
}

static void init(void)
{
    ANSELAbits.ANSELA4 = 0;     //led f3 port setting it to digital
    TRISAbits.TRISA4 = 0;       //setting output
    ANSELAbits.ANSELA6 = 0;     //laser b1 port
    TRISAbits.TRISA6 = 0;
    ANSELBbits.ANSELB7 = 0;     //laser b1 port
    TRISBbits.TRISB7 = 0;
    
    ANSELBbits.ANSELB4 = 1;     //  setting analog for ldr  (ADC Positive Channel Selection Register) 001100 RB4/ANB4
    TRISBbits.TRISB4 = 1;       //  setting input
    
    //UART TX and RX
    ANSELCbits.ANSELC4 = 0; //tx digital 
    ANSELCbits.ANSELC7 = 0; //rx
    TRISCbits.TRISC4 = 0; //setting tx output 0
    TRISCbits.TRISC7 = 1; //setting rx input 1
}

static void UART_init(void)
{
    SP1BRGH = 0x00;
    SP1BRGL = 0x01; //0x09 EUSART1 (TX/CK) 
    RC4PPS = 0x09;  //setting UART tx port.
    TX1STAbits.TXEN = 1;
    TX1STAbits.SYNC = 0;
    RC1STAbits.SPEN =1;
}

static void ADC_init(void)
{
    
    ADCON0bits.ADFM = 1;        //right justify 
    ADCON0bits.ADCS = 0;        //set clock
    //ADCLKbits.ADCS = 0x07;
    ADPCHbits.ADPCH = 0x0C;     //set RB4 as analog channel
    RB4PPS = 0x0C;              //set adc pin
    ADREFbits.ADPREF = 00;
    ADREFbits.ADNREF = 0;
    ADCON0bits.ADON = 1;        //set enable
    //ADCON0bits.ADGO = 1         //software enable conversation starts 
}   

unsigned int ADC(void)
{
    unsigned int result;
    
    ADCON0bits.GO = 1;
    while (ADCON0bits.GO);              //Wait for conversion done
    result = ((ADRESH << 8) + ADRESL);    //Read result
    return result;
}

void blink (void)
{
    LATAbits.LATA4 = 0; 
    LATAbits.LATA6 = 0; 
    __delay_ms(500);
    LATAbits.LATA4 = 1; 
    LATAbits.LATA6 = 1; 
    __delay_ms(500);
}

static void UART_write(uint8_t txData)//whenever the UxTIF is 1 it will write a new byte.
{
    while(0 == PIR3bits.TX1IF)
    {
        ;
    }
    
    TX1REG = txData;
}