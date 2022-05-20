#include <reg51.h>
#include <stdio.h>

unsigned int ziffer[] = {0, 8, 1, 5};
int interruptCount;
int index = 0;
int count;
sbit impuls = P2^0;
sbit schalter = P2^1;
sbit end = P2^2;

void init() {
	TMOD = 0x10;
	IE = 0x88;
	P2 = 0;
}

void timerInterrupt() interrupt 3
{
	TR1 = 0; // stoppt den timer
  TH1 = 0x3C;         // 50 ms
	TL1 = 0xB0;
	interruptCount++;
	TR1 = 1; // startet den timer
}

void delay(float seconds)
{
	TR1 = 1; // startet den timer
	while (interruptCount < seconds * 20);
	interruptCount = 0;
	TR1 = 0; // stoppt den timer
}

void main() {
	init();
	while (!end) {
		while(schalter == 0 || P1 == 0xFF);
		if (ziffer[index] == 0)
			count = 10;
		else
			count = ziffer[index];
		count = count * 2;
	
		for (;count > 0; count--)
		{
			impuls = 1;
			delay(0.2);
			impuls = 0;
			delay(0.2);
		}
		index++;
			if (index == 4)
				end = 1;
		while(1);
	}
}



