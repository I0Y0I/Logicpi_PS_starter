//
// Created by ioyoi on 25-6-29.
//

#include "pi_usart.h"

uint8_t pi_rx_buffer[PI_RX_BUFF_SIZE] = {0};
uint8_t pi_rx_ptr = 0;
uint8_t pi_rx_len = 0;
uint8_t pi_rx_flag = 0;

void pi_usart_init(const uint32_t baudrate) {
    rcu_periph_clock_enable(RCU_USART0);
    rcu_periph_clock_enable(RCU_GPIOA);
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
    usart_deinit(USART0);
    usart_baudrate_set(USART0, baudrate);
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    usart_enable(USART0);
    usart_interrupt_enable(USART0, USART_INT_RBNE);
    usart_interrupt_enable(USART0, USART_INT_IDLE);
    nvic_irq_enable(USART0_IRQn, 0, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
}

void USART0_IRQHandler(void) {
    // Receive Interrupt
    if (RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE)) {
        if (pi_rx_len < PI_RX_BUFF_SIZE) {
            pi_rx_buffer[pi_rx_ptr++] = USART_DATA(USART0) & 0xff;
        }
        usart_interrupt_flag_clear(USART0, USART_INT_FLAG_RBNE);
    }
    // Receive finished
    else if (RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_IDLE)) {
        pi_rx_buffer[pi_rx_ptr] = '\0';
        pi_rx_len = pi_rx_ptr;
        pi_rx_flag = 1;
        pi_rx_ptr = 0;
        USART_DATA(USART0);
        usart_interrupt_flag_clear(USART0, USART_INT_FLAG_IDLE);
    }
}

int _read(int fd, char *ptr, int len) {
    if (fd == STDIN_FILENO) {
        // Wait for RX
        while (pi_rx_flag == 0);
        if (len > pi_rx_len) {
            len = pi_rx_len;
        }

        for (int i = 0; i < len; i++) {
            ptr[i] = pi_rx_buffer[i];
        }

        pi_rx_flag = 0;

        return len;
    }
    errno = EBADF;
    return -1;
}

int _write(int fd, char *ptr, int len) {
    if (fd == STDOUT_FILENO || fd == STDERR_FILENO) {
        int i;
        for (i = 0; i < len; i++) {
            usart_data_transmit(USART0, (uint16_t)ptr[i]);
            while (RESET == usart_flag_get(USART0, USART_FLAG_TBE));
        }
        return len;
    }
    errno = EBADF;
    return -1;
}

int _lseek(int fd, int ptr, int dir) {
    (void)fd;
    (void)ptr;
    (void)dir;

    errno = EBADF;
    return -1;
}

int _close(int fd) {
    if (fd >= STDIN_FILENO && fd <= STDERR_FILENO) {
        return 0;
    }

    errno = EBADF;
    return -1;
}

int _isatty(int fd) {
    if (fd >= STDIN_FILENO && fd <= STDERR_FILENO) {
        return 1;
    }

    errno = EBADF;
    return 0;
}

int _fstat(int fd, struct stat *st) {
    if (fd >= STDIN_FILENO && fd <= STDERR_FILENO) {
        st->st_mode = S_IFCHR;
        return 0;
    }

    errno = EBADF;
    return 0;
}