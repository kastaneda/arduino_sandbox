#!/bin/sh
avrdude -p attiny13 -c stk500v1 -P /dev/ttyUSB0 -b 19200 -q -U flash:w:blink.hex
