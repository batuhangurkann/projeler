#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/hibernate.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

int main(void)
{
    // Sistem saatini 16 MHz'e ayarla
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    // Hibernate mod�l�n� etkinle�tir.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_HIBERNATE));

    // Hibernate mod�l�n� yap�land�r.
    HibernateEnableExpClk(SysCtlClockGet());
    HibernateGPIORetentionEnable(); // GPIO durumunu koru.

    // Hibernate modunda RTC (Real-Time Clock) ayarlar�n� yap.
    HibernateRTCEnable(); // RTC'yi ba�lat.
    HibernateRTCSet(0);   // RTC'yi s�f�rla.

    // 5 saniye sonra uyanmas� i�in alarm ayarla.
    HibernateRTCMatchSet(0, 5); // 5 saniye sonra uyanacak.

    // Uyanma i�in hiberenasyon alarm�n� etkinle�tir.
    HibernateWakeSet(HIBERNATE_WAKE_PIN | HIBERNATE_WAKE_RTC);

    // Hibernate moduna gir.
    HibernateRequest();

    while (1)
    {

    }

    return 0;
}
