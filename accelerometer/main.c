#include <stdint.h>
#include <stdlib.h>
#include "twi.h"
#include "ubit_led_matrix.h"
#include "gpio.h"

int main(){
	ubit_led_matrix_init();
	ubit_led_matrix_light_only_at(0,0);
	twi_init();

	uint8_t slave_address = 0x01D;
	uint8_t start_register = 0x0D;
	uint8_t *data_buffer;
	data_buffer = (uint8_t *)malloc(8* sizeof(uint8_t));

	twi_multi_read(slave_address, start_register, 1, data_buffer);
	if(data_buffer[0] != 0){
		ubit_led_matrix_light_only_at(1,1);
	}
	free(data_buffer);
	ubit_led_matrix_light_only_at(0,1);
	
	while(1);

	return 0;
}