/*
 * lcd.h
 *
 *  Created on: 1 Kas 2024
 *      Author: infob
 */

#ifndef ZAMANLAYICI_H_
#define ZAMANLAYICI_H_

#define LCD_PORT                         GPIO_PORTB_BASE
#define LCD_PORT_ENABLE                  SYSCTL_PERIPH_GPIOB
#define RS GPIO_PIN_0
#define E  GPIO_PIN_1
#define D4 GPIO_PIN_4
#define D5 GPIO_PIN_5
#define D6 GPIO_PIN_6
#define D7 GPIO_PIN_7

void lcd_komut(unsigned char b);
void lcd_karakterkomut(unsigned char c);
void lcd_yaz(char*);
void lcd_ilkAyarlar(void);
void lcd_temizle(void);

#endif /* ZAMANLAYICI_H_ */
