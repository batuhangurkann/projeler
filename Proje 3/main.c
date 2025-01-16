#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "inc/tm4c123gh6pm.h"
#include "zamanlayiciheader.h"

void SetInitSettings();
void timerkesmefonksiyonu();
void format_time(char *buffer, int saat, int dakika, int saniye);

volatile int saat = 0;
volatile int dakika = 0;
volatile int saniye = 0;

int main(void)
{
    lcd_ilkAyarlar();
    SetInitSettings();

    while (1)
    {

    }

}

void SetInitSettings()
{
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_A_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet());
    IntMasterEnable();
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntRegister(TIMER0_BASE, TIMER_A, timerkesmefonksiyonu);
    TimerEnable(TIMER0_BASE, TIMER_A);
}

void timerkesmefonksiyonu()
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);


    saniye++;
    if (saniye == 60) {
        saniye = 0;
        dakika++;
    }
    if (dakika == 60) {
        dakika = 0;
        saat++;
    }
    if (saat == 24) {
        saat = 0;
    }


    char buffer[9];
    format_time(buffer, saat, dakika, saniye);
    lcd_komut(0xC8);
    lcd_yaz(buffer);


    uint32_t deger = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, ~deger);
}



void format_time(char *buffer, int saat, int dakika, int saniye)
{
    buffer[0] = '0' + (saat / 10);
    buffer[1] = '0' + (saat % 10);
    buffer[2] = ':';
    buffer[3] = '0' + (dakika / 10);
    buffer[4] = '0' + (dakika % 10);
    buffer[5] = ':';
    buffer[6] = '0' + (saniye / 10);
    buffer[7] = '0' + (saniye % 10);
    buffer[8] = '\0';
}



