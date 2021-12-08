/* 
 * Created:   Mi Nov 17 2021
 * Processor: 80C31
 * Compiler:  Keil for 8051
 */

#include <reg51.h>
#include <stdio.h>

unsigned int codes[4][3] = {
	{ 9, 0, 3 },
	{ 2, 4, 7 },
	{ 5, 1, 2 },
	{ 1, 6, 3 }
};

sfr input = 0x90;
sfr output = 0xA0;

sbit input_submit = P3^2;
sbit dip_submit = P3^3;

sbit led_true = P3^0;
sbit led_false = P3^1;

int selected_index;
unsigned int input_count;
unsigned int error_count;
unsigned int real_digit;

void Check();
void Show(int);
int GetIndex();
int GetSelectedDigit();

void main()
{ 
	led_false = led_true = input_count = error_count = output = 0; //reset variables and outputs

	while (dip_submit) { } // stay here if no code is selected
	selected_index = input >> 4; //return dip state

	while (1)
	{
		while (input_submit)
		{
			output = input; // set output to input
		}
		Check(); // check if input was successful
	}
}

void Check()
{	
	if (input_count < 3)
	{
		real_digit = codes[selected_index][input_count];

		if (output != real_digit) // increment error count if code wrong
			error_count++; 
	}

	if (input_count == 2)
	{
		led_false = (error_count > 0);
		led_true = (error_count == 0);
		
		while (1); // stay here forever
	}
	
	input_count++; // increment input count
	while (!input_submit); //wait until submit released
}
