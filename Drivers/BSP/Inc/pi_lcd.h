//
// Created by ioyoi on 25-7-1.
//

#ifndef PI_LCD_H
#define PI_LCD_H

#define PI_LCD_WIGHT 320
#define PI_LCD_HEIGHT 240

// SCK is PB13
#define PI_LCD_SCK_RESET() gpio_bit_reset(GPIOB, GPIO_PIN_13)
#define PI_LCD_SCK_SET() gpio_bit_set(GPIOB, GPIO_PIN_13)
// MOSI is PB15
#define PI_LCD_MOSI_RESET() gpio_bit_reset(GPIOB, GPIO_PIN_15)
#define PI_LCD_MOSI_SET() gpio_bit_set(GPIOB, GPIO_PIN_15)
// RST is PB2
#define PI_LCD_RST_RESET() gpio_bit_reset(GPIOB, GPIO_PIN_2)
#define PI_LCD_RST_SET() gpio_bit_set(GPIOB, GPIO_PIN_2)
// DC is PC13
#define PI_LCD_DC_RESET() gpio_bit_reset(GPIOC, GPIO_PIN_13)
#define PI_LCD_DC_SET() gpio_bit_set(GPIOB, GPIO_PIN_13)
// CS is PB12
#define PI_LCD_CS_RESET() gpio_bit_reset(GPIOB, GPIO_PIN_12)
#define PI_LCD_CS_SET() gpio_bit_set(GPIOB, GPIO_PIN_12)
// BLK is PB1
#define PI_LCD_BLK_RESET() gpio_bit_reset(GPIOB, GPIO_PIN_1)
#define PI_LCD_BLK_SET() gpio_bit_set(GPIOB, GPIO_PIN_1)

#include "gd32f30x.h"

void pi_lcd_init(void);
void pi_lcd_gpio_init(void);
void pi_lcd_set_init(void);
uint8_t pi_lcd_transmit(uint8_t data);
void pi_lcd_write_data(uint8_t data);
void pi_lcd_write_data_16(uint16_t data);
void pi_lcd_write_reg(uint8_t reg);
void pi_lcd_write_area(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

#endif //PI_LCD_H
