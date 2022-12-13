#!/bin/sh

# Use https://www.engbedded.com/conffuse/
# - Do not use RSTDISBL
# - Do use SPIEN

# Here: BOD off, use internal 1.2 MHz clock
avrdude -p attiny13 -P /dev/ttyUSB0 -c stk500v1 -b 19200 -q -U hfuse:w:0xff:m -U lfuse:w:0x6a:m
