
/***************************************************************************************************
                                   ExploreEmbedded
 ****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: This file contains the program to the on board peripherals of Starter AVR board. 

The libraries have been tested on ExploreEmbedded development boards. We strongly believe that the
library works on any of development boards for respective controllers. However, ExploreEmbedded
disclaims any kind of hardware failure resulting out of usage of libraries, directly or indirectly.
Files may be subject to change without prior notice. The revision history contains the information
related to updates.


GNU GENERAL PUBLIC LICENSE:
    Copyright (C) 2012  ExploreEmbedded

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.


Errors and omissions should be reported to codelibraries@exploreembedded.com
 **************************************************************************************************/
#include "adc.h"
#include "delay.h"
#include "gpio.h"
#include "lcd.h"
#include "stdutils.h"
#include "uart.h"

#define SWITCH1 P3_2
#define SWITCH2 P3_3
#define LED1    P3_4
#define LED2    P3_5


void led_Test(void);
void lcd_Test(void);
void switch_Test(void);


int main() 
{

    char option; 

    GPIO_PinDirection(SWITCH1,INPUT);
    GPIO_PinDirection(SWITCH2,INPUT);

    if((GPIO_PinRead(SWITCH1)==1) &&  (GPIO_PinRead(SWITCH2)==1)) 
    {
        // If no Switches are pressed then Board Testing is not required, Just blink the Leds.
        GPIO_PinDirection(LED1,OUTPUT);
        GPIO_PinDirection(LED2,OUTPUT);

        while(1)
        {
            GPIO_PinWrite(LED1,1);
            GPIO_PinWrite(LED2,1);
            DELAY_ms(200);

            GPIO_PinWrite(LED1,0);
            GPIO_PinWrite(LED2,0);
            DELAY_ms(200);
        }
    }

    UART_Init(9600);
    UART_Printf("\n\rStarter 8051 Test Menu\n\r 1.Led test\n\r 2.Lcd test\n\r 3.Switch test\n\rSelect One of the above options");

    while(1)
    {
        option = UART_RxChar();
        switch(option)
        {
        case '1':
            led_Test();
            break;

        case '2':
            lcd_Test();
            break;

        case '3':
            switch_Test();
            break;

        default:
            break;    
        }
    }
    return (0);
}


void led_Test(void)
{
    uint8_t i,pattern;  

    while(1)
    {

        P0 = 0xff; /* Turn ON all the leds connected to Ports */
        P1 = 0xff;
        P2 = 0xff;
        P3 = 0xff;
        DELAY_ms(500);

        P0 = 0x00; /* Turn OFF all the leds connected to Ports */
        P1 = 0x00;
        P2 = 0x00;
        P3 = 0x00;
        DELAY_ms(500);

        pattern=0x01;
        for(i=0;i<8;i++)
        {
            P0 = pattern;
            P1 = pattern;
            P2 = pattern;
            P3 = pattern;  
            pattern = pattern<<1;
            DELAY_ms(200);
        }
    }

}



void lcd_Test(void)
{
    LCD_SetUp(P0_0,P0_1,P0_2,P_NC,P_NC,P_NC,P_NC,P0_4,P0_5,P0_6,P0_7);
    LCD_Init(2,16);
    LCD_DisplayString("Explore\n Starter 8051..."); 

    while(1);
}





void switch_Test(void)
{
    GPIO_PinDirection(LED1,OUTPUT);
    GPIO_PinDirection(LED2,OUTPUT);
    GPIO_PinDirection(SWITCH1,INPUT);
    GPIO_PinDirection(SWITCH2,INPUT);
    UART_TxString("\n\n\n\rPress the switches and observe the output on Leds");
    while(1)
    {
        GPIO_PinWrite(LED1,GPIO_PinRead(SWITCH1));
        GPIO_PinWrite(LED2,GPIO_PinRead(SWITCH2));        
    }
}
