#include <stdint.h>

#define GPIO ((NRF_GPIO_REGS*) 0x50000000)

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t RESERVED1[120];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

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


	int sleep = 0;
	while(1){

		if(!(GPIO->IN & (1 << 26))){

			for(int row = 13; row < 16; row++){
				GPIO->OUTSET = (1 << row);
			}
		}
		if(!(GPIO->IN & (1 << 17))){
			for(int row = 13; row < 16; row++){
				GPIO->OUTCLR = (1 << row);

			}
		}


		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
