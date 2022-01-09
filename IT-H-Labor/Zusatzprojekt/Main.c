#include <reg51.h>
#include <stdio.h>

int count;

void Main()
{
	count = P2 = IT0 = 0;
	IE = 0x81;
	IT0 = 1;
	while(1);
}

void Ir() interrupt 0	//Externe interrupt 0 an port 3.2
{
	int tens, ones;
	count++;
	if(count > 99)
		return;
	tens = count/10;
	ones = count - tens*10;
	
	P2 = tens << 4;
	P2 += ones;
}