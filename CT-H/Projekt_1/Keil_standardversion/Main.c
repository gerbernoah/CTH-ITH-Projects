/* 
 * Created:   Mi Nov 17 2021
 * Processor: 80C31
 * Compiler:  Keil for 8051
 */

#include <reg51.h>
#include <stdio.h>

//ablage der codes
unsigned int codes[4][3] = {
    { 9, 0, 3 },
    { 2, 4, 7 },
    { 5, 1, 2 },
    { 1, 6, 3 }
};

sfr input = 0x90;    // input equals port 1
sfr output = 0xA0;     // output equals port 2

sbit led_true = P3^0;
sbit led_false = P3^1;
sbit input_submit = P3^2;
sbit dip_submit = P3^3;

unsigned int selected_index;
unsigned int real_digit;
unsigned int input_count;
unsigned int error;

void Pruefe();
int HoleWert();

void main()
{ 
    led_false = led_true = input_count = error = output = 0; // reset everything

    while (dip_submit);         // stay here until code is submited
    selected_index = input >> 4;     //return dip state

    while (1)
    {
        while (input_submit)
        {
            output = input & 0x0F; // set output to input
        }
        Pruefe(); // check if input was successful
    }
}

void Pruefe()
{    
    if (output != HoleWert()) // increment error count if code is wrong
        error = 1; 

    if (input_count == 2)
    {
        led_false = error;
        led_true = !error;
        
        while (1); // stay here forever
    }
    
    input_count++;         // increment input count
    while (!input_submit);     // wait until submit released
}

int HoleWert()
{
    return codes[selected_index][input_count];
}