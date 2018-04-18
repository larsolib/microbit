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
	volatile uint32_t RESERVED[4];
	volatile uint32_t TXDRDY;
	volatile uint32_t RESERVED1[1];
	volatile uint32_t ERROR;
	volatile uint32_t RESERVED2[7];
	volatile uint32_t RXTO;
	volatile uint32_t RESERVED3[110];
	volatile uint32_t INTEN;
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	volatile uint32_t RESERVED4[93];
	volatile uint32_t ERRORSRC;
	volatile uint32_t RESERVED5[31];
	volatile uint32_t ENABLE;
	volatile uint32_t RESERVED6[1];
	volatile uint32_t PSELRTS;
	volatile uint32_t PSELTXD;
	volatile uint32_t PSELCTS;
	volatile uint32_t PSELRXD;
	volatile uint32_t RXD;
	volatile uint32_t TXD;
	volatile uint32_t RESERVED7[1];
	volatile uint32_t BAUDRATE;
	volatile uint32_t RESERVED8[17];
	volatile uint32_t CONFIG;
} NRF_UART_REG;

void uart_init(){
	GPIO->PIN_CNF[24] = 1;
	GPIO->PIN_CNF[25] = 0;

	UART->PSELTXD = 24;
	UART->PSELRXD = 25;

	UART->PSELCTS = 0xFFFFFFFF;
	UART->PSELRTS = 0xFFFFFFFF;
	UART->BAUDRATE = 0x00275000;
	
	UART->ENABLE = 4;

	UART->STARTTRX = 1;
}

void uart_send(char letter){
	UART->STARTTX = 1;
	UART->TXDRDY = 0;
	UART->TXD = letter;
	while(!UART->TXDRDY);
	UART->STOPTX = 1;
}

char uart_read(){
	if(UART->RXDRDY){
		UART->STARTTRX = 1;
		char rx = UART->RXD;
		UART->STOPRX = 1;
		return rx;
	}
	return '\0';
}
