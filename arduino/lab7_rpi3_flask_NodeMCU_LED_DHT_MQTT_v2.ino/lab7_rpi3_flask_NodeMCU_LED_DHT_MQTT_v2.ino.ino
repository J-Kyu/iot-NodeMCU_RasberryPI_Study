#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
//GPIO Pin mapping 부분, nodemcu와 아두이노간 pin이 달라서 초기 설정 필요
#define D0 16 // LED
#define D1 5 // Relay
#define D2 4 // DHT22
#define LED_PIN D0
#define RELAY1_PIN D1
#define DHT_PIN D2
#define CDS_PIN A0
// Sensors and Actuators
#define DHTTYPE DHT22
#define LED_ON HIGH
#define LED_OFF LOW
#define RELAY_ON LOW
#define RELAY_OFF HIGH
int led_state, usbled_state;
// Wifi
const char *wifi_ssid = "J-Kyu"; // 사용하는 공유기 이름
const char *wifi_password = "password"; // 공유기 password 입력


// MQTT
#define mqtt_broker "203.252.106.154" //MQTT broker address(자신의 Raspberry Pi3 IP) 노트북을 통한 모바일 핫스팟에 서 IP check
#define mqtt_user "iot"
#define mqtt_pwd "csee1414"
#define TOPIC_GREETINGS "Hello from nodeMCU at 2"
String mqtt_payload;

//Publish를 위한 Topic
const char *mqtt_nodeName = "nodeMCU.2"; // nth405를 자신의 학번으로 변경
const char *pub_dht = "iot/2/dht22"; // nth405를 자신의 학번으로 변경
const char *pub_cds = "iot/2/cds"; // nth405를 자신의 학번으로 변경
//Subscribe Topic
const char *sub_topic = "iot/2"; // nth405를 자신의 학번으로 변경
WiFiClient wifiClient; // WIFI client
DHT dht(DHT_PIN, DHTTYPE); // 온습도 센서 instance 선언
float temperature, humidity;
int lightValue;
char pub_data[80]; //publishing 할때 사용
void callback(char* topic, byte* payload, unsigned int length);

PubSubClient mqttc(mqtt_broker, 1883, callback, wifiClient); // MQTT client

void callback(char *topic, byte *payload, unsigned int length) {//Web으로 부터 수신한 Message에 따른동작 제어 함수
  
  char message_buff[100]; //initialise storage buffer
  String msgString;
  int i = 0;
  Serial.println("Message arrived: topic: " + String(topic));
  Serial.println("Length: "+ String(length,DEC));
  
  //create character buffer with ending null terminator (string)
  for(i=0; i<length; i++){
    message_buff[i] = payload[i];
  }
  
  message_buff[i]= '\0';
  msgString = String(message_buff );
  Serial.println("Payload: "+ msgString);
  led_state = digitalRead(LED_PIN);
  usbled_state = digitalRead(RELAY1_PIN);


    //전송된 메시가 "led"이면 LED를 받을 때마다 켜고 끈다.(토글)
  if (msgString == "LED") {
    digitalWrite(LED_PIN, !led_state);
    Serial.println("Switching LED");
  }
  else if (msgString == "LED/ON") {
    digitalWrite(LED_PIN, LED_ON);
    Serial.println("LED ON");
  } 
  else if (msgString == "LED/OFF") {
    digitalWrite(LED_PIN, LED_OFF);
    Serial.println("LED OFF");
  } 
  else if (msgString == "dht22") {
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();
    mqtt_payload = String("Temperature is ") + String(temperature) + String(", and Humidity is ") +
    String(humidity);
    mqttc.publish("iot/2/dht22", mqtt_payload.c_str());
    Serial.println("Message sent : " + mqtt_payload);
  } 
  else if (msgString == "cds") {
    lightValue = analogRead(CDS_PIN);
    String payload = String("Light intensity is ") + String(lightValue);
    mqttc.publish("iot/2/cds", payload.c_str());
    Serial.println("Message sent : " + payload);
  }
  else if(msgString == "USBLED/ON"){
      digitalWrite(RELAY1_PIN, RELAY_ON);
      usbled_state = RELAY_ON; 
  }
  else if(msgString == "USBLED/OFF"){
      digitalWrite(RELAY1_PIN, RELAY_OFF);
      usbled_state = RELAY_OFF; 
  }
} /* end of callback() for MQTT */


void setup() {
  Serial.begin(9600);
  delay(10);
  pinMode(LED_PIN, OUTPUT); // Initialize the LED_BUILTIN pin as an output
  digitalWrite(LED_PIN, LED_OFF); //LED off
  pinMode(RELAY1_PIN, OUTPUT);
  digitalWrite(RELAY1_PIN, RELAY_OFF);
  pinMode(CDS_PIN,INPUT);
  InitWiFi();
  
  //Connection to MQTT broker
  if (mqttc.connect(mqtt_nodeName, mqtt_user, mqtt_pwd)){
    mqttc.publish(pub_dht, TOPIC_GREETINGS); // testing message of publish
    mqttc.subscribe(sub_topic);//Subscribe 할 Topic
  }
  dht.begin();
}



void loop() {
  if(!wifiClient.connected()){
    reconnect();
  }
  delay(500); // delay
  
  mqttc.loop();
} /* end of loop() */


void InitWiFi(){
  Serial.println();
  Serial.println("Connectiong to WiFi..");
  // attempt to connect to WiFi network
  WiFi.begin(wifi_ssid, wifi_password);
  while (WiFi.status() != WL_CONNECTED){
  delay(500);
  Serial.print(".");
  }
  // 접속이 되면 출력
  Serial.println();
  Serial.print("Connected to AP: ");
  //접속 정보를 출력
  Serial.println(WiFi.localIP());
}


void reconnect(){
  int status;
  //네트워크 접속
  while (!wifiClient.connected()){
    status = WiFi.status();
    if( status != WL_CONNECTED) {
      WiFi.begin(wifi_ssid, wifi_password);
      while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println(".");
      }
      Serial.println("Connected to AP again");
    }
    delay(5000);
  }//end while
}//Network 접속 확인 함수
