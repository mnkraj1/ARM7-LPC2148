#include <lpc214x.h>

volatile int flag = 0;
__irq void Ext_ISR(void) { 
	flag = !flag;
  EXTINT |= 0x4;
  VICVectAddr = 0;
}

void init();

int main() {
	IO0DIR |= (1<<31); 
	init();
	while(1) {
		if(flag == 0) {
			 IO0SET |= (1<<31); 
		} else {
			IO0CLR |= (1<<31);
		}
	}
	return 0;
}

void init() {
	EXTMODE = 0x04; // Edge triggered for eint2
	EXTPOLAR = 0x00; // falling edge for eint 2
	PINSEL0 = 0x80000000;
	VICIntSelect &= ~(1<<16); 
	VICVectAddr0 = (unsigned long)Ext_ISR;
	VICVectCntl0 = 0x20 | 16;
	VICIntEnable = (1<<16);
	
	EXTINT &= ~(0x04); 
}