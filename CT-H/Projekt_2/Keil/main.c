/* 
 * Created:   Mi Nov 17 2021
 * Processor: 80C31
 * Compiler:  Keil for 8051
 */

#include <reg51.h>
#include <stdio.h>

sfr input = 0x90;
sfr output = 0xA0;
unsigned int tic = 0;
int value = 128;

void ti() interrupt 3
{
	TR1 = 0;
	TH1 = 0x3C;
	TL1 = 0xB0;
	tic++;
	TR1 = 1;
}

void init()
{
	output = 4;
	input = 0;
	TMOD = 0x10;
	IE = 0x88;
	TH1 = 0x3C;
	TL1 = 0xB0;
}

void delay(unsigned int seconds)
{
	TR1 = 1;
	while(tic < seconds*20);
	tic = 0;
	TR1 = 0;
}

void main()
{
init();
	while(1)
	{
		while(input == 0);
		
		//vorgegebene versoin mitels switch case (vereinfachung von if)
		/*switch(input)
		{
			case 1: value -= 2; break;
			case 2: value -= 1; break;
			case 4: value += 1; break;
			case 8: value += 2; break;
		}
		*/
		
		
		//unsere version mitels funktion (funktioniert nicht auf jedem computer)
		value += (input*(-516+input*(364+input*(-77+5*input)))/112)*(!(input&(input-1)));

		
		
		value = value > 255 ? 255:value; //makes value <= 255
		output = 1 << ((value>30) + (value>100) + (value>155) + (value>225));
		
		delay(1);
		while(input != 0);
	}
}