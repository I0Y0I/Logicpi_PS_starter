/*!
    \file    main.c
    \brief   led spark with systick, USART print and key example

   \version 2024-12-20, V3.0.1, firmware for GD32F30x
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#include "gd32f30x.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"
#include "pi.h"

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/

int main(void)
{
#ifdef __FIRMWARE_VERSION_DEFINE
    uint32_t fw_ver = 0;
#endif

    /* configure systick */
    systick_config();
    /* initialize the LEDs, USART and key */
    pi_led_init();
    pi_usart_init(115200);
    pi_button_init();

    /* print out the clock frequency of system, AHB, APB1 and APB2 */
    printf("\r\nCK_SYS is %d", rcu_clock_freq_get(CK_SYS));
    printf("\r\nCK_AHB is %d", rcu_clock_freq_get(CK_AHB));
    printf("\r\nCK_APB1 is %d", rcu_clock_freq_get(CK_APB1));
    printf("\r\nCK_APB2 is %d", rcu_clock_freq_get(CK_APB2));

#ifdef __FIRMWARE_VERSION_DEFINE
    fw_ver = gd32f30x_firmware_version_get();
    /* print firmware version */
    printf("\r\nGD32F30x series firmware version: V%d.%d.%d", (uint8_t)(fw_ver >> 24), (uint8_t)(fw_ver >> 16), (uint8_t)(fw_ver >> 8));
#endif /* __FIRMWARE_VERSION_DEFINE */

    PI_LCD_BLK_RESET();
    pi_lcd_init();
    pi_lcd_fill(MOCHA_BASE);
    // pi_lcd_fill_rectangle(0, 0, PI_LCD_WIDTH>>1, PI_LCD_HEIGHT>>1, MOCHA_SURFACE0);
    // pi_lcd_draw_line(80, 0, 80, 120, MOCHA_BLUE);
    // pi_lcd_draw_rectangle(20, 20, 140, 100, MOCHA_ROSEWATER);
    // pi_lcd_draw_circle(80, 60, 10, MOCHA_PINK);
    PI_LCD_BLK_SET();

    while (1){
        switch (pi_button_get_event()) {
            case PI_BUTTON_SINGLE_PRESS:
                pi_led_set(PI_LED_RED);
                pi_lcd_print_string(64, 104, "Short  Press", MOCHA_RED, MOCHA_SURFACE0, FONT_LARGE);
                printf("\r\nShort press!");
                delay_1ms(1000);
                pi_lcd_fill_rectangle(64, 104, 256, 136, MOCHA_BASE);
                pi_led_set(PI_LED_OFF);
                break;
            case PI_BUTTON_DOUBLE_PRESS:
                pi_led_set(PI_LED_GREEN);
                pi_lcd_print_string(64, 104, "Double Press", MOCHA_GREEN, MOCHA_SURFACE0, FONT_LARGE);
                printf("\r\nDouble press!");
                delay_1ms(1000);
                pi_lcd_fill_rectangle(64, 104, 256, 136, MOCHA_BASE);
                pi_led_set(PI_LED_OFF);
                break;
            case PI_BUTTON_LONG_PRESS:
                pi_led_set(PI_LED_BLUE);
                pi_lcd_print_string(64, 104, "Long   Press", MOCHA_BLUE, MOCHA_SURFACE0, FONT_LARGE);
                printf("\r\nLong press!");
                delay_1ms(1000);
                pi_lcd_fill_rectangle(64, 104, 256, 136, MOCHA_BASE);
                pi_led_set(PI_LED_OFF);
                break;
            default:
                break;
        }
    }
}
