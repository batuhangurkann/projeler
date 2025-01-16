#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

// UART'ý ayarlama
void ConfigureUART(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    UARTStdioConfig(0, 115200, SysCtlClockGet());
}

int main(void) {
    // Sistem frekansýný ayarlama
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    // UART'ý yapýlandýrma
    ConfigureUART();

    UARTprintf("Floating-point iþlemleri örnekleri\n");

    // Floating-point iþlemleri
    float number1 = 5.75;
    float number2 = 2.5;
    float result;

    // Toplama
    result = number1 + number2;
    UARTprintf("Toplama: %.2f + %.2f = %.2f\n", number1, number2, result);

    // Çýkarma
    result = number1 - number2;
    UARTprintf("Çýkarma: %.2f - %.2f = %.2f\n", number1, number2, result);

    // Çarpma
    result = number1 * number2;
    UARTprintf("Çarpma: %.2f * %.2f = %.2f\n", number1, number2, result);

    // Bölme
    result = number1 / number2;
    UARTprintf("Bölme: %.2f / %.2f = %.2f\n", number1, number2, result);

    while (1) {
    }

    return 0;
}
