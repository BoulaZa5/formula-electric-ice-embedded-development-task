from machine import Pin, Timer
from utime import sleep_ms


last_state = -1
current_state = 0


def change_state(pin):
    global current_state
    current_state = current_state + 1

def run_300(timer):
    global current_state
    if current_state is 3:
        led1.value(not led1.value())
    elif current_state is 4:
        led2.value(not led2.value())
    elif current_state is 5:
        led3.value(not led3.value())

def run_1000(timer):
    global current_state
    if current_state is 2:
        led1.value(not led1.value())
    elif current_state is 3:
        led2.value(not led2.value())
    elif current_state is 4:
        led3.value(not led3.value())


led1 = Pin(4, Pin.OUT)
led2 = Pin(0, Pin.OUT)
led3 = Pin(2, Pin.OUT)

tim300 = Timer(0)
tim1000 = Timer(1)
push_button = Pin(26, Pin.IN, Pin.PULL_DOWN)

tim300.init(mode=Timer.PERIODIC, period=300, callback=run_300)
tim1000.init(mode=Timer.PERIODIC, period=1000, callback=run_1000)
push_button.irq(trigger=Pin.IRQ_RISING, handler=change_state)

while (1):
    if current_state != last_state:
        last_state = current_state
        led1.value(0)
        led2.value(0)
        led3.value(0)
    if current_state is 0:
        pass
    elif current_state is 1:
        led1.value(1)
    elif current_state is 2:
        led2.value(1)
    elif current_state is 3:
        led3.value(1)
    elif current_state is 4:
        pass
    elif current_state is 5:
        pass
    else:
        current_state = 0
    sleep_ms(100)
