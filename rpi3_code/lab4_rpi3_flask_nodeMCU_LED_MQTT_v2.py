from flask import Flask
from flask_mqtt import Mqtt

app = Flask(__name__)
app.config['MQTT_BROKER_URL'] = '192.168.137.110'
app.config['MQTT_BROKER_PORT'] = 1883
mqtt = Mqtt(app)

@app.route('/led')
def led_toggle():
    mqtt.publish('iot/21500629', 'led')
    return 'led toggled'
@app.route('/usbled')
def usbled_toggle():
    mqtt.publish('iot/21500629','usbled')
    return 'usb led toggled'


if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=False)