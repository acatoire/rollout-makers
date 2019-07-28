import blynklib
import time

from Modules.RepeatingEvent import RepeatingEvent
from Modules.BlynkManagers import BlynkReader

# BLYNK_AUTH = '1MHwzmqo-DiF1XBll5qOYhemNfte2CYx'
BLYNK_AUTH = 'xbzggg5NU6Ye9G4XD6utHK6l_3nqb5Lr'


# TODO

class ScreenSimulator:

    def __init__(self):

        self.blynk_screen = BlynkReader(BLYNK_AUTH)

        self.pin = 10

        # Start recurring tasks
        # #  Updater of the blynk server
        task_blynk = RepeatingEvent(0.5, self.task_blynk_runner)
        task_blynk.start()
        # #  Recurring task to simulate value update
        task_value = RepeatingEvent(1, self.task_reader)
        task_value.start()

    def task_blynk_runner(self):

        # keep the blynk app up to date
        self.blynk_screen.run()

    def task_reader(self):

        # Get value from server
        self.blynk_screen.server_update(self.pin)

        if self.pin == 10:
            self.pin = 11
        elif self.pin == 11:
            self.pin = 12
        elif self.pin == 12:
            self.pin = 10

        # Print Receive values
        print("Read screen info: " +
              self.blynk_screen.screen_id.__str__() + "/" +
              self.blynk_screen.test_run_actual.__str__() + "/" +
              self.blynk_screen.test_run_total_nb.__str__())


def main():

    # Start the simulator
    simulator = ScreenSimulator()

    ###########################################################
    # infinite loop that keep the app running
    ###########################################################
    while True:
        time.sleep(1)


if __name__ == "__main__":
    main()


