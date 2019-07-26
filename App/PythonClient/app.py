import blynklib
import random
from threading import Timer,Thread,Event

# BLYNK_AUTH = '1MHwzmqo-DiF1XBll5qOYhemNfte2CYx'
BLYNK_AUTH = 'xbzggg5NU6Ye9G4XD6utHK6l_3nqb5Lr'

# initialize Blynk
blynk = blynklib.Blynk(BLYNK_AUTH)


WRITE_EVENT_PRINT_MSG = "[WRITE_VIRTUAL_PIN_EVENT] Pin: V{} Value: '{}'"
READ_PRINT_MSG = "[READ_VIRTUAL_PIN_EVENT] Pin: V{}"


class MyThread(Thread):
    def __init__(self, period, function):
        Thread.__init__(self)

        self.period = period
        self.stopped = Event()
        self.function_call = function

    def run(self):
        while not self.stopped.wait(self.period):
            # call a function
            self.function_call()

    def stop(self):
        self.stopped.set()


def task_1s():
    value = random.randint(0, 9)

    print("Send value: " + value.__str__())
    blynk.virtual_write(1, value)


def main():

    thread = MyThread(5, task_1s)
    thread.start()


    # register handler for virtual pin V1 write event
    @blynk.handle_event('write V1')
    def write_virtual_pin_handler(pin, value):
        print(WRITE_EVENT_PRINT_MSG.format(pin, value))

    # register handler for virtual pin V11 reading
    @blynk.handle_event('read V3')
    def read_virtual_pin_handler(pin):
        print(READ_PRINT_MSG.format(pin))
        blynk.virtual_write(pin, random.randint(0, 9))


    ###########################################################
    # infinite loop that waits for event
    ###########################################################
    while True:
        blynk.run()


if __name__ == "__main__":
    main()


