//
// Created by ioyoi on 25-7-1.
//
#include "pi_lcd.h"

void pi_lcd_init(void) {
    pi_lcd_gpio_init();
    pi_lcd_set_init();
}

void pi_lcd_gpio_init(void) {
    rcu_periph_clock_enable(RCU_SPI1);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);

    // Init SPI1
    gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13 | GPIO_PIN_15);
    gpio_bit_set(GPIOB, GPIO_PIN_13 | GPIO_PIN_15);
    gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_14);
    spi_parameter_struct spi_init_struct;
    spi_init_struct.trans_mode = SPI_BIDIRECTIONAL_TRANSMIT;
    spi_init_struct.device_mode = SPI_MASTER;
    spi_init_struct.frame_size = SPI_FRAMESIZE_8BIT;
    spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;
    spi_init_struct.nss = SPI_NSS_SOFT;
    spi_init_struct.prescale = SPI_PSC_8;
    spi_init_struct.endian = SPI_ENDIAN_MSB;
    spi_init(SPI1, &spi_init_struct);
    spi_enable(SPI1);

    // Init other IO
    gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_12);
    gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13);
    gpio_bit_set(GPIOB, GPIO_PIN_1 | GPIO_PIN_12);
    gpio_bit_reset(GPIOB, GPIO_PIN_2);
    gpio_bit_set(GPIOC, GPIO_PIN_13);
}

void pi_lcd_set_init(void) {
    PI_LCD_RST_RESET();
    delay_1ms(100);
    PI_LCD_RST_SET();
    delay_1ms(1);

    // 软件reset
    pi_lcd_write_reg(0x01);
    delay_1ms(120);
    // 关闭睡眠模式
    pi_lcd_write_reg(0x11);
    delay_1ms(120);

    // 横屏显示设置
    // Bottom to Top, Left to Right
    pi_lcd_write_reg(0x36);
    pi_lcd_write_data(0xA0);

    // 色彩格式设置（16bit）
    pi_lcd_write_reg(0x3A);
    pi_lcd_write_data(0x05);

    // 时序设置
    pi_lcd_write_reg(0xB2);
    pi_lcd_write_data(0x0C);
    pi_lcd_write_data(0x0C);
    pi_lcd_write_data(0x00);
    pi_lcd_write_data(0x33);
    pi_lcd_write_data(0x33);

    // 门控电压设置
    pi_lcd_write_reg(0xB7);
    pi_lcd_write_data(0x75);

    // 参考电压（VCOM）设置
    pi_lcd_write_reg(0xBB);
    pi_lcd_write_data(0x22);

    // 控制寄存器（LCMCTRL）设置
    pi_lcd_write_reg(0xC0);
    pi_lcd_write_data(0x2C);

    // VDV、VRH设置
    pi_lcd_write_reg(0xC2);
    pi_lcd_write_data(0x01);
    pi_lcd_write_reg(0xC3);
    pi_lcd_write_data(0x13);
    pi_lcd_write_reg(0xC4);
    pi_lcd_write_data(0x20);

    // 帧率设置
    pi_lcd_write_reg(0xC6);
    pi_lcd_write_data(0x11);

    // 供电设置
    pi_lcd_write_reg(0xD0);
    pi_lcd_write_data(0xA4);
    pi_lcd_write_data(0xA1);

    // Gamma设置
    pi_lcd_write_reg(0xE0);
    pi_lcd_write_data(0xD0);
    pi_lcd_write_data(0x05);
    pi_lcd_write_data(0x0A);
    pi_lcd_write_data(0x09);
    pi_lcd_write_data(0x08);
    pi_lcd_write_data(0x05);
    pi_lcd_write_data(0x2E);
    pi_lcd_write_data(0x44);
    pi_lcd_write_data(0x45);
    pi_lcd_write_data(0x0F);
    pi_lcd_write_data(0x17);
    pi_lcd_write_data(0x16);
    pi_lcd_write_data(0x2B);
    pi_lcd_write_data(0x33);
    pi_lcd_write_reg(0xE1);
    pi_lcd_write_data(0xD0);
    pi_lcd_write_data(0x05);
    pi_lcd_write_data(0x0A);
    pi_lcd_write_data(0x09);
    pi_lcd_write_data(0x08);
    pi_lcd_write_data(0x05);
    pi_lcd_write_data(0x2E);
    pi_lcd_write_data(0x43);
    pi_lcd_write_data(0x45);
    pi_lcd_write_data(0x0F);
    pi_lcd_write_data(0x16);
    pi_lcd_write_data(0x16);
    pi_lcd_write_data(0x2B);
    pi_lcd_write_data(0x33);

    // 开启显示
    pi_lcd_write_reg(0x29);
    delay_1ms(100);
}

uint8_t pi_lcd_transmit(const uint8_t data) {
    // Wait for Transmit buffer empty
    while (RESET == spi_i2s_flag_get(SPI1, SPI_FLAG_TBE)) {}
    // Send Byte
    spi_i2s_data_transmit(SPI1, data);
    // Wait Receive buffer ready
    while (RESET == spi_i2s_flag_get(SPI1, SPI_FLAG_RBNE)) {}
    // Return Received data
    return spi_i2s_data_receive(SPI1);
}

void pi_lcd_write_data(const uint8_t data) {
    PI_LCD_DC_SET();
    PI_LCD_CS_RESET();
    pi_lcd_transmit(data);
    PI_LCD_CS_SET();
    // LCD_WR_DATA8(data);
}

void pi_lcd_write_data_16(const uint16_t data) {
    PI_LCD_DC_SET();
    PI_LCD_CS_RESET();
    pi_lcd_transmit(data >> 8);
    pi_lcd_transmit(data);
    PI_LCD_CS_SET();
    // LCD_WR_DATA16(data);
}

void pi_lcd_write_reg(const uint8_t reg) {
    PI_LCD_DC_RESET();
    PI_LCD_CS_RESET();
    pi_lcd_transmit(reg);
    PI_LCD_CS_SET();
    PI_LCD_DC_SET();
}

void pi_lcd_write_area(const uint16_t x1, const uint16_t y1, const uint16_t x2, const uint16_t y2) {
    pi_lcd_write_reg(0x2a);
    pi_lcd_write_data_16(x1);
    pi_lcd_write_data_16(x2);
    pi_lcd_write_reg(0x2b);
    pi_lcd_write_data_16(y1);
    pi_lcd_write_data_16(y2);
    pi_lcd_write_reg(0x2c);
}

void pi_lcd_fill(const uint16_t color) {
    pi_lcd_fill_rectangle(0, 0, PI_LCD_WIDTH, PI_LCD_HEIGHT, color);
}

void pi_lcd_fill_rectangle(const uint16_t x1, const uint16_t y1, const uint16_t x2, const uint16_t y2, const uint16_t color) {
    pi_lcd_write_area(x1, y1, x2-1, y2-1);
    for (uint16_t x = x1; x < x2; x++) {
        for (uint16_t y = y1; y < y2; y++) {
            pi_lcd_write_data_16(color);
        }
    }
}

void pi_lcd_draw_point(const uint16_t x, const uint16_t y, const uint16_t color) {
    pi_lcd_write_area(x, y, x, y);
    pi_lcd_write_data_16(color);
}

void pi_lcd_draw_line(const uint16_t x1, const uint16_t y1, const uint16_t x2, const uint16_t y2, uint16_t color) {
    uint16_t x_delta = x2 - x1, y_delta = y2 - y1;
    uint16_t x_step, y_step;
    uint16_t x_error = 0, y_error = 0;
    uint16_t x_ptr = x1, y_ptr = y1;
    uint16_t length;

    if (x_delta & 0x8000) {
        x_step = -1;
        x_delta = -x_delta;
    } else if (x_delta == 0) {
        x_step = 0;
    } else {
        x_step = 1;
    }

    if (y_delta & 0x8000) {
        y_step = -1;
        y_delta = -y_delta;
    } else if (y_delta == 0) {
        y_step = 0;
    } else {
        y_step = 1;
    }

    if (x_delta > y_delta) {
        length = x_delta;
    } else {
        length = y_delta;
    }

    for (uint16_t t = 0; t < length; t++) {
        pi_lcd_draw_point(x_ptr, y_ptr, color);
        x_error += x_delta;
        y_error += y_delta;

        if (x_error > length) {
            x_error -= length;
            x_ptr += x_step;
        }

        if (y_error > length) {
            y_error -= length;
            y_ptr += y_step;
        }
    }
}

void pi_lcd_draw_rectangle(const uint16_t x1, const uint16_t y1, const uint16_t x2, const uint16_t y2, uint16_t color) {
    pi_lcd_draw_line(x1, y1, x1, y2, color);
    pi_lcd_draw_line(x1, y2, x2, y2, color);
    pi_lcd_draw_line(x2, y2, x2, y1, color);
    pi_lcd_draw_line(x2, y1, x1, y1, color);
}

void pi_lcd_draw_circle(const uint16_t x, const uint16_t y, const uint16_t radius, uint16_t color) {
    uint16_t dx = 0, dy = radius;
    while (dx <= dy) {
        pi_lcd_draw_point(x + dx, y + dy, color);
        pi_lcd_draw_point(x + dx, y - dy, color);
        pi_lcd_draw_point(x - dx, y + dy, color);
        pi_lcd_draw_point(x - dx, y - dy, color);
        pi_lcd_draw_point(x + dy, y + dx, color);
        pi_lcd_draw_point(x + dy, y - dx, color);
        pi_lcd_draw_point(x - dy, y + dx, color);
        pi_lcd_draw_point(x - dy, y - dx, color);
        dx++;
        if (dx * dx + dy * dy >= radius * radius) {
            dy--;
        }
    }
}