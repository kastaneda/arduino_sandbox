import machine, time

led = machine.Pin(2, machine.Pin.OUT)

for c in range(11):
    led.value(1 - led.value())
    time.sleep_ms(250)

# prepare for wake-up: discharge the RST capacitor
d1 = machine.Pin(5, machine.Pin.OUT)
d1.value(1) # now both capacitor legs is HIGH
time.sleep_ms(500)
# set D1 leg to high-impendance state
d1 = machine.Pin(5, machine.Pin.IN)
time.sleep_ms(50)

# final short blink
led.value(0)
time.sleep_ms(100)
led.value(1)

machine.deepsleep()
