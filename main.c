//** System OSC default 16 MHZ ***\\\


#include "Lcd.h"

void main(void)
{
    LcdInit();
    LcdDisplayOn();
    while(1){
        LcdSetCursor(0, 0);
        LcdPrint("TIVA LAUNCHPAD");
        LcdSetCursor(1, 0);
        LcdPrint("HELLO WORD");
        LcdHome();
    }
}



