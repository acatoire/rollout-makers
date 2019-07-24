import blynklib
import random

BLYNK_AUTH = 'xbzggg5NU6Ye9G4XD6utHK6l_3nqb5Lr'

# initialize Blynk
blynk = blynklib.Blynk(BLYNK_AUTH)

WRITE_EVENT_PRINT_MSG = "[WRITE_VIRTUAL_PIN_EVENT] Pin: V{} Value: '{}'"
READ_PRINT_MSG = "[READ_VIRTUAL_PIN_EVENT] Pin: V{}"


# register handler for virtual pin V4 write event
@blynk.handle_event('write V1')
def write_virtual_pin_handler(pin, value):
    print(WRITE_EVENT_PRINT_MSG.format(pin, value))

# register handler for virtual pin V11 reading
@blynk.handle_event('read V10')
def read_virtual_pin_handler(pin):
    print(READ_PRINT_MSG.format(pin))
    blynk.virtual_write(pin, random.randint(0, 255))


###########################################################
# infinite loop that waits for event
###########################################################
while True:
    blynk.run()
