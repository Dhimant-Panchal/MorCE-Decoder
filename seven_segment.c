#include "includes/seven_segment.h"

#include "pico/stdlib.h"

// ------------------------------------------------------------------

/**
 * Notice that we have eight pins, so we can represent the pins that
 * should be turned on as 8-bit values. The uint8_t type specifically
 * refers to an unsigned 8-bit integer. When individual bits are used
 * to represent data it's known as a bitfield.
 * 
 * We can then use bitwise operations and bitmasks to interpret
 * these bitfields.
 * 
 * Additionally, placing these in an array allows us to define values
 * from 0 - 9 such that we can get the bitfield for a given number by
 * simply indexing the array!
 * 
 * (These bitfields are defined in the ordering of the ALL_SEGMENTS array
 * in the header file, i.e., from A in the most-significant bit to G, then
 * DP in the least-significant bit.)
 */
uint8_t values[] = {
    0b11101110, //A
    0b00111110, //b
    0b10011100, //c
    0b01111010, //d
    0b10011110, //e
    0b10001110, //f
    0b11110110, //g
    0b01101110, //H
    0b00001100, //i
    0b01111000, //j
    0b01101110, //k
    0b00011100, //l
    0b10101000, //m
    0b00101010, //n
    0b11111100, //o
    0b11001110, //p
    0b11100110, //q
    0b00001010, //r
    0b10110110, //s
    0b00011110, //t
    0b01111100, //u
    0b00111000, //v
    0b01010100, //w
    0b01101110, //x
    0b01110110, //y
    0b11011010, //z
    0b00000010, // -
    0b11111110, // B or 8 (error)
    0b00000001, // .
    0b00010000 // _
};

// As an extension task, you could add hexadecimal support to your
// program to display up to 15 in hexadecimal!

// ------------------------------------------------------------------

void seven_segment_init() {
    for (unsigned int i = 0; i < ALL_SEGMENTS_COUNT; i++) {
        gpio_init(ALL_SEGMENTS[i]);
        gpio_set_dir(ALL_SEGMENTS[i], GPIO_OUT);
    }
}

void seven_segment_off() {
    // This display is common-anode, which means we need to turn a GPIO
    // pin ON for it to appear OFF on the display. 
    for (unsigned int i = 0; i < ALL_SEGMENTS_COUNT; i++) {
        gpio_put(ALL_SEGMENTS[i], true);
    }
}

void seven_segment_on() {
    for (unsigned int i = 0; i < ALL_SEGMENTS_COUNT; i++) {
        gpio_put(ALL_SEGMENTS[i], false);
    }
}

unsigned int seven_segment_show(unsigned int number) {
    if (number > 30) return 1;
    for (unsigned int i = 0; i < 30; i++) {
        // Create a mask to check the current bit.
        //
        // Our first segment (A) starts in the most-significant
        // bit of the bitfield, so we need to 7 - i to map i to
        // the bit for the relevant segment as follows:
        //
        // i = 0 -> 7 - i = 7 - 0 = 7
        // i = 1 -> 7 - i = 7 - 1 = 6
        // ...
        // i = 6 -> 7 - i = 7 - 6 = 1
        // i = 7 -> 7 - i = 7 - 7 =  0
        unsigned int segmentBit = 1 << (7 - i);

        // When the segmentBit is 1 << 7, it produces 0b1000_0000.
        // Where 1 is in the most significant bit and all the other
        // bits are 0.

        // Bitwise-and the segmentBit with the bitfield for the
        // current number. If we get zero, it means that segment
        // should turned off, otherwise the bit is turned on.
        bool illuminateSegment = (segmentBit & values[number]); //!= 0;

        // Recall, however, that because the display is common-anode,
        // whenever we want to illuminate a segment, we actually need
        // to pull that pin low (i.e., put false).
        gpio_put(
            ALL_SEGMENTS[i],
            !illuminateSegment
        );
    }

    return 0;

}
