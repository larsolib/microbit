#include "uart.h"
#include "gpio.h"

#include <stdint.h>
#define UART ((NRF_UART_REG*)0x40002000)
//TGT_RXD pin 25
//TGT_TXD pin 24
typedef struct {
	volatile uint32_t STARTTRX;
	volatile uint32_t STOPRX;
	volatile uint32_t STARTTX;
	volatile uint32_t STOPTX;
	volatile uint32_t RESERVED0[60];
	volatile uint32_t CTS;
	volatile uint32_t NCTS;
	volatile uint32_t RXDRDY;
	volatile uint32_t RESERVED;
	volatile uint32_t TXDRDY;
	volatile uint32_t RESERVED1[120];
	volatile uint32_t INTEN;
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	volatile uint32_t RESERVED2[93];
	volatile uint32_t ERRORSRC;
	volatile uint32_t RESERVED3[31];
	volatile uint32_t ENABLE;
	volatile uint32_t RESERVED4[1];
	volatile uint32_t PSELRTS;
	volatile uint32_t PSELTXD;
	volatile uint32_t PSELCTS;
	volatile uint32_t PSELRXD;
	volatile uint32_t RXD;
	volatile uint32_t TXD;
	volatile uint32_t RESERVED5[1];
	volatile uint32_t BAUDRATE;
	volatile uint32_t RESERVED6[11];
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
	UART->TXDRDY = 0;
	UART->TXD = (uint32_t)letter;
	while(UART->TXDRDY & (0)){continue;}
	UART->STARTTRX = 0;
}

char uart_read(){
	UART->RXDRDY = 0;
	uint32_t temp = UART->RXD;
	if(temp){
		return (char)temp;
	}
	return '\0';
}
