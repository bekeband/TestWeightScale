/* 
 * File:   HX711Reader.h
 * Author: user
 *  These are weight scale computing assert as well. 
 * Created on 2016. január 6., 13:35
 */

#ifndef HX711READER_H
#define	HX711READER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "system_definitions.h"

#define OCLOCK PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_4);
#define CLKLOW PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_4);
#define CLKHIGH PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_4);

#define IDATA  PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_5);
#define DOUT PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_5)

#define AD_AVERAGE  1
#define AD_GAIN_128 25
#define AD_GANI_64  27

void HX711_InitPorts();
bool HX711_IsReadyData();
uint32_t HX711_GetData(int bitnum);
uint32_t HX711_GetAverageData();



#ifdef	__cplusplus
}
#endif

#endif	/* HX711READER_H */

