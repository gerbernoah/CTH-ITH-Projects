#include <reg51.h>
#include <stdio.h>

sbit LED = P1^0;

//LED blinken
void Aufgabe1() 
{
	while(1)
	{
		LED = ~LED;
	}
}


//LED blinken mit code als gemeinsamer Block
void Aufgabe2a()	
{
	unsigned int i;
	TMOD = 0x10; // timer 1 mode 1
	
	while(1)
	{
		LED = ~LED;  
   
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


//Delay zu 2b und 3
void Delay(unsigned int seconds)
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


//LED blinken mit code modular aufgebaut
void Aufgabe2b()
{	
	while(1)
	{
		LED = ~LED;  
		Delay(1);
	}
}


//Bitmuster tauschen
void Aufgabe3()
{
	int bit1 = 0x70;
	int bit2 = 0xB7;
	
	while(1)
	{
		P2 = bit1;
		Delay(2);
		P2 = bit2;
		Delay(2);
	}
}


void main()
{
	//Aufgabe1();
	//Aufgabe2a();
	//Aufgabe2b();
	Aufgabe3();
}
