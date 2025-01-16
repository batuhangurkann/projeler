/*
 * lcd.c
 *
 *  Created on: 1 Kas 2024
 *      Author: infob
 */

#include "inc/tm4c123gh6pm.h"
#include "lcd.h"
#include "stdint.h"
#include "stdbool.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"

void otuzhexgonder()
{

    HWREG(LCD_PORT + (GPIO_O_DATA + (D4|D5|D6|D7 << 2))) = 0x30;
    HWREG(LCD_PORT + (GPIO_O_DATA + (E << 2))) = 0x02;
    SysCtlDelay(250);
    HWREG(LCD_PORT + (GPIO_O_DATA + (E << 2))) = 0x00;
    SysCtlDelay(30000);

}


void yirmihexgonder()
{
    HWREG(LCD_PORT + (GPIO_O_DATA + (D4|D5|D6|D7 << 2))) = 0x20;
    HWREG(LCD_PORT + (GPIO_O_DATA + (E << 2))) = 0x02;
    SysCtlDelay(10);
    HWREG(LCD_PORT + (GPIO_O_DATA + (E << 2))) = 0x00;
    SysCtlDelay(50000);
}


void lcd_ilkAyarlar() {
    SYSCTL_RCGCGPIO_R |= 0x02;  // HWREGBITW(SYSCTL_RCGCBASE + ((SYSCTL_PERIPH_GPIOB & 0xff00) >> 8),SYSCTL_PERIPH_GPIOB & 0xff) = 1;
    GPIO_PORTB_DIR_R   = 0xff;
    GPIO_PORTB_DEN_R  |= 0xff;
    SysCtlDelay(50000);
    HWREG(LCD_PORT + (GPIO_O_DATA + (RS << 2))) = 0x00;

    otuzhexgonder();
    otuzhexgonder();
    otuzhexgonder();
    yirmihexgonder();

    lcd_temizle();
    lcd_komut(0x28);
    lcd_komut(0x06);
    lcd_komut(0x80);
    lcd_komut(0x0f);
    lcd_temizle();
}

void lcd_git(char x, char y)
{
    if(x==1)
        lcd_komut(0x80+((y-1)%16));
    else
        lcd_komut(0xC0+((y-1)%16));
}

void lcd_temizle(void)
{
    lcd_komut(0x01);
    SysCtlDelay(10);
}

void lcd_yaz (char* s)
{
    while(*s)
        lcd_karakterkomut(*s++);
}


void lcd_komut(unsigned char b)
{
    unsigned char d = (b & 0xf0);
    HWREG(LCD_PORT + (GPIO_O_DATA + (D4|D5|D6|D7 << 2))) = d;
    HWREG(LCD_PORT + (GPIO_O_DATA + (RS << 2))) = 0x00;
    HWREG(LCD_PORT + (GPIO_O_DATA + (E << 2))) = 0x02;
    SysCtlDelay(10);
    HWREG(LCD_PORT + (GPIO_O_DATA + (E << 2))) = 0x00;
    SysCtlDelay(50000);

    unsigned char e = ((b & 0x0f) << 4);
    HWREG(0x400050F0) = e;
    HWREG(LCD_PORT + (GPIO_O_DATA + (RS << 2))) = 0x00;
    HWREG(LCD_PORT + (GPIO_O_DATA + (E << 2))) = 0x02;
    SysCtlDelay(10);
    HWREG(LCD_PORT + (GPIO_O_DATA + (E << 2))) = 0x00;
    SysCtlDelay(50000);
}

void lcd_karakterkomut(unsigned char c)
{
    HWREG(LCD_PORT + (GPIO_O_DATA + (240 << 2))) = (c & 0xf0);
    HWREG(LCD_PORT + (GPIO_O_DATA + (RS << 2))) = 0x01;
    HWREG(LCD_PORT + (GPIO_O_DATA + (E << 2))) = 0x02;
    SysCtlDelay(10);
    HWREG(LCD_PORT + (GPIO_O_DATA + (E << 2))) = 0x00;
    SysCtlDelay(50000);

    HWREG(LCD_PORT + (GPIO_O_DATA + (240 << 2))) = ((c & 0x0f) << 4 );
    HWREG(LCD_PORT + (GPIO_O_DATA + (RS << 2))) = 0x01;
    HWREG(LCD_PORT + (GPIO_O_DATA + (E << 2))) = 0x02;
    SysCtlDelay(10);
    HWREG(LCD_PORT + (GPIO_O_DATA + (E << 2))) = 0x00;
    SysCtlDelay(50000);

}

