#include "stdint.h"
#include "stdbool.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/gpio.h"
#include "driverlib/gpio.c"
#include "driverlib/sysctl.h"
#include "driverlib/sysctl.c"
#include "driverlib/pin_map.h"
#include "math.h"
#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "lcd.h"



int main(void)
{

    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
       lcd_ilkAyarlar();

       while(1)
       {
       lcd_yaz("deneme testi");
       SysCtlDelay(1333333);
       lcd_temizle();
       }

}




