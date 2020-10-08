#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266HTTPClient.h>


#define D0 16
#define D1 5


const char *ssid = "J-Kyu";
const char *password = "password";
const char *mymqtt_Client_id = "iot_21500629";

char *mqtt_topic = "iot/21500629";
char *mqtt_broker = "192.168.137.110";

char message_buff[100];

WiFiClient wifiClient;
int ledPin = D0;
int usbPin = D1;

void callback(char *mqtt_topic, byte *payload, unsigned int length){
  int i = 0;
  Serial.println("Message arrived: topic: " + String(mqtt_topic));
  Serial.println("Length: "+ String(length,DEC));
  //create character buffer with ending null terminator (string)
  
  for(i=0; i<length; i++){
    message_buff[i] = payload[i];
  }
  
  message_buff[i]= '\0';
  String msgString = String(message_buff);
  Serial.println("Payload: "+ msgString);
  int ledState = digitalRead(ledPin);
    int usbState = digitalRead(usbPin);
  //전송된 메시가 "led"이면 LED를 받을 때마다 켜고 끈다.(토글)
  if (msgString == "led"){
    digitalWrite(ledPin, !ledState);
    Serial.println("Switching LED");
  }
  else if (msgString == "usbled"){
    digitalWrite(usbPin, !usbState);
    Serial.println("Switching USB LED");
  }
}


PubSubClient espClient(mqtt_broker, 1883, callback,wifiClient);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(10);

  //led
  pinMode(ledPin, OUTPUT); // Initialize the LED_BUILTIN pin as an output
  digitalWrite(ledPin, LOW); //LED off

  //usb led
  pinMode(usbPin, OUTPUT); // Initialize the LED_BUILTIN pin as an output
  digitalWrite(usbPin, HIGH); //LED off

  
  //Connect to wifi my network;
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  //wifi에 연결을 시도한다.
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
    //연결되면 접속한 IP가 뭔지 출력한다.
    Serial.println("");
    Serial.print("WiFi Connected: ");
    Serial.println(WiFi.localIP());
    
    //Connection to broker
    if (espClient.connect(mymqtt_Client_id)){
      espClient.publish(mqtt_topic, "Publishing message from my nodeMCU");
      espClient.subscribe(mqtt_topic);
    }
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  espClient.loop();

}
