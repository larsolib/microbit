#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "twi.h"
#include "ubit_led_matrix.h"
#include "gpio.h"
#include "accel.h"

int main(){
	ubit_led_matrix_init();
	twi_init();
	accel_init();
	// uint8_t slave_address = 0x1D;
	// uint8_t start_register = 0x0D;
	// uint8_t *data_buffer;
	// data_buffer = (uint8_t *)malloc(8* sizeof(uint8_t));

	// twi_multi_read(slave_address, start_register, 1, data_buffer);
	// if(data_buffer[0] == 0x5A){
	// 	ubit_led_matrix_light_only_at(1,1);
	// }
	// free(data_buffer);
	int *data_buffer1;
	data_buffer1 = (int *)malloc(8* sizeof(int));
	int x_acc, y_acc;
	int x_dot, y_dot;

	int sleep;
	while(1){

		accel_read_x_y_z(data_buffer1);
		
		x_acc = data_buffer1[0];
		y_acc = data_buffer1[1];
		

		x_dot = x_acc / 50;
		y_dot = -y_acc / 50;
		if (x_dot > 2 ){
			x_dot = 2;
		}
		else if (x_dot < -2){
			x_dot = -2;
		}

		if (y_dot > 2 ){
			y_dot = 2;
		}
		else if (y_dot < -2){
			y_dot = -2;
		}


		ubit_led_matrix_light_only_at(x_dot, y_dot);
		sleep = 1000000;
		
		while(--sleep);
	}
	free(data_buffer1);
	return 0;
}