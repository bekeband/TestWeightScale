/*******************************************************************************
 System Interrupts File

  File Name:
    system_int.c

  Summary:
    Raw ISR definitions.

  Description:
    This file contains a definitions of the raw ISRs required to support the
    interrupt sub-system.

  Summary:
    This file contains source code for the interrupt vector functions in the
    system.

  Description:
    This file contains source code for the interrupt vector functions in the
    system.  It implements the system and part specific vector "stub" functions
    from which the individual "Tasks" functions are called for any modules
    executing interrupt-driven in the MPLAB Harmony system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    interrupt-driven in the system.  These handles are passed into the individual
    module "Tasks" functions to identify the instance of the module to maintain.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2014 released Microchip Technology Inc.  All rights reserved.

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

#include <xc.h>
#include <sys/attribs.h>
#include "test.h"
#include "system_definitions.h"


// *****************************************************************************
// *****************************************************************************
// Section: System Interrupt Vector Functions
// *****************************************************************************
// *****************************************************************************
void __ISR(_TIMER_5_VECTOR, ipl1AUTO) _IntHandlerDrvTmrInstance0(void)
{
  USECTIMERFLAG = 1;
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_5);

}
void __ISR(_TIMER_2_VECTOR, ipl1AUTO) _IntHandlerDrvTmrInstance1(void)
{
  SCALE_READ_FLAG = 1;
  PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_2); 
}
void __ISR(_TIMER_3_VECTOR, ipl1AUTO) _IntHandlerDrvTmrInstance2(void)
{
 
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_3);
 
}

void __ISR(_UART_2_VECTOR, ipl1AUTO) _IntHandlerDrvUsartInstance0(void)
{ uint8_t ibyte;
  if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_2_ERROR))
  {
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_2_ERROR);
  } else
  if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_2_RECEIVE))
  {
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_2_RECEIVE);
    ibyte = PLIB_USART_ReceiverByteReceive(USART_ID_2);
  } else
  if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_2_TRANSMIT))
  {

    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_2_TRANSMIT);
    PLIB_INT_SourceDisable(INT_ID_0, INT_SOURCE_USART_2_TRANSMIT);
  }
}

void __ISR(_UART_5_VECTOR, ipl1AUTO) _IntHandlerDrvUsartInstance1(void)
{
  if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_5_ERROR))
  {
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_5_ERROR);
  } else
  if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_5_RECEIVE))
  {
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_5_RECEIVE);
  } else
  if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_5_TRANSMIT))
  {
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_5_TRANSMIT);
    PLIB_INT_SourceDisable(INT_ID_0, INT_SOURCE_USART_5_TRANSMIT);
  }
}

void __ISR(_RTCC_VECTOR, ipl1AUTO) _IntHandlerRTCC(void)
{
//    SYS_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_6);
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_RTCC);
    alarmTriggered = 1;
}


/*******************************************************************************
 End of File
*/

