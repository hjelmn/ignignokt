/* 
 * File:   main.c
 * Author: hjelmn
 *
 * Created on February 25, 2024, 8:53 AM
 */

// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = OFF       // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#define _XTAL_FREQ 4000000  

/**
 * Wait for a given number of milli-seconds using busy waiting scheme.
 * @param time - time in ms to wait.
 */
#define wait_ms(time) __delay_ms(time)

/* Delay 500ms before reacting to the switch again. */
const unsigned long switch_delay = 500;

void configure_pins() {
    ANSEL = 0;
    GPIO = 0;
    nGPPU = 0;
    CMCON = 0b00000111;
    
    /* Configure the input pins. Pin 5 (GPIO 2) is connected to a switch to
     * ground and pin 7 (GPIO 0) is connected to a potentiometer and photo
     * resistor. Configure the output pin which will turn on/off the LEDs. This
     * is pin 3 (GPIO 4). */
    TRISIO = 0b00101;

    WPU = 0b0100;
}

int switch_activated() {
    if (GPIO2 == 0) {
        wait_ms(100);
        return GPIO2 == 0;
    }
    return 0;
}

void reset_photo_input() {
    /* Set the photoresistor pin to output temporarily */
    TRISIO = 0b00100;
    /* Pull to ground */
    GPIO0 = 0;
    __delay_us(2);
    /* Change back to input. */
    TRISIO = 0b00101;
}

void set_output(unsigned char value) {
    GPIO = value << 4;
}

int detect_brightness() {
    int counter = 0;
    reset_photo_input();
    while (GPIO0 == 0) {
        if (++counter == 10000) {
            return 10000;
        }
    }

    return counter;
}

/*
 * 
 */
int main(int argc, char** argv) {
    configure_pins();
    
    unsigned char toggle = 0;

    while (1) {
        if (switch_activated()) {
            toggle = toggle ? 0 : 1;
        }

        if (toggle || (detect_brightness() >= 8)) {
            set_output(1);
        } else {
            set_output(0);
        }
    }
    
    return (EXIT_SUCCESS);
}

