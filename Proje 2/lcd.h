/*
 * lcd.h
 *
 *  Created on: 1 Kas 2024
 *      Author: infob
 */

#ifndef LCD_H_
#define LCD_H_

#define LCD_PORT                         GPIO_PORTB_BASE
#define LCD_PORT_ENABLE                  SYSCTL_PERIPH_GPIOB
#define RS                               GPIO_PIN_0
#define E                                GPIO_PIN_1

#define D4                               GPIO_PIN_4
#define D5                               GPIO_PIN_5
#define D6                               GPIO_PIN_6
#define D7                               GPIO_PIN_7

#define SYSCTL_RCGCBASE                  0x400fe600

void lcd_temizle(void);
void lcd_yaz(char*);
void lcd_git(char,char);
void lcd_ilkAyarlar(void);
void lcd_komut(unsigned char b);
void lcd_karakterkomut(unsigned char c);


#endif /* LCD_H_ */
