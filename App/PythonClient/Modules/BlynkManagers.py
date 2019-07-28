
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

    def update_to_server(self):

        print("Send screen info: " +
              self.blynk_screen.screen_id.__str__() + "/" +
              self.blynk_screen.test_run_actual.__str__() + "/" +
              self.blynk_screen.test_run_total_nb.__str__())

        self.blynk.virtual_write(10, self.screen_id)
        self.blynk.virtual_write(11, self.test_run_total_nb)
        self.blynk.virtual_write(12, self.test_run_actual)

        self.server_update()

    def server_update(self):

        print("Execute a sync on server")
        self.blynk.virtual_sync(10)
        self.blynk.virtual_sync(11)
        self.blynk.virtual_sync(12)

    def set_screen_test_run(self, total, actual):

        self.screen_id = 0
        self.test_run_total_nb = total
        self.test_run_actual = actual

    def set_screen_fail(self):

        self.screen_id = 1

    def set_screen_success(self):

        self.screen_id = 2

class BlynkReader:

    def __init__(self, auth_key):

        self.blynk = blynklib.Blynk(auth_key)

        self.WRITE_EVENT_PRINT_MSG = "[WRITE_VIRTUAL_PIN_EVENT] Pin: V{} Value: '{}'"
        self.READ_PRINT_MSG = "[READ_VIRTUAL_PIN_EVENT] Pin: V{}"

        self.screen_id = 0
        self.test_run_total_nb = 0
        self.test_run_actual = 0

        # register handler for virtual pin V1 write event
        @self.blynk.handle_event('write V*')
        def write_virtual_pin_handler(pin, value):
            print(self.WRITE_EVENT_PRINT_MSG.format(pin, value[0]))

            if pin == 10:
                self.screen_id = value[0]
            if pin == 11:
                self.test_run_total_nb = value[0]
            if pin == 12:
                self.test_run_actual = value[0]

    def run(self):

        self.blynk.run()

    def server_update(self, pin):

        print("Sync pin " + pin.__str__() + " on server")
        self.blynk.virtual_sync(pin)
