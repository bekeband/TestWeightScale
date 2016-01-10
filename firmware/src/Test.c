/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    test.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "test.h"
#include "buttons.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************


TEST_DATA testData;

void TEST_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    testData.state = TEST_STATE_INIT;
//    testData.state = TEST_STATE_READ_BUTTONS;

    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}

void StopAndBlinkLED()
{
  while (1)
  {
    SYS_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_6);
    delayusec(500000);
  }
}

/******************************************************************************
  Function:
    void TEST_Tasks ( void )

  Remarks:
    See prototype in test.h.
 */
char  BUFFER[20];
#define MAX_AD_COUNTER 8

void TEST_Tasks ( void )
{ char but; uint32_t AVERAGE; float SCALEW;
    /* Check the application's current state. */
    switch ( testData.state )
    {
        /* Application's initial state. */
        case TEST_STATE_INIT:
        {
          
          HX711_InitPorts();
          InitButtons();
          Init_LCD();
          LCD_I2C_Backlight();
          LCD_I2C_PrintStr("bekeband.hu");
          LCD_I2C_SetCursor(0,1);
          LCD_I2C_PrintStr("init OK");
          testData.state = TEST_STATE_READ_BUTTONS;
          break;
        }
      case TEST_STATE_READ_BUTTONS:
      {
        while (1)
        {
        but = ButtonScan();
        if (1)
        {
          AVERAGE = HX711_GetAverageData();
          SCALEW = (2.0 / 900000.0) * (int32_t)AVERAGE;
          SCALEW = SCALEW * 50;
          sprintf(BUFFER, "D=%10li", AVERAGE);
          LCD_I2C_SetCursor(0,0);
          LCD_I2C_PrintStr(BUFFER);
          sprintf(BUFFER, "F=%10.2f kg", SCALEW);
          LCD_I2C_SetCursor(0,1);
          LCD_I2C_PrintStr(BUFFER);
        } else
        {
/*            sprintf(BUFFER, "not ready");
            LCD_I2C_SetCursor(0,1);
            LCD_I2C_PrintStr(BUFFER);
            but = BUTTON_NONE;*/
        }
        }
        StopAndBlinkLED();
        break;
      }
        /* The default state should never be executed. */
        default:
        {
            break;
        }
    }
}
 

/*******************************************************************************
 End of File
 */
