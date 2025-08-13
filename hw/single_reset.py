import machine
import time

# GPIO 2 == pin D4 == built-in LED
# the LED is inverted, HIGH = no light, LOW = bright blue
led = machine.Pin(2, machine.Pin.OUT)

# BLINK EXACTLY FIVE TIMES
# and also give us some time to ensure
# that the button does not restart the MCU yet
for c in range(9):
    print(led, 'value =', led.value())
    time.sleep_ms(250)
    led.value(1 - led.value())

print(led, 'value =', led.value())
# why is there 9 state changes, not 10?
# bacause the LED is inverted and it's initial value is 0
# sooo, we end the loop with 1, meaning the LED is off

# or do it fancy
#p = machine.PWM(led)
#p.freq(10000)
#for c in range(5):
#    for d in range(1007, 256, -16):
#        p.duty(d)
#        time.sleep_ms(3)
#    for d in range(256, 1023, 16):
#        p.duty(d)
#        time.sleep_ms(3)
#p.deinit()
#time.sleep_ms(5)
#led.value(1)

time.sleep_ms(500)

# XXX DEBUG LOLWUT
print('---------------------------------------')
d1 = machine.Pin(5, machine.Pin.IN, machine.Pin.PULL_UP)
print(d1, 'value =', d1.value())
print('---------------------------------------')

# PREPARE FOR WAKE-UP
# discharge the RST capacitor by setting HIGH on both ends
# initialize with high level on early configuration stage
# GPIO 5 == pin D1
d1 = machine.Pin(5, mode=machine.Pin.OUT, value=1)
# otherwise, the next line of code, kinda 'd1.value(1)'
# may not got a chance to run due to a sudden restart

# give it some time (that's much more than it actually need)
time.sleep_ms(100)

# after all that, set D1 to high-impendance mode with pull-up
d1 = machine.Pin(5, machine.Pin.IN, machine.Pin.PULL_UP)
time.sleep_ms(100)

# XXX
print(d1, 'value =', d1.value())
print('---------------------------------------')

# FINAL SHORT BLINK
# just to debug / to show we're going to deep sleep
led.value(0)
time.sleep_ms(100)
led.value(1)

machine.deepsleep()
