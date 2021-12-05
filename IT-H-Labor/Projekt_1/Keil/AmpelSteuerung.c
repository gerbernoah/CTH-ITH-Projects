#include <reg51.h>
#include <stdio.h>

sbit led_red = 0xA0;
sbit led_yellow = 0xA1;
sbit led_green = 0xA2;

void Delay(unsigned int seconds);
void DelayWithTimer(unsigned int seconds);
void DelayWithLoop(unsigned int seconds);
void SetLEDState(bit red, bit yellow, bit green);

void main(void)
 { 
    while(1) // infinite loop
    {
        SetLEDState(1, 0, 0);
        Delay(2);
        SetLEDState(1, 1, 0);
        Delay(1);
        SetLEDState(0, 0, 1);
        Delay(4);
        SetLEDState(0, 1, 0);
        Delay(1);
    }
}

void Delay(unsigned int seconds)
{
	//DelayWithLoop(seconds);
	DelayWithTimer(seconds);
}
void DelayWithTimer(unsigned int seconds)
{
		unsigned int i;
	
    TMOD = 0x10; // timer 1 mode 1
   
    for (; seconds > 0; seconds--)
    {
        for (i = 0; i < 20; i++) // delay of 1 second
        {
            // 0x3CB0: 50 ms timer
            TH1 = 0x3C; // set timer high flag
            TL1 = 0xB0; // set timer low flag

            TR1 = 1; // start timer
     
            while (~TF1) { } // wait until timer finished
     
            TR1 = 0; // stop timer
            TF1 = 0; // reset timer flag
        }
    }
}

void DelayWithLoop(unsigned int seconds)
{
	
	 unsigned int i;
	 unsigned int j;

   for (; seconds > 0; seconds--)
   {
        for (i = 0; i < 9550; i++)
        {
            for (j = 0; j < 12; j++) { }
        }
   }
}

void SetLEDState(bit red, bit yellow, bit green)
{
   led_red = red;
   led_yellow = yellow;
   led_green = green;
}