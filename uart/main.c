#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "gpio.h"

void illuminati_party();
ssize_t _write(int fd, const void *buf, size_t count);

int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	//B
	GPIO->PIN_CNF[17] = 0;

	//A
	GPIO->PIN_CNF[26] = 0;

	uart_init();
	iprintf("Norway has %d counties.\n\r", 18);
	int sleep = 0;
	while(1){
		char rx = uart_read();

		uart_send(rx);

		if(!(GPIO->IN & (1 << 17))){
			uart_send('A');
		}
		if(!(GPIO->IN & (1 << 26))){
			uart_send('B');
		}

		while((!(GPIO->IN & (1 << 17)))||(!(GPIO->IN & (1 << 26))));

		if(rx != ('\0')){illuminati_party();}

		sleep = 1000;
		while(--sleep);
	}
	return 0;
}

ssize_t _write(int fd, const void *buf, size_t count){
	char * letter = (char *)(buf);
	for(int i = 0; i < count; i++){
		uart_send(*letter);
		letter++;
	}
	return count;
}

void illuminati_party(){

	static int TOGGLE = 1;

	if(TOGGLE){
		for(int row = 13; row < 16; row++){
			GPIO->OUTSET = (1 << row);
		}
	}
	else{	
		for(int row = 13; row < 16; row++){
			GPIO->OUTCLR = (1 << row);
		}
	}
	TOGGLE = !TOGGLE;
}