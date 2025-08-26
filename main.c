/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"

void init_LCD()
{
    LCD_Start();
    LCD_Position(0,0);
    LCD_PrintString("Rotary Sensor Lab");
    CyDelay(1000);
    LCD_ClearDisplay();
    LCD_Position(0,0);
    LCD_PrintString("Rotary");
}

int main(void)
{
    int32 count = 0;
    CyGlobalIntEnable; /* Enable global interrupts. */

    
    QuadDec_Start();
    QuadDec_SetCounter(0);
    for(;;)
    {
        count = QuadDec_GetCounter();
        LCD_Position(1,0);
        LCD_PrintNumber(count);
    }
}

/* [] END OF FILE */
