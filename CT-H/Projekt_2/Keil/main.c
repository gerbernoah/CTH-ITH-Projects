/* 
 * Created:   Mi Nov 17 2021
 * Processor: 80C31
 * Compiler:  Keil for 8051
 */

#include <reg51.h>
#include <stdio.h>

sfr input = 0x90;
sfr output = 0xA0;

unsigned int interruptCount = 0;
int value = 128;

// 3 = timer 1 überlauf
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
    input = 0;      
	output = 4;     // neutraler zustand
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

void main()
{
    init();

	while (1) // endlosschleife
	{
		while (input == 0);
		
		//vorgegebene version mittels switch case (vereinfachung von if)
		/*switch(input)
		{
			case 1: value -= 2; break;
			case 2: value -= 1; break;
			case 4: value += 1; break;
			case 8: value += 2; break;
		}
		*/
		
		// unsere version mittels funktion (funktioniert nicht auf jedem computer)
		value += (input*(-516+input*(364+input*(-77+5*input)))/112)*(!(input&(input-1)));

		value = value > 255 ? 255:value; // setzt value <= 255
		output = 1 << ((value>30) + (value>100) + (value>155) + (value>225));
		
		delay(1);

		while (input != 0);
	}
}
