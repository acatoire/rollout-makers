import blynklib
import time

from Modules.RepeatingEvent import RepeatingEvent
from Modules.BlynkManagers import BlynkSender

# BLYNK_AUTH = '1MHwzmqo-DiF1XBll5qOYhemNfte2CYx'
BLYNK_AUTH = 'xbzggg5NU6Ye9G4XD6utHK6l_3nqb5Lr'


class TestCampaignSimulator:

    def __init__(self):

        self.sender = BlynkSender(BLYNK_AUTH)

        self.print_result = False

        self.test_run_total_nb = 0
        self.test_run_actual = 0

        # Start recurring tasks
        # #  Updater of the blynk server
        task_blynk = RepeatingEvent(0.5, self.task_blynk_runner)
        task_blynk.start()
        # #  Recurring task to simulate value update
        task_value = RepeatingEvent(5, self.task_updater)
        task_value.start()

    def task_blynk_runner(self):

        # keep the blynk app up to date
        self.sender.run()

    def task_updater(self):

        # Alternate result and status
        if self.print_result:
            # print result
            self.print_result = False

            if 0 == (self.test_run_actual % 5):
                # every 5 test send a fail
                self.sender.set_screen_fail()
            else:
                # for other send success
                self.sender.set_screen_success()
        else:
            # print status
            self.print_result = True

            # Simulate activity
            self.test_run_total_nb = 30
            self.test_run_actual = (self.test_run_actual + 1) % self.test_run_total_nb

            # update screen
            self.sender.set_screen_test_run(self.test_run_total_nb, self.test_run_actual)

        self.sender.update()


def main():

    # Start the simulator
    simulator = TestCampaignSimulator()

    ###########################################################
    # infinite loop that keep the app running
    ###########################################################
    while True:
        time.sleep(1)


if __name__ == "__main__":
    main()


