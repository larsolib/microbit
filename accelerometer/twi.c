#include "twi.h"
#include "gpio.h"
void twi_init(){
	GPIO->PIN_CNF[0] = (3 << 2)|(6 << 8);
	GPIO->PIN_CNF[30] = (3 << 2)|(6 << 8);
	TWI0->PSELSCL = 0;
	TWI0->PSELSDA = 30;
	TWI0->RXDRDY = 0;
	TWI0->TXDSENT = 0;
	TWI0->ERROR = 0;
	TWI0->FREQUENCY = 0x01980000;
	TWI0->ENABLE = 5;
}

void twi_multi_read(
	uint8_t slave_address,
	uint8_t start_register,
	int registers_to_read,
	uint8_t * data_buffer
	){
	TWI0->ADDRESS = slave_address;
	TWI0->STARTTX = 1;
	
	TWI0->TXDSENT = 0;
	TWI0->TXD = start_register;
	while(!(TWI0->TXDSENT));

	TWI0->RXDRDY = 0;
	TWI0->STARTRX = 1;
	for (int i = 0; i < registers_to_read - 1; i++){
		while(!(TWI0->RXDRDY));
		data_buffer[i] = TWI0->RXD;
		TWI0->RXDRDY = 0;
	}
	TWI0->STOP = 1;
	while(!(TWI0->RXDRDY));
	
	data_buffer[registers_to_read - 1] = TWI0->RXD;

}

void twi_multi_write(
	uint8_t slave_address,
	uint8_t start_register,
	int registers_to_write,
	uint8_t * data_buffer
){
	TWI0->ADDRESS = slave_address;
	TWI0->STARTTX = 1;

	TWI0->TXDSENT = 0;
	TWI0->TXD = start_register;
	while(!TWI0->TXDSENT);

	for (int n = 0; n < registers_to_write; n++){
		TWI0->TXDSENT = 0;
		TWI0->TXD = data_buffer[n];
		while(!TWI0->TXDSENT);
	}
	TWI0->STOP = 0;
}