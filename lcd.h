/*
 * lcd.h
 *
 *  Created on: 4 Kas 2021
 *      Author: Lenovo
 */

#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "inc/tm4c123gh6pm.h"


#define LCDPORT                          GPIO_PORTB_DATA_BITS_R
#define RS                               (1<<0)
#define EN                               (1<<1)
#define ALL_CONTROL                      RS|EN
#define D4                               (1<<4)
#define D5                               (1<<5)
#define D6                               (1<<6)
#define D7                               (1<<7)
#define ALL_DATA                         D4|D5|D6|D7

#define LcdControlAdress                 0x4000500C // Just Concerned to pins 0 and 1 (RS ->0 EN->1)
#define LcdDataAdress                    0x400053C0 // Just Concerned to pins D4 D5 D6 D7
#define GPIO_PORTB_CONTROL               (*((volatile uint32_t *)LcdControlAdress))
#define GPIO_PORTB_DATA                  (*((volatile uint32_t *)LcdDataAdress))

void LcdEnable();
void LcdCmd(unsigned char );
void LcdWrite(unsigned char );
void LcdInit();
void LcdClear();
void LcdSetCursor(unsigned char ,unsigned char);
void LcdPrint(char *);
void LcdCursorOn();
void LcdBlinkOn();
void LcdDisplayOn();
void LcdHome();


#endif /* LCD_H_ */
