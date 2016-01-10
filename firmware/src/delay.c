
#include <stdint.h>
#include "system_definitions.h"
#include "delay.h"

void debug_LED()
{
  while (1)
  {
    SYS_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_6);
    delayusec(100000);
  }
}

void delayusec(uint32_t usectime)
{
  PLIB_TMR_Stop(TMR_ID_4);
  DRV_TMR0_CounterClear();
  PLIB_TMR_Period32BitSet(TMR_ID_4, usectime * (SYS_CLK_BUS_PERIPHERAL_1 / 1000000));
  DRV_TMR0_Start();
  while (!PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_TIMER_5));
  PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_TIMER_5);
}

