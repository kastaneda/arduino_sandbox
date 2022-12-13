#!/bin/sh
avr-gcc -g -DF_CPU=1200000 -Wall -Os -mmcu=attiny13a -c -o blink.o ATtiny13_blink.c
avr-gcc -g -DF_CPU=1200000 -Wall -Os -mmcu=attiny13a -o blink.elf blink.o
avr-size blink.elf
avr-objcopy -j .text -j .data -O ihex blink.elf blink.hex
