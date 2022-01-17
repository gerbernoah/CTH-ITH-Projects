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

void init()
{
	TMOD = 0x10;    // timer 1 modus 1
}

void Delay(unsigned int seconds)
{
	unsigned int i;
   
    for (; seconds > 0; seconds--)
    {
        for (i = 0; i < 20; i++) // delay of 1 second
        {
            // 0x3CB0: 50 ms timer
            TH1 = 0x3C; // set timer high flag
            TL1 = 0xB0; // set timer low flag

            TR1 = 1; // start timer
     
            while (~TF1); // wait until timer finished
     
            TR1 = 0; // stop timer
            TF1 = 0; // reset timer flag
        }
    }
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
			Delay(2);
		}
	}
}