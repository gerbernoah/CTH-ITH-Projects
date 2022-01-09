#include <reg51.h>
#include <stdio.h>

int count;

void Main()
{
	count = P2 = IT0 = 0;
	IE = 0x85;
	IT0 = 1;
	IT1 = 1;
	while(1);
}

void Ausgabe()
{
	int tens, ones;
	tens = count/10;
	ones = count - tens*10;
	
	P2 = tens << 4;
	P2 += ones;
}

void Ir1() interrupt 0	//Externe interrupt 0 an port 3.2
{
	if(count > 98)
		return;
	count++;
	Ausgabe();
}

void Ir2() interrupt 2	//Externe interrupt 2 an port 3.3
{
	
	if(count == 0)
		return;
	count--;
	Ausgabe();
}

