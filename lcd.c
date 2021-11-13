/*
 * lcd.c
 *
 *  Created on: 4 Kas 2021
 *      Author: Lenovo
 */
#include "lcd.h"

void Delay(uint32_t second){
    NVIC_ST_RELOAD_R=second;
    NVIC_ST_CURRENT_R=0X00;
    NVIC_ST_CTRL_R |= NVIC_ST_CTRL_CLK_SRC|NVIC_ST_CTRL_ENABLE;  //16mhz clock source
    while((NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT)==0);
    NVIC_ST_CTRL_R &= ~NVIC_ST_CTRL_ENABLE;
}
void LcdEnable(){
    GPIO_PORTB_DATA_R |= 0x02; // EN=1
    Delay(DELAY_100us);
    GPIO_PORTB_DATA_R &= 0XFC ; // EN=0
}
void LcdCmd(unsigned char c){
    GPIO_PORTB_DATA =(c & 0xf0);
    GPIO_PORTB_CONTROL=0X00; //0X00  ~(1<<RS)
    LcdEnable();
    Delay(DELAY_4_1ms);

    GPIO_PORTB_DATA =((c & 0x0f)<<4);
    GPIO_PORTB_CONTROL = 0X00; //~(1<<RS);
    LcdEnable();
    Delay(DELAY_4_1ms);
}
void LcdWrite(unsigned char c){
    GPIO_PORTB_DATA =(c & 0xf0); //D4 D5 D6 D7 -> HIGH NIBBLE
    GPIO_PORTB_CONTROL=0X01; //0X00  ~(1<<RS)
    LcdEnable();
    Delay(DELAY_4_1ms);

    GPIO_PORTB_DATA =((c & 0x0f)<<4); //D4 D5 D6 D7 -> LOW NIBBLE
    GPIO_PORTB_CONTROL = 0X01; //~(1<<RS);
    LcdEnable();
    Delay(DELAY_4_1ms);
}
void LcdHome(){
    LcdCmd(0x02);
    Delay(DELAY_100us);
}
void LcdClear(){
    LcdCmd(0x01);
    LcdCmd(0x02);
    Delay(DELAY_100us);
}
void LcdDisplayOn(){
    LcdCmd(0x0c);
    Delay(DELAY_100us);
}

void LcdCursorOn(){
    LcdCmd(0x0e);
    Delay(DELAY_100us);
}
void LcdBlinkOn(){
    LcdCmd(0x0f);
    Delay(DELAY_100us);
}
void LcdSetCursor(unsigned char row ,unsigned char col){
    char adress;
    if(row == 0)
        adress=0;
    else if(row==1)
        adress=0x40;
    else
        adress=0;
    adress|=col;
    LcdCmd(0x80 | adress);
}
void LcdPrint(char* text){
    char* string=text;
    while((string !=0) && (*string != 0)){
        LcdWrite(*string);
        string++;
    }
}
void LcdInit(){
    SYSCTL_RCGCGPIO_R|=(1<<1); // PORT B Enable
    GPIO_PORTB_DIR_R|=ALL_CONTROL|ALL_DATA;
    GPIO_PORTB_DEN_R|=ALL_CONTROL|ALL_DATA;
    GPIO_PORTB_DATA_R=0x00;
    GPIO_PORTB_CONTROL &=~(1<<0); //0 register RS =0;

    GPIO_PORTB_DATA=0X30; //(1<<4)|(1<<5); //30H
    LcdEnable();
    Delay(DELAY_15ms);
    GPIO_PORTB_DATA=0X30;
    LcdEnable();
    Delay(DELAY_4_1ms);
    GPIO_PORTB_DATA =0X30;
    LcdEnable();
    Delay(DELAY_4_1ms);

    LcdCmd(0x3F);
    LcdCmd(0x0e); // DISPALY ON CURSON ON
    LcdCmd(0x01); // CLEAR SCREEN
    LcdCmd(0x06); // ENTRY MODE SET 0b0I/DS0 //ID=1  S =0
    LcdClear();
}



