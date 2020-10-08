from flask import Flask, render_template
from flask_mqtt import Mqtt
import time # library for time delay
import paho.mqtt.client as mqtt
app = Flask(__name__)
app.config['MQTT_BROKER_URL'] = '203.252.106.154'
app.config['MQTT_BROKER_PORT'] = 1883
app.config['MQTT_USERNAME'] = 'iot' # Username for MQTT
app.config['MQTT_PASSWORD'] = 'csee1414' # Password for MQTT
mqtt = Mqtt(app)
pub_topic = 'iot/2'
sub_topic_dht22 = 'iot/2/dht22'
sub_topic_cds = 'iot/2/cds'
sub_topic_dht22_t = 'iot/2/dht22_t'
sub_topic_dht22_h = 'iot/2/dht22_h'
# global variable for message payload
mqtt_message=''
warningMessage = 'Not Intended Page...please check your url again~!'
print('@@ Use URL: /iot/2/{led,dht22}')


################### routing ##################

@app.route('/')
def index():
    return render_template('index_lab7.html', result='Hi J-Kyu')
@app.route('/iot/2')
def index2():
    return render_template('index_lab7.html', result='Hi J-Kyu')


@app.route('/iot/2/<cmd>')
def get_command(cmd):
    global mqtt_message
    if cmd == 'led':
        mqtt.publish(pub_topic, 'led')
        return render_template('index_lab7.html', result='LED Toggle')
    elif cmd == 'dht22':
        mqtt.publish(pub_topic, 'dht22')
        time.sleep(2)
        return render_template('index_lab7.html', result=mqtt_message)
    elif cmd == 'cds':
        mqtt.publish(pub_topic, 'cds')
        time.sleep(2)
        return render_template('index_lab7.html', result=mqtt_message)
    elif cmd == 'dht22_t':
        mqtt.publish(pub_topic, 'dht22_t')
        time.sleep(2)
        return render_template('index_lab7.html', result=mqtt_message)
    elif cmd == 'dht22_h':
        mqtt.publish(pub_topic, 'dht22_h')
        time.sleep(2)
        return render_template('index_lab7.html', result=mqtt_message)
    elif cmd == 'ledon':
        mqtt.publish(pub_topic, 'LED/ON')
        return render_template('index_lab7.html', result='LED ON')
    elif cmd == 'ledoff':
        mqtt.publish(pub_topic, 'LED/OFF')
        return render_template('index_lab7.html', result='LED OFF')
    elif cmd == 'usbledon':
        mqtt.publish(pub_topic, 'USBLED/ON')
        return render_template('index_lab7.html', result='USB LED ON')
    elif cmd == 'usbledoff':
        mqtt.publish(pub_topic, 'USBLED/OFF')
        return render_template('index_lab7.html', result='USB LED OFF')
    elif cmd == 'usbled':
        mqtt.publish(pub_topic, 'USBLED')
        return render_template('index_lab7.html', result='USB LED Toggle')
    else:
        return render_template('index_lab7.html', result=warningMessage)
################### Function defition #################
# When mqtt is connected, subscribe to following topics
@mqtt.on_connect()
def handle_connect(client, userdata, flags, rc):
    mqtt.subscribe(sub_topic_dht22)
    mqtt.subscribe(sub_topic_cds)
    mqtt.subscribe(sub_topic_dht22_t)
    mqtt.subscribe(sub_topic_dht22_h)
# When mqtt receives message from subscribed topic
@mqtt.on_message()
def handle_mqtt_message(client, userdata, message):
    global mqtt_message

    topic = message.topic
    payload = message.payload.decode('utf-8')

    mqtt_message = payload
    print ("Topic: " , payload)

@app.errorhandler(404)
def page_not_found(error):
    print(error)
    return render_template('index_lab7.html', result=warningMessage)


if __name__=='__main__':
    app.run(host='0.0.0.0', port=5000, debug=False)