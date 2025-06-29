//
// Created by ioyoi on 25-6-29.
//

#ifndef PI_USART_H
#define PI_USART_H

#include "gd32f30x.h"

#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define PI_RX_BUFF_SIZE 64
extern uint8_t pi_rx_buffer[PI_RX_BUFF_SIZE];
extern uint8_t pi_rx_flag;

void pi_usart_init(uint32_t baudrate);
void USART0_IRQHandler(void);

#endif //PI_USART_H
