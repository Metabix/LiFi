/* 
 * File:   init.h
 * Author: C74305
 *
 * Created on March 9, 2023, 3:40 PM
 */

#ifndef INIT_H
#define	INIT_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* INIT_H */


static void init (void)
{
    ANSELFbits.ANSELF3 = 0;                                                     //led f3 port setting it to digital
    TRISFbits.TRISF3 = 0; 
    ANSELBbits.ANSELB1= 0;                                                      //laser b1 port
    TRISBbits.TRISB1= 0;
    
    //UART TX and RX
    ANSELFbits.ANSELF0 = 0;                                                     //tx digital 
    ANSELFbits.ANSELF1 = 0;                                                     //rx
    TRISFbits.TRISF0 = 0;                                                       //setting tx output 0
    TRISFbits.TRISF1 = 1;                                                       //setting rx input 1
    
    //DSM out 
    ANSELDbits.ANSELD2 = 0;                                                     //f2 as dsm_out
    TRISDbits.TRISD2 = 0;                                                       // setting output   
    
    //ADC
    ANSELAbits.ANSELA0 = 1;
    TRISAbits.TRISA0 = 1;
    
    //CMP
    ANSELAbits.ANSELA2 = 1;
    TRISAbits.TRISA2 =1;
}