/* Seven-segment display (5161BS) */
// http://www.xlitx.com/datasheet/5161BS.pdf

// (Raspberry Pi Pico pinout: https://datasheets.raspberrypi.com/pico/Pico-R3-A4-Pinout.pdf)

// --------------------------------------------------------------------

#pragma once

// --------------------------------------------------------------------

// (The top-center and bottom-center PINS are to be connected to the
//  anode - power rail - and you needn't connect both.)
//
// (You can wire top-left of seven-segment display to top-left of the
//  below pins on the Raspberry Pi, etc.,)
//
// (It's also probably best to add a resistor - any will do, but we would
//  suggest using the lowest resistance one provided - which is 220ohm - to
//  avoid damage.)

/** Top-center horizontal bar. */
#define SEGMENT_A            7  // Pin 10 (GPIO 07)

/** Top-right vertical bar */
#define SEGMENT_B            6  // Pin 09 (GPIO 06)

/** Bottom-right vertical bar */
#define SEGMENT_C           20  // Pin 26 (GPIO 20)

/** Bottom-center horizontal bar */
#define SEGMENT_D           19  // Pin 25 (GPIO 19)


/** Bottom-left vertical bar */
#define SEGMENT_E           18  // Pin 24 (GPIO 18)

/** Top-left vertical bar */
#define SEGMENT_F            8  // Pin 11 (GPIO 08)

/** Center horizontal bar */
#define SEGMENT_G            9  // Pin 12 (GPIO 09)

/** Decimal-point */
#define SEGMENT_DP          21  // Pin 27 (GPIO 21)



/** An array containing the pins for all segments. */
static const unsigned int ALL_SEGMENTS[] = {SEGMENT_A, SEGMENT_B, SEGMENT_C, SEGMENT_D, SEGMENT_E, SEGMENT_F, SEGMENT_G, SEGMENT_DP};

/** There are eight total segments (when we include the decimal point). */
#define ALL_SEGMENTS_COUNT  8
// How could you compute the above (at compile-time) without hardcoding it?



// --------------------------------------------------------------------
// (!) You'll need to implement these methods!

/**
 * Called once at the start of the program to initialize all of the GPIO
 * pins responsible for the seven-segment display.
 */
void seven_segment_init();

/** Turn off the entire seven-segment display. */
void seven_segment_off();

/** Turn on the entire seven-segment display. */
void seven_segment_on();

/**
 * Displays the specified number on the seven-segment display. (This function
 * should support all numbers from 0 to 9.)
 * 
 * If the number cannot be displayed (e.g., it's out of range), this
 * method should return a non-zero value.
 * 
 * Otherwise, if the number is valid, the number should be displayed and
 * this method should return 0 to indicate success.
 * 
 * --------------------------------------------------------------------------
 * 
 * Don't get confused with how this function works! If the specified number
 * can be displayed, it should be displayed on the screen immediately by THIS
 * function. The return value is this function's way of showing whether it
 * did this successfully or not.
 * 
 * --------------------------------------------------------------------------
 * 
 * @param number The number to display on the screen.
 * @return Zero if the number has been sucessfully displayed, otherwise a non-zero
 * value.
 */
unsigned int seven_segment_show(unsigned int number);
