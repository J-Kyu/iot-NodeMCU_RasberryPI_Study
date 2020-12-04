import hassapi as  hass


class BtMonitorCtl(hass.Hass):
    def initialize(self):
        self.btSensoriPhone = self.args.get("btSensoriPhone")
        self.stRasbianDisplay = self.args.get("stRasbianDisplay")
        self.log("^^^^^^^^^^^^^^^^^^^^^^^")
        self.log(self.get_state(self.btSensoriPhone))
        self.log("WWWWWWWWWWWWWWWWWWWWWWW")
        self.listen_state(self.ControlMonitorCallback,self.btSensoriPhone)


    def ControlMonitorCallback(self, entity, attribute, old , new, kwargs):

        confidence = float(self.get_state(self.btSensoriPhone))
        isOn = self.get_state(self.stRasbianDisplay)
        self.log("\t2^^^^^^^^^^^^^^^^^^^^^^2")
        self.log("\t{}".format(confidence))
        self.log("\t2wwwwwwwwwwwwwwwwwwwwww2\n")

        if confidence >= 90:
            self.log("Rasbian Display On")
            self.turn_on("switch.rasbian_display")

        elif confidence < 80:
            self.log("Rasbian Display Off")
            self.turn_off("switch.rasbian_display")
