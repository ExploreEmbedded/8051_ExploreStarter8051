/***************************************************************************************************
                                   ExploreEmbedded    
*****************************************************************************************************
 * File:   gpio.h
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains the the accessing the GPIO pins of a controller.
                First the GPIO pins needs to configured(Input/Output) and later used accordingly.

The libraries have been tested on ExploreEmbedded development boards. We strongly believe that the 
library works on any of development boards for respective controllers. However, ExploreEmbedded 
disclaims any kind of hardware failure resulting out of usage of libraries, directly or indirectly.
Files may be subject to change without prior notice. The revision history contains the information 
related to updates. 


GNU GENERAL PUBLIC LICENSE: 
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
***************************************************************************************************/


#include <reg51.h>
#include "stdutils.h"
#include "gpio.h"



/***************************************************************************************************
            void GPIO_PinWrite(gpioPins_et enm_pinNumber, uint8_t v_pinValue_u8)
****************************************************************************************************
 * I/P Arguments: 
                gpioPins_et: pin number which needs to be updated.
                             Refer the gpio.h for pin numbering.
                gpioValue_et: Value to be updated(LOW/HIGH) on the selected pin.
                              

 * Return value    : none

 * description :This function updates the specified value on the selected pin.  
                Before updating the pins status, the pin function should be selected and then
                the pin should be configured as OUTPUT 
****************************************************************************************************/
void GPIO_PinWrite(gpioPins_et enm_pinNumber, uint8_t v_pinValue_u8)
{

    uint8_t v_portNumber_u8;


    v_portNumber_u8 =  (enm_pinNumber>>3);  // Divide the pin number by 8 go get the PORT number
    enm_pinNumber  =   enm_pinNumber & 0x07;  // lower 3-bits contains the bit number of a byte 

    /* Go to particular port after decoding from the pin number and 
        update the value of the specified pin*/
    switch(v_portNumber_u8)
    {
    case 0:
        util_UpdateBit(P0,enm_pinNumber,v_pinValue_u8);
        break;

    case 1:
        util_UpdateBit(P1,enm_pinNumber,v_pinValue_u8);
        break;

    case 2:
        util_UpdateBit(P2,enm_pinNumber,v_pinValue_u8);
        break;

    case 3:
        util_UpdateBit(P3,enm_pinNumber,v_pinValue_u8);
        break;
    }                
}








/***************************************************************************************************
                    uint8_t GPIO_PinRead(gpioPins_et enm_pinNumber)
****************************************************************************************************
 * I/P Arguments: 
                gpioPins_et: pin number which needs to be read.
                             Refer the gpio.h for pin numbering.

 * Return value    : 
                 uint8_t:    Status of the specified pin.

 * description :This function returns the status of the selected pin.
                Before reading the pins status, the pin should be configured as INPUT 
****************************************************************************************************/
uint8_t GPIO_PinRead(gpioPins_et enm_pinNumber)
{
    uint8_t v_portNumber_u8;
    uint8_t returnStatus = 0;

    v_portNumber_u8 =  (enm_pinNumber>>3); // Divide the pin number by 8 go get the PORT number
    enm_pinNumber  =     enm_pinNumber & 0x07; // lower 3-bits contains the bit number of a byte 

    /* Go to particular port after decoding from the pin number and read the pins status */
    switch(v_portNumber_u8)     
    {                             
    case 0: 
        returnStatus = util_IsBitSet(P0,enm_pinNumber);
        break;

    case 1:
        returnStatus = util_IsBitSet(P1,enm_pinNumber);
        break;

    case 2:
        returnStatus = util_IsBitSet(P2,enm_pinNumber);
        break;

    case 3:
        returnStatus = util_IsBitSet(P3,enm_pinNumber);
        break;
    }                         
    return returnStatus;
}
