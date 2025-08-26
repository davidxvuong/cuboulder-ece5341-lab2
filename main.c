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
#define LCD_CLEAR_LINE      "                "
#define DEBOUNCING_COUNT    3

void init_LCD()
{
    LCD_Start();
    LCD_Position(0,0);
    LCD_PrintString("Rotary Sensor Lab");
    CyDelay(1000);
    LCD_ClearDisplay();
    LCD_Position(0,0);
    LCD_PrintString("QD");
    LCD_Position(0,8);
    LCD_PrintString("SW");
}

int main(void)
{
    int32 quad_dec_count = 0;
    int32 sw_count = 0;
    uint8 stable_count = 0;
    uint8 prev_gpio_3_7 = 0;      // last stable state
    uint8 last_gpio_3_7 = 0;      // last read
    uint8 cur_gpio_3_7 = 0;
    uint8 cur_gpio_3_5 = 0;

    CyGlobalIntEnable; /* Enable global interrupts. */

    init_LCD();
    QuadDec_Start();
    QuadDec_SetCounter(0);

    // Initialize both states
    prev_gpio_3_7 = P3_7_Read();
    last_gpio_3_7 = prev_gpio_3_7;

    for(;;)
    {
        cur_gpio_3_5 = P3_5_Read();
        cur_gpio_3_7 = P3_7_Read();

        // Debounce: check if current read matches last read
        if (cur_gpio_3_7 == last_gpio_3_7)
        {
            stable_count++;
        }
        else
        {
            stable_count = 0;
        }

        last_gpio_3_7 = cur_gpio_3_7;

        // Only act when stable for DEBOUNCING_COUNT reads
        if (stable_count >= DEBOUNCING_COUNT)
        {
            // Detect rising edge of stable signal
            if (prev_gpio_3_7 == 0 && cur_gpio_3_7 == 1)
            {
                if (cur_gpio_3_5)
                    sw_count++;
                else
                    sw_count--;
            }

            // Update last stable state and reset counter
            prev_gpio_3_7 = cur_gpio_3_7;
            stable_count = 0;
        }

        // HW QuadDec counter
        quad_dec_count = QuadDec_GetCounter();

        // Display counters
        LCD_Position(1,0);
        LCD_PrintNumber(quad_dec_count);
        LCD_Position(1,8);
        LCD_PrintNumber(sw_count);
    }
}


/* [] END OF FILE */
