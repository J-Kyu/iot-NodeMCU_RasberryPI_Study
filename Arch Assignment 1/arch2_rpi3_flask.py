import eventlet
from flask import Flask, render_template
from flask_mqtt import Mqtt
from flask_socketio import SocketIO
import time # library for time delay
import paho.mqtt.client as mqtt

eventlet.monkey_patch()

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
sub_topic_message = 'iot/2/message'

mqtt = Mqtt(app)
socketio = SocketIO(app)


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



################### Function defition #################
# When mqtt is connected, subscribe to following topics
@mqtt.on_connect()
def handle_connect(client, userdata, flags, rc):
    mqtt.subscribe(sub_topic_dht22)
    mqtt.subscribe(sub_topic_cds)
    mqtt.subscribe(sub_topic_dht22_t)
    mqtt.subscribe(sub_topic_dht22_h)
    mqtt.subscribe(sub_topic_message)
# When mqtt receives message from subscribed topic
@mqtt.on_message()
def handle_mqtt_message(client, userdata, message):
    global mqtt_message
    data = dict(
        topic=message.topic,
        payload=message.payload.decode()
    )
    print("-----------",data)
    socketio.emit('mqtt_message', data)

    


@app.errorhandler(404)
def page_not_found(error):
    print(error)
    return render_template('index_lab7.html', result=warningMessage)


########################SockeIO#############################

@socketio.on('message')
def handle_message(message):
    print('received message: ' + message)

@socketio.on("request") 
def request(message): 
    print(message)
    mqtt.publish(pub_topic, message)


if __name__=='__main__':
    socketio.run(app, host='0.0.0.0', port=5000, use_reloader=False, debug=True)
    #app.run(host='0.0.0.0', port=5000, debug=False)