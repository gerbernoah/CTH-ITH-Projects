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

void delay(int ms_50)
{
	TR1 = 1; // startet den timer
	while (interruptCount < ms_50);
	interruptCount = 0;
	TR1 = 0; // stoppt den timer
}

void make_impuls(int ms_50)
{
	impuls = 1;
	delay(ms_50);
	impuls = 0;
	delay(ms_50);
}

void main() {
	init();
	while(schalter == 0 || P1 == 0xFF);
	for (index = 0; index < 4; index++)
	{
		if (ziffer[index] == 0)
			count = 10;
		else
			count = ziffer[index];
		
		for (;count > 0; count--)
			make_impuls(1);
		make_impuls(4);
	}
	end = 1;
	while(1);
}



