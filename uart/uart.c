#include "uart.h"
#include "gpio.h"

#include <stdint.h>
#define UART ((NRF_UART_REG*)0x40002000)
typedef struct {
	volatile uint32_t STARTTRX;
	volatile uint32_t RESERVED0[191];
	volatile uint32_t INTEN;
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	volatile uint32_t RESERVED1[93];
	volatile uint32_t ERRORSRC;
	volatile uint32_t RESERVED3[31];
	volatile uint32_t ENABLE;
	volatile uint32_t RESERVED3[1];
	volatile uint32_t PSELRTS;
	volatile uint32_t PSELTXD;
	volatile uint32_t PSELCTS;
	volatile uint32_t PSELRXD;
	volatile uint32_t RXD;
	volatile uint32_t TXD;
	volatile uint32_t RESERVED4[1];
	volatile uint32_t BAUDRATE;
	volatile uint32_t RESERVED5[11];
	volatile uint32_t CONFIG;
} NRF_UART_REG;

void uart_init(){
	UART->PSELCTS = 0xFFFFFFFF;
	UART->PSELRTS = 0xFFFFFFFF;
	UART->BAUDRATE = 0x00275000;
	

	UART->PSELTXD = (1 << 24);
	UART->PSELRXD = (1 << 25);
	UART->ENABLE = 4;

	UART->STARTTRX = 1;
}

void uart_send(char letter){
	UART->TXD = letter;
}