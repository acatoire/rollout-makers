
import blynklib


class BlynkSender:

    def __init__(self, auth_key):

        self.blynk = blynklib.Blynk(auth_key)

        self.WRITE_EVENT_PRINT_MSG = "[WRITE_VIRTUAL_PIN_EVENT] Pin: V{} Value: '{}'"
        self.READ_PRINT_MSG = "[READ_VIRTUAL_PIN_EVENT] Pin: V{}"

        self.screen_id = 0
        self.test_run_total_nb = 0
        self.test_run_actual = 0

    def run(self):

        self.blynk.run()

    def update(self):

        print("Send screen info: " +
              self.screen_id.__str__() + "/" +
              self.test_run_total_nb.__str__() + "/" +
              self.test_run_actual.__str__())

        self.blynk.virtual_write(10, self.screen_id)
        self.blynk.virtual_write(11, self.test_run_total_nb)
        self.blynk.virtual_write(12, self.test_run_actual)

    def set_screen_test_run(self, total, actual):

        self.screen_id = 0
        self.test_run_total_nb = total
        self.test_run_actual = actual

    def set_screen_fail(self):

        self.screen_id = 1

    def set_screen_success(self):

        self.screen_id = 2

