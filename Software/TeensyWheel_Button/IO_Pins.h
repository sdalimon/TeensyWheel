#ifndef IO_PINS_H
#define IO_PINS_H

// IO Assignments

// Analog Inputs
const int WHEEL      = A6; // Wheel
const int ACCEL      = A8; // Pedals
const int BRAKE      = A9; // Pedals

// Digital Inputs
const int DP_UP      =  7; // D Pad
const int DP_DOWN    = 16; // D Pad
const int DP_LEFT    = 17; // D Pad
const int DP_RIGHT   =  8; // D Padd
const int PAD_R      = 35; // Paddles
const int PAD_L      = 30; // Paddles
const int GEAR_UP    =  1; // Gearshift
const int GEAR_DOWN  =  0; // Gearshift
const int GEAR_REV   =  2; // Gearshift
const int BTN_1      = 34; // Wheel Buttons
const int BTN_2      = 31; // Wheel Buttons
const int BTN_3      = 32; // Wheel Buttons
const int BTN_4      = 33; // Wheel Buttons
const int BTN_5      = 19; // L1 LB Button
const int BTN_6      =  6; // R1 RB Button
const int BTN_7      =  5; // L2 LT Button
const int BTN_8      =  4; // R2 RT Button
const int BTN_9      = 13; // SHARE Button - Oops conflicts with LED.  I hope i still works.
const int BTN_10     = 39; // OPTIONS Button
const int BTN_11     = 21; // L3 SL Button
const int BTN_12     =  3; // R3 SR Button
const int BTN_MODE   =  9; // MODE Button
const int SENSE_HIGH = 25; // Sensitivity Switch
const int SENSE_MED  = 40; // Sensitivity Switch
const int SENSE_LOW  = 24; // Sensitivity Switch

// Digital Outputs
const int LED1       = 10; // Wheel LEDS
const int LED2       = 15; // Wheel LEDs
const int LED3       = 11; // Wheel LEDs
const int LED4       = 14; // Wheel LEDs
const int LEDR       = 41; // Bicolour status LED
const int LEDG       = 12; // Bicolour status LED
const int VIB_1      = 37; // Vibrator Control
const int VIB_2      = 36; // Vibrator Control

// Input to Windows Joystick button mapping {Button 0 Input, Button 1 Input, ...}
const int NUM_BTNS = 18;
const int BTN_MAP[NUM_BTNS] = {BTN_1, BTN_2, BTN_3, BTN_4, BTN_5, BTN_6, BTN_7, BTN_8, BTN_9, BTN_10, BTN_11, BTN_12, \
                               BTN_MODE, GEAR_UP, GEAR_DOWN, GEAR_REV, SENSE_HIGH, SENSE_LOW};
#endif
