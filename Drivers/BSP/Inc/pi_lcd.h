//
// Created by ioyoi on 25-7-1.
//

#ifndef PI_LCD_H
#define PI_LCD_H

#define PI_LCD_WIDTH 320
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
#define PI_LCD_DC_SET() gpio_bit_set(GPIOC, GPIO_PIN_13)
// CS is PB12
#define PI_LCD_CS_RESET() gpio_bit_reset(GPIOB, GPIO_PIN_12)
#define PI_LCD_CS_SET() gpio_bit_set(GPIOB, GPIO_PIN_12)
// BLK is PB1
#define PI_LCD_BLK_RESET() gpio_bit_reset(GPIOB, GPIO_PIN_1)
#define PI_LCD_BLK_SET() gpio_bit_set(GPIOB, GPIO_PIN_1)

#include "gd32f30x.h"
#include "systick.h"

#include "pi_lcd_font.h"

void pi_lcd_init(void);
void pi_lcd_gpio_init(void);
void pi_lcd_set_init(void);
uint8_t pi_lcd_transmit(uint8_t data);
void pi_lcd_write_data(uint8_t data);
void pi_lcd_write_data_16(uint16_t data);
void pi_lcd_write_reg(uint8_t reg);
void pi_lcd_write_area(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

void pi_lcd_fill(uint16_t color);
void pi_lcd_fill_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void pi_lcd_draw_point (uint16_t x, uint16_t y, uint16_t color);
void pi_lcd_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void pi_lcd_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void pi_lcd_draw_circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color);

void pi_lcd_print_char(uint16_t x, uint16_t y, uint8_t c, uint16_t text_color, uint16_t back_color, uint8_t font_size);
void pi_lcd_print_string(uint16_t x, uint16_t y, const uint8_t *s, uint16_t text_color, uint16_t back_color, uint8_t font_size);

// Catppuccin Mocha - 16-bit (RGB565) Color Palette for TFT screens

#define MOCHA_ROSEWATER 0xF71B // Original: 0xf5e0dc
#define MOCHA_FLAMINGO  0xF679 // Original: 0xf2cdcd
#define MOCHA_PINK      0xF61C // Original: 0xf5c2e7
#define MOCHA_MAUVE     0xCD3E // Original: 0xcba6f7
#define MOCHA_RED       0xF455 // Original: 0xf38ba8
#define MOCHA_MAROON    0xED15 // Original: 0xeba0ac
#define MOCHA_PEACH     0xFD90 // Original: 0xfab387
#define MOCHA_YELLOW    0xFF15 // Original: 0xf9e2af
#define MOCHA_GREEN     0xA714 // Original: 0xa6e3a1
#define MOCHA_TEAL      0x971A // Original: 0x94e2d5
#define MOCHA_SKY       0x8EFD // Original: 0x89dceb
#define MOCHA_SAPPHIRE  0x763D // Original: 0x74c7ec
#define MOCHA_BLUE      0x8DBF // Original: 0x89b4fa
#define MOCHA_LAVENDER  0xB5FF // Original: 0xb4befe
#define MOCHA_TEXT      0xCEBE // Original: 0xcdd6f4
#define MOCHA_SUBTEXT1  0xBE1B // Original: 0xbac2de
#define MOCHA_SUBTEXT0  0xA579 // Original: 0xa6adc8
#define MOCHA_OVERLAY2  0x94D6 // Original: 0x9399b2
#define MOCHA_OVERLAY1  0x7C33 // Original: 0x7f849c
#define MOCHA_OVERLAY0  0x6B90 // Original: 0x6c7086
#define MOCHA_SURFACE2  0x5ACE // Original: 0x585b70
#define MOCHA_SURFACE1  0x422B // Original: 0x45475a
#define MOCHA_SURFACE0  0x3188 // Original: 0x313244
#define MOCHA_BASE      0x18E5 // Original: 0x1e1e2e
#define MOCHA_MANTLE    0x18C4 // Original: 0x181825
#define MOCHA_CRUST     0x1083 // Original: 0x11111b

#define FONT_MINI   12
#define FONT_SMALL  16
#define FONT_MEDIUM 24
#define FONT_LARGE  32

#endif //PI_LCD_H
