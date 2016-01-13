

#include "HX711Reader.h"

void HX711_InitPorts()
{
  OCLOCK
  IDATA
}

bool HX711_IsReadyData()
{
  CLKLOW
  return !DOUT;
}

uint32_t HX711_GetData(int bitnum)
{ int i; uint32_t result = 0;
  for (i = 0; i < 24; i++)
  {
    CLKHIGH
    delayusec(1);
    result <<= 1;
    CLKLOW
    delayusec(1);
    if (DOUT) { result++; };
  }

  for (i = 0; i < (bitnum - 24); i++)
  {
    CLKHIGH
    delayusec(1);
    CLKLOW
    delayusec(1);
  }
  
  result ^= 0x800000;

  return result;
}

uint32_t HX711_GetAverageData()
{ int i; uint32_t ADSUM = 0;
  for (i = 0; i < AD_AVERAGE; i++)
  {
    while (!HX711_IsReadyData());
    ADSUM += HX711_GetData(AD_GAIN_128);
  }
  ADSUM = (ADSUM / AD_AVERAGE);
  ADSUM = (ADSUM - 0x800000);
  return ADSUM;
}

/*  ADFLOAT = (2.0 / 900000.0) * ADFLOAT;
     ADFLOAT = ADFLOAT * 50;
      sprintf(BUFFER, "D=%10.2f kg", ADFLOAT);
      LCD_I2C_SetCursor(0,1);
      LCD_I2C_PrintStr(BUFFER);*/