/*
 * lcd.c
 *
 *  Created on: 1 Kas 2024
 *      Author: infob
 */

#include "inc/tm4c123gh6pm.h"
#include "zamanlayiciheader.h"
#include "stdint.h"
#include "stdbool.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"



void lcd_komut(unsigned char b)
{
    GPIOPinWrite(LCD_PORT, D4 | D5 | D6 | D7, (b & 0xf0) );
    GPIOPinWrite(LCD_PORT, RS, 0x00);
    GPIOPinWrite(LCD_PORT, E, 0x02);
    SysCtlDelay(10);
    GPIOPinWrite(LCD_PORT, E, 0x00);
    SysCtlDelay(50000);


    GPIOPinWrite(LCD_PORT, D4 | D5 | D6 | D7, (b & 0x0f) << 4 );
    GPIOPinWrite(LCD_PORT, RS, 0x00);
    GPIOPinWrite(LCD_PORT, E, 0x02);
    SysCtlDelay(10);
    GPIOPinWrite(LCD_PORT, E, 0x00);
    SysCtlDelay(50000);
}

void lcd_karakterkomut(unsigned char c)
{
    GPIOPinWrite(LCD_PORT, D4 | D5 | D6 | D7, (c & 0xf0) );
    GPIOPinWrite(LCD_PORT, RS, 0x01);
    GPIOPinWrite(LCD_PORT, E, 0x02);
    SysCtlDelay(10);
    GPIOPinWrite(LCD_PORT, E, 0x00);
    SysCtlDelay(50000);


    GPIOPinWrite(LCD_PORT, D4 | D5 | D6 | D7, (c & 0x0f) << 4 );
    GPIOPinWrite(LCD_PORT, RS, 0x01);
    GPIOPinWrite(LCD_PORT, E, 0x02);
    SysCtlDelay(10);
    GPIOPinWrite(LCD_PORT, E, 0x00);
    SysCtlDelay(50000);

}

void lcd_yaz (char* s)
{
    while(*s)
        lcd_karakterkomut(*s++);
}


void lcd_temizle(void)
{
    lcd_komut(0x01);
    SysCtlDelay(10);
}

void otuzhexgonder()
{

    GPIOPinWrite(LCD_PORT, D4|D5|D6|D7, 0x30);
    GPIOPinWrite(LCD_PORT, E, 2);
    SysCtlDelay(250);
    GPIOPinWrite(LCD_PORT, E, 0);
    SysCtlDelay(30000);

}


void yirmihexgonder()
{
     GPIOPinWrite(LCD_PORT, D4 | D5 | D6 | D7,  0x20 );
     GPIOPinWrite(LCD_PORT, E, 0x02);
     SysCtlDelay(10);
     GPIOPinWrite(LCD_PORT, E, 0x00);
     SysCtlDelay(50000);
}


void lcd_ilkAyarlar() {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinTypeGPIOOutput(LCD_PORT, 0xFF);
    SysCtlDelay(50000);
    GPIOPinWrite(LCD_PORT, RS,  0x00 );

    otuzhexgonder();
    otuzhexgonder();
    otuzhexgonder();
    yirmihexgonder();

    lcd_temizle();
    lcd_komut(0x28);
    lcd_komut(0x0C);
    lcd_komut(0x06);
    lcd_komut(0x01);
    lcd_temizle();
}
