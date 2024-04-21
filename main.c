// Importing necessary libraries
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "includes/morse_tree.h"
#include "includes/parse_input_str.h"
#include "includes/seven_segment.h"

// Defining pins and constants
#define BUTTON_PIN 16
#define ASCII_OFFSET 65

// Main method
int main()
{
	// Initializing components
	stdio_init_all();
	gpio_init(BUTTON_PIN);
	gpio_set_dir(BUTTON_PIN, GPIO_IN);
	gpio_pull_down(BUTTON_PIN);
	seven_segment_init();
	seven_segment_off();

	// Creating Binary Tree data structure - which will be traversed for output
	struct node TOP = populateTree();

	// Definitions of vars which mentain program flow and manage input
	char buffer[5] = ""; // stores dots and dashes (0's and 1's)
	int ind = 0;		 // index variable to append dashes and dots into buffer
	int status = 0;		 // responsible to help with communication between functions with the status of button press

	// Welcome message on start of program
	// Displays Welcome over serial and then HI on the seven-segment display
	printf("Welcome");
	seven_segment_show(7);
	sleep_ms(300);
	seven_segment_off();
	sleep_ms(300);
	seven_segment_show(8);
	sleep_ms(300);
	seven_segment_off();
	sleep_ms(300);
	seven_segment_show(26);
	sleep_ms(300);
	seven_segment_off();
	sleep_ms(300);

	// Main program loop
	while (true)
	{
		if (status != 3)
		{
			seven_segment_off();
		}

		status = 0;

		// Checks if button is pressed or status is pressed
		if (gpio_get(BUTTON_PIN) || status)
		{
			// Stores timestamp on button press start
			absolute_time_t now = get_absolute_time();

			// block execution while button is pressed and check if the button press is shorter than 700ms
			while (gpio_get(BUTTON_PIN))
			{
				// Blinking middle segment on button press
				seven_segment_show(26);
				// checking if press is longer than 700ms
				if (absolute_time_diff_us(now, get_absolute_time()) > 700 * 1000)
				{
					// Printing error message on button press longer than 700ms
					printf("Error: Button held for longer than 700ms\n");
					// Showing 8 on error - button held for longer than 700ms
					seven_segment_show(27);
					status = 3;
					break;
				}
			}
			// The button press was longer than 700ms so it is ignored and the following code needs not be executed
			if (status == 3)
			{
				sleep_ms(700);
				continue;
			}

			seven_segment_off();

			// stores timestamp on button press end
			absolute_time_t later = get_absolute_time();

			// Calculating time of button press
			uint64_t elapsed = absolute_time_diff_us(now, later);
			int elap = elapsed / 1000;

			// If elapsed time is lesser than 200 ms, append dot(0) on buffer
			if ((elap > 1) && (elap < 250))
			{
				seven_segment_show(28); // shows a dot - assures that input has been taken
				sleep_ms(35);
				seven_segment_off();
				if (ind < 5)
				{
					buffer[ind] = '0';
					ind++;
				}
			}

			// If elapsed time is in between 250 ms and 400 ms, append dash(1) on buffer
			else if ((elap > 250) && (elap < 400))
			{
				seven_segment_show(29); // shows a dash - assures that input has been taken
				sleep_ms(35);
				seven_segment_off();
				if (ind < 5)
				{
					buffer[ind] = '1';
					ind++;
				}
			}
			status = 0;
		}

		// stores timestamp on button press end
		absolute_time_t last_pressed = get_absolute_time();
		while (!gpio_get(BUTTON_PIN))
		{
			// if elapsed time is greater than 400 ms, process input and return output on 7seg display
			if (absolute_time_diff_us(last_pressed, get_absolute_time()) > (400 * 1000))
			{
				printf("%c\n", binaryToLetter(TOP, buffer));
				seven_segment_show((int)binaryToLetter(TOP, buffer) - ASCII_OFFSET);
				sleep_ms(300);

				// refreshing buffer on display of output
				for (int i = 0; i < 5; i++)
				{
					buffer[i] = '\0';
				}
				ind = 0;
				break;
			}
			// The following condition applies for an inter-signal gap, so we resume checking for more button
			// presses within one letter once the button is pressed again
			else // If button is pressed , it only exits this loop , so we use status to enable the loop above
			{
				status = 1;
			}
		}
	}
	return 0;
}
/*
Morse code key

A 	·−
B 	−···
C 	−·−·
D 	−··
E 	·
F 	··−·
G 	−−·
H 	····
I 	··
J 	·−−−
K 	−·−
L 	·−··
M 	−−
N 	−·
O 	−−−
P 	·−−·
Q 	−−·−
R 	·−·
S 	···
T 	−
U 	··−
V 	···−
W 	·−−
X 	−··−
Y 	−·−−
Z 	−−··
*/