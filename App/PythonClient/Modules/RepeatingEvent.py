
from threading import Thread,Event


class RepeatingEvent(Thread):
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

