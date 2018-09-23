from machine import Pin, ADC
from utime import sleep_ms


def write_to_comanode_7seg(value, seven_seg_leds):
    seven_seg = { 0: (0, 0, 0, 0, 0, 0, 1),
                  1: (1, 0, 0, 1, 1, 1, 1),
                  2: (0, 0, 1, 0, 0, 1, 0),
                  3: (0, 0, 0, 0, 1, 1, 0),
                  4: (1, 0, 0, 1, 1, 0, 0),
                  5: (0, 1, 0, 0, 1, 0, 0)}
    for count, led in enumerate(seven_seg_leds):
            led.value(seven_seg[ans][count])

			
a = Pin(0, Pin.OUT, Pin.PULL_UP)
b = Pin(2, Pin.OUT, Pin.PULL_UP)
c = Pin(27, Pin.OUT, Pin.PULL_UP)
d = Pin(26, Pin.OUT, Pin.PULL_UP)
e = Pin(25, Pin.OUT, Pin.PULL_UP)
f = Pin(4, Pin.OUT, Pin.PULL_UP)
g = Pin(21, Pin.OUT, Pin.PULL_UP)
seven_seg_leds = (a, b, c, d, e, f, g)

adc = ADC(Pin(32, Pin.IN))
last_reading = 6

while (1):
    ans = int((adc.read() * 5 / 4095) + 0.5)
    if last_reading != ans:
        last_reading = ans
        write_to_comanode_7seg(ans, seven_seg_leds)
    sleep_ms(100)
