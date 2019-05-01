/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC18F47K40
        Driver Version    :  2.00
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

#include "inc/ym2612.h"
#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    
    ym2612_init();
    
    ym2612_write(0x22, 0, 0x00); // LFO off
	ym2612_write(0x27, 0, 0x00); // Note off (channel 0)
	ym2612_write(0x28, 0, 0x01); // Note off (channel 1)
	ym2612_write(0x28, 0, 0x02); // Note off (channel 2)
	ym2612_write(0x28, 0, 0x04); // Note off (channel 3)
	ym2612_write(0x28, 0, 0x05); // Note off (channel 4)
	ym2612_write(0x28, 0, 0x06); // Note off (channel 5)
	ym2612_write(0x2B, 0, 0x00); // DAC off
	ym2612_write(0x30, 0, 0x71); //
	ym2612_write(0x34, 0, 0x0D); //
	ym2612_write(0x38, 0, 0x33); //
	ym2612_write(0x3C, 0, 0x01); // DT1/MUL
	ym2612_write(0x40, 0, 0x23); //
	ym2612_write(0x44, 0, 0x2D); //
	ym2612_write(0x48, 0, 0x26); //
	ym2612_write(0x4C, 0, 0x00); // Total level
	ym2612_write(0x50, 0, 0x5F); //
	ym2612_write(0x54, 0, 0x99); //
	ym2612_write(0x58, 0, 0x5F); //
	ym2612_write(0x5C, 0, 0x94); // RS/AR 
	ym2612_write(0x60, 0, 0x05); //
	ym2612_write(0x64, 0, 0x05); //
	ym2612_write(0x68, 0, 0x05); //
	ym2612_write(0x6C, 0, 0x07); // AM/D1R
	ym2612_write(0x70, 0, 0x02); //
	ym2612_write(0x74, 0, 0x02); //
	ym2612_write(0x78, 0, 0x02); //
	ym2612_write(0x7C, 0, 0x02); // D2R
	ym2612_write(0x80, 0, 0x11); //
	ym2612_write(0x84, 0, 0x11); //
	ym2612_write(0x88, 0, 0x11); //
	ym2612_write(0x8C, 0, 0xA6); // D1L/RR
	ym2612_write(0x90, 0, 0x00); //
	ym2612_write(0x94, 0, 0x00); //
	ym2612_write(0x98, 0, 0x00); //
	ym2612_write(0x9C, 0, 0x00); // Proprietary
	ym2612_write(0xB0, 0, 0x32); // Feedback/algorithm
	ym2612_write(0xB4, 0, 0xC0); // Both speakers on
	ym2612_write(0x28, 0, 0x00); // Key off	
    ym2612_write(0xA4, 0, 0x22);	// 
	ym2612_write(0xA0, 0, 0x69); // Set frequency

	/* Program loop */
	while(1) {
		__delay_ms(1000);
		ym2612_write(0x28, 0, 0xF0); // Key on
		__delay_ms(1000);
		ym2612_write(0x28, 0, 0x00); // Key off
	}
	

    /*while (1) {
        // Add your application code
    }*/
}
/**
 End of File
*/