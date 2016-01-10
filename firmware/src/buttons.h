/* 
 * File:   buttons.h
 * Author: user
 *
 * Created on 2015. okt�ber 9., 13:27
 */

#ifndef BUTTONS_H
#define	BUTTONS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "system_definitions.h"

#define	OFF		0
#define	ON		1

#define BUTTON_NONE			0
#define BUT_UP_ON       1
#define BUT_UP_OFF			2
#define BUT_OK_ON       3
#define BUT_OK_OFF			4
#define BUT_LF_ON       5
#define BUT_LF_OFF			6
#define BUT_RG_ON       7
#define BUT_RG_OFF			8
#define BUT_DN_ON       9
#define BUT_DN_OFF			10
#define BUT_ES_ON       11
#define BUT_ES_OFF			12

#define	COL1		PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_1) // PORTBbits.RB0 // RB0
#define	COL2		PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_2) // PORTBbits.RB1 //RB1
#define	COL3		PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_3) //PORTBbits.RB2 // RB2

#define SETCOL1  PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_1);
#define SETCOL2  PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_2);
#define SETCOL3  PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_3);

#define ICOL1 PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_1);
#define ICOL2 PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_2);
#define ICOL3 PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_3);

#define OCOL1 PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_1);
#define OCOL2 PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_2);
#define OCOL3 PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_3);

#define bitset(var,bitno) ((var) |= 1 << (bitno))
#define bitclr(var,bitno) ((var) &= ~(1 << (bitno)))
  typedef union {
  struct {
    unsigned B1: 1;
    unsigned B2: 1;
    unsigned B3: 1;
    unsigned B4: 1;
    unsigned B5: 1;
    unsigned B6: 1;
    unsigned B7: 1;
    unsigned B8: 1;
  };
  struct {
    unsigned char BB;
  };
  }s_buttons;
void InitButtons();
char ButtonScan();


#ifdef	__cplusplus
}
#endif

#endif	/* BUTTONS_H */

