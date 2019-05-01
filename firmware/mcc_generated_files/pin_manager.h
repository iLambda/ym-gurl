/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC18F47K40
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.00
        MPLAB 	          :  MPLAB X 5.10	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IC aliases
#define IC_TRIS                 TRISAbits.TRISA0
#define IC_LAT                  LATAbits.LATA0
#define IC_PORT                 PORTAbits.RA0
#define IC_WPU                  WPUAbits.WPUA0
#define IC_OD                   ODCONAbits.ODCA0
#define IC_ANS                  ANSELAbits.ANSELA0
#define IC_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define IC_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define IC_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define IC_GetValue()           PORTAbits.RA0
#define IC_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define IC_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define IC_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define IC_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define IC_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define IC_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define IC_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define IC_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set CS aliases
#define CS_TRIS                 TRISAbits.TRISA1
#define CS_LAT                  LATAbits.LATA1
#define CS_PORT                 PORTAbits.RA1
#define CS_WPU                  WPUAbits.WPUA1
#define CS_OD                   ODCONAbits.ODCA1
#define CS_ANS                  ANSELAbits.ANSELA1
#define CS_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define CS_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define CS_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define CS_GetValue()           PORTAbits.RA1
#define CS_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define CS_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define CS_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define CS_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define CS_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define CS_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define CS_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define CS_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set WR aliases
#define WR_TRIS                 TRISAbits.TRISA2
#define WR_LAT                  LATAbits.LATA2
#define WR_PORT                 PORTAbits.RA2
#define WR_WPU                  WPUAbits.WPUA2
#define WR_OD                   ODCONAbits.ODCA2
#define WR_ANS                  ANSELAbits.ANSELA2
#define WR_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define WR_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define WR_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define WR_GetValue()           PORTAbits.RA2
#define WR_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define WR_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define WR_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define WR_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define WR_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define WR_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define WR_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define WR_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set RD aliases
#define RD_TRIS                 TRISAbits.TRISA3
#define RD_LAT                  LATAbits.LATA3
#define RD_PORT                 PORTAbits.RA3
#define RD_WPU                  WPUAbits.WPUA3
#define RD_OD                   ODCONAbits.ODCA3
#define RD_ANS                  ANSELAbits.ANSELA3
#define RD_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define RD_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define RD_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define RD_GetValue()           PORTAbits.RA3
#define RD_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define RD_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define RD_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define RD_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define RD_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define RD_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define RD_SetAnalogMode()      do { ANSELAbits.ANSELA3 = 1; } while(0)
#define RD_SetDigitalMode()     do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set A0 aliases
#define A0_TRIS                 TRISAbits.TRISA4
#define A0_LAT                  LATAbits.LATA4
#define A0_PORT                 PORTAbits.RA4
#define A0_WPU                  WPUAbits.WPUA4
#define A0_OD                   ODCONAbits.ODCA4
#define A0_ANS                  ANSELAbits.ANSELA4
#define A0_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define A0_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define A0_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define A0_GetValue()           PORTAbits.RA4
#define A0_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define A0_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define A0_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define A0_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define A0_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define A0_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define A0_SetAnalogMode()      do { ANSELAbits.ANSELA4 = 1; } while(0)
#define A0_SetDigitalMode()     do { ANSELAbits.ANSELA4 = 0; } while(0)

// get/set A1 aliases
#define A1_TRIS                 TRISAbits.TRISA5
#define A1_LAT                  LATAbits.LATA5
#define A1_PORT                 PORTAbits.RA5
#define A1_WPU                  WPUAbits.WPUA5
#define A1_OD                   ODCONAbits.ODCA5
#define A1_ANS                  ANSELAbits.ANSELA5
#define A1_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define A1_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define A1_SetValue(v)          do { LATAbits.LATA5 = (v); } while(0)
#define A1_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define A1_GetValue()           PORTAbits.RA5
#define A1_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define A1_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define A1_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define A1_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define A1_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define A1_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define A1_SetAnalogMode()      do { ANSELAbits.ANSELA5 = 1; } while(0)
#define A1_SetDigitalMode()     do { ANSELAbits.ANSELA5 = 0; } while(0)

// get/set D0 aliases
#define D0_TRIS                 TRISBbits.TRISB0
#define D0_LAT                  LATBbits.LATB0
#define D0_PORT                 PORTBbits.RB0
#define D0_WPU                  WPUBbits.WPUB0
#define D0_OD                   ODCONBbits.ODCB0
#define D0_ANS                  ANSELBbits.ANSELB0
#define D0_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define D0_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define D0_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define D0_GetValue()           PORTBbits.RB0
#define D0_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define D0_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define D0_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define D0_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define D0_SetPushPull()        do { ODCONBbits.ODCB0 = 0; } while(0)
#define D0_SetOpenDrain()       do { ODCONBbits.ODCB0 = 1; } while(0)
#define D0_SetAnalogMode()      do { ANSELBbits.ANSELB0 = 1; } while(0)
#define D0_SetDigitalMode()     do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set D1 aliases
#define D1_TRIS                 TRISBbits.TRISB1
#define D1_LAT                  LATBbits.LATB1
#define D1_PORT                 PORTBbits.RB1
#define D1_WPU                  WPUBbits.WPUB1
#define D1_OD                   ODCONBbits.ODCB1
#define D1_ANS                  ANSELBbits.ANSELB1
#define D1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define D1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define D1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define D1_GetValue()           PORTBbits.RB1
#define D1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define D1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define D1_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define D1_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define D1_SetPushPull()        do { ODCONBbits.ODCB1 = 0; } while(0)
#define D1_SetOpenDrain()       do { ODCONBbits.ODCB1 = 1; } while(0)
#define D1_SetAnalogMode()      do { ANSELBbits.ANSELB1 = 1; } while(0)
#define D1_SetDigitalMode()     do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set D2 aliases
#define D2_TRIS                 TRISBbits.TRISB2
#define D2_LAT                  LATBbits.LATB2
#define D2_PORT                 PORTBbits.RB2
#define D2_WPU                  WPUBbits.WPUB2
#define D2_OD                   ODCONBbits.ODCB2
#define D2_ANS                  ANSELBbits.ANSELB2
#define D2_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define D2_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define D2_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define D2_GetValue()           PORTBbits.RB2
#define D2_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define D2_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define D2_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define D2_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define D2_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define D2_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define D2_SetAnalogMode()      do { ANSELBbits.ANSELB2 = 1; } while(0)
#define D2_SetDigitalMode()     do { ANSELBbits.ANSELB2 = 0; } while(0)

// get/set D3 aliases
#define D3_TRIS                 TRISBbits.TRISB3
#define D3_LAT                  LATBbits.LATB3
#define D3_PORT                 PORTBbits.RB3
#define D3_WPU                  WPUBbits.WPUB3
#define D3_OD                   ODCONBbits.ODCB3
#define D3_ANS                  ANSELBbits.ANSELB3
#define D3_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define D3_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define D3_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define D3_GetValue()           PORTBbits.RB3
#define D3_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define D3_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define D3_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define D3_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define D3_SetPushPull()        do { ODCONBbits.ODCB3 = 0; } while(0)
#define D3_SetOpenDrain()       do { ODCONBbits.ODCB3 = 1; } while(0)
#define D3_SetAnalogMode()      do { ANSELBbits.ANSELB3 = 1; } while(0)
#define D3_SetDigitalMode()     do { ANSELBbits.ANSELB3 = 0; } while(0)

// get/set D4 aliases
#define D4_TRIS                 TRISBbits.TRISB4
#define D4_LAT                  LATBbits.LATB4
#define D4_PORT                 PORTBbits.RB4
#define D4_WPU                  WPUBbits.WPUB4
#define D4_OD                   ODCONBbits.ODCB4
#define D4_ANS                  ANSELBbits.ANSELB4
#define D4_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define D4_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define D4_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define D4_GetValue()           PORTBbits.RB4
#define D4_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define D4_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define D4_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define D4_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define D4_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define D4_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define D4_SetAnalogMode()      do { ANSELBbits.ANSELB4 = 1; } while(0)
#define D4_SetDigitalMode()     do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set D5 aliases
#define D5_TRIS                 TRISBbits.TRISB5
#define D5_LAT                  LATBbits.LATB5
#define D5_PORT                 PORTBbits.RB5
#define D5_WPU                  WPUBbits.WPUB5
#define D5_OD                   ODCONBbits.ODCB5
#define D5_ANS                  ANSELBbits.ANSELB5
#define D5_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define D5_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define D5_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define D5_GetValue()           PORTBbits.RB5
#define D5_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define D5_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define D5_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define D5_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define D5_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define D5_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define D5_SetAnalogMode()      do { ANSELBbits.ANSELB5 = 1; } while(0)
#define D5_SetDigitalMode()     do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set D6 aliases
#define D6_TRIS                 TRISBbits.TRISB6
#define D6_LAT                  LATBbits.LATB6
#define D6_PORT                 PORTBbits.RB6
#define D6_WPU                  WPUBbits.WPUB6
#define D6_OD                   ODCONBbits.ODCB6
#define D6_ANS                  ANSELBbits.ANSELB6
#define D6_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define D6_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define D6_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define D6_GetValue()           PORTBbits.RB6
#define D6_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define D6_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define D6_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define D6_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define D6_SetPushPull()        do { ODCONBbits.ODCB6 = 0; } while(0)
#define D6_SetOpenDrain()       do { ODCONBbits.ODCB6 = 1; } while(0)
#define D6_SetAnalogMode()      do { ANSELBbits.ANSELB6 = 1; } while(0)
#define D6_SetDigitalMode()     do { ANSELBbits.ANSELB6 = 0; } while(0)

// get/set D7 aliases
#define D7_TRIS                 TRISBbits.TRISB7
#define D7_LAT                  LATBbits.LATB7
#define D7_PORT                 PORTBbits.RB7
#define D7_WPU                  WPUBbits.WPUB7
#define D7_OD                   ODCONBbits.ODCB7
#define D7_ANS                  ANSELBbits.ANSELB7
#define D7_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define D7_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define D7_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define D7_GetValue()           PORTBbits.RB7
#define D7_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define D7_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define D7_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define D7_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)
#define D7_SetPushPull()        do { ODCONBbits.ODCB7 = 0; } while(0)
#define D7_SetOpenDrain()       do { ODCONBbits.ODCB7 = 1; } while(0)
#define D7_SetAnalogMode()      do { ANSELBbits.ANSELB7 = 1; } while(0)
#define D7_SetDigitalMode()     do { ANSELBbits.ANSELB7 = 0; } while(0)

// get/set RC0 procedures
#define RC0_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define RC0_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define RC0_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define RC0_GetValue()              PORTCbits.RC0
#define RC0_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define RC0_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define RC0_SetPullup()             do { WPUCbits.WPUC0 = 1; } while(0)
#define RC0_ResetPullup()           do { WPUCbits.WPUC0 = 0; } while(0)
#define RC0_SetAnalogMode()         do { ANSELCbits.ANSELC0 = 1; } while(0)
#define RC0_SetDigitalMode()        do { ANSELCbits.ANSELC0 = 0; } while(0)

// get/set RC1 procedures
#define RC1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define RC1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define RC1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define RC1_GetValue()              PORTCbits.RC1
#define RC1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define RC1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define RC1_SetPullup()             do { WPUCbits.WPUC1 = 1; } while(0)
#define RC1_ResetPullup()           do { WPUCbits.WPUC1 = 0; } while(0)
#define RC1_SetAnalogMode()         do { ANSELCbits.ANSELC1 = 1; } while(0)
#define RC1_SetDigitalMode()        do { ANSELCbits.ANSELC1 = 0; } while(0)

// get/set SCL1 aliases
#define SCL1_TRIS                 TRISCbits.TRISC2
#define SCL1_LAT                  LATCbits.LATC2
#define SCL1_PORT                 PORTCbits.RC2
#define SCL1_WPU                  WPUCbits.WPUC2
#define SCL1_OD                   ODCONCbits.ODCC2
#define SCL1_ANS                  ANSELCbits.ANSELC2
#define SCL1_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define SCL1_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define SCL1_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define SCL1_GetValue()           PORTCbits.RC2
#define SCL1_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define SCL1_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define SCL1_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define SCL1_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define SCL1_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define SCL1_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define SCL1_SetAnalogMode()      do { ANSELCbits.ANSELC2 = 1; } while(0)
#define SCL1_SetDigitalMode()     do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set SDA1 aliases
#define SDA1_TRIS                 TRISCbits.TRISC3
#define SDA1_LAT                  LATCbits.LATC3
#define SDA1_PORT                 PORTCbits.RC3
#define SDA1_WPU                  WPUCbits.WPUC3
#define SDA1_OD                   ODCONCbits.ODCC3
#define SDA1_ANS                  ANSELCbits.ANSELC3
#define SDA1_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define SDA1_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define SDA1_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define SDA1_GetValue()           PORTCbits.RC3
#define SDA1_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define SDA1_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define SDA1_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define SDA1_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define SDA1_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define SDA1_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define SDA1_SetAnalogMode()      do { ANSELCbits.ANSELC3 = 1; } while(0)
#define SDA1_SetDigitalMode()     do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set RD0 procedures
#define RD0_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define RD0_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define RD0_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define RD0_GetValue()              PORTDbits.RD0
#define RD0_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define RD0_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define RD0_SetPullup()             do { WPUDbits.WPUD0 = 1; } while(0)
#define RD0_ResetPullup()           do { WPUDbits.WPUD0 = 0; } while(0)
#define RD0_SetAnalogMode()         do { ANSELDbits.ANSELD0 = 1; } while(0)
#define RD0_SetDigitalMode()        do { ANSELDbits.ANSELD0 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/