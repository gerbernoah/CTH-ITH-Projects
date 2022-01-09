#include <reg51.h>
#include <stdio.h>

int table[] =
{
	0x00,
	0x80,
	0xC0,
	0xE0,
	0xF0,
	0xF8,
	0xFC,
	0xFE,
	0xFF,
	0xFE,
	0xFC,
	0xF8,
	0xF0,
	0xE0,
	0xC0,
	0x80
};

int interruptCount;

void timerInterrupt() interrupt 3
{
	TR1 = 0; // stoppt den timer
  // 50 ms
  TH1 = 0x3C;         
	TL1 = 0xB0;
	
	interruptCount++;
	
  TR1 = 1; // startet den timer
}

void init()
{
	TMOD = 0x10;    // timer 1 modus 1
	IE = 0x88;      // setzt die bits EA & ET1
  // 50 ms
  TH1 = 0x3C;
	TL1 = 0xB0;
}

void delay(unsigned int seconds)
{
	TR1 = 1; // startet den timer
	while (interruptCount < seconds * 20);
	interruptCount = 0;
	TR1 = 0; // stoppt den timer
}

void Main()
{
	int i;
	init();
	while(1)
	{
		for(i = 0; i < 16; i++)
		{
			P2 = table[i];
			delay(2);
		}
	}
}