#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHTesp.h>

//GPIO Pin mapping 부분, nodemcu와 아두이노간 pin이 달라서 초기 설정 필요

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define D0 16 // LED
#define D1 5 // Relay
#define D2 4 // DHT22

#define LED_PIN 16 //D0
#define RELAY1_PIN 2 //D1
#define DHT_PIN 0 //D3
#define CDS_PIN A0 //A0

// Sensors and Actuators
#define LED_ON HIGH
#define LED_OFF LOW
#define RELAY_ON LOW
#define RELAY_OFF HIGH
#define DHTTYPE DHTesp::DHT22 // case of dht11 module


int led_state, usbled_state;
// Wifi
const char *wifi_ssid = "J-Kyu"; // 사용하는 공유기 이름
const char *wifi_password = "password"; // 공유기 password 입력

//Screen
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


//Global Variable
unsigned long previousHTTime = 0;





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

DHTesp dht; // 온습도 센서 instance 선언

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
  if (msgString == "led") {
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
    humidity = dht.getHumidity();
    temperature = dht.getTemperature();
    mqtt_payload = String("Temperature is ") + String(temperature) + String(", and Humidity is ") +
    String(humidity);
    mqttc.publish("iot/2/dht22", mqtt_payload.c_str());
    Serial.println("Message sent : " + mqtt_payload);
  } 
  else if (msgString == "dht22_t") {
    temperature = dht.getTemperature();
    mqtt_payload = String("Temperature is ") + String(temperature);
    mqttc.publish("iot/2/dht22_t", mqtt_payload.c_str());
    Serial.println("Message sent : " + mqtt_payload);
  } 
  else if (msgString == "dht22_h") {
    humidity = dht.getHumidity();
    mqtt_payload = String("Humidity is ") + String(humidity);
    mqttc.publish("iot/2/dht22_h", mqtt_payload.c_str());
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
  else if(msgString == "USBLED"){
      digitalWrite(RELAY1_PIN, !usbled_state);
      usbled_state = !usbled_state; 
  }
} /* end of callback() for MQTT */


void setup() {
  Serial.begin(9600);
  delay(10);
  //DHT22
  dht.setup(DHT_PIN,DHTTYPE);
  
  //LED_Pin
  pinMode(LED_PIN, OUTPUT); // Initialize the LED_BUILTIN pin as an output
  digitalWrite(LED_PIN, LED_OFF); //LED off
  
  //USB LED
  pinMode(RELAY1_PIN, OUTPUT);
  digitalWrite(RELAY1_PIN, RELAY_OFF);
  
  //CDS
  pinMode(CDS_PIN,INPUT);

  //WiFi
  InitWiFi();

  //OLDE
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  display.clearDisplay();
  display.setTextColor(WHITE);
  
  //Connection to MQTT broker
  if (mqttc.connect(mqtt_nodeName, mqtt_user, mqtt_pwd)){
    mqttc.publish(pub_dht, TOPIC_GREETINGS); // testing message of publish
    mqttc.subscribe(sub_topic);//Subscribe 할 Topic
  }
  else{
    Serial.println("MQTT connection failed.....\n");
  }
  
}



void loop() {

   
  unsigned long currentTime = millis();  

  
  if(currentTime-previousHTTime >= 1000){
      
      previousHTTime = millis();
      
      float humidity = dht.getHumidity();
      float temperature = dht.getTemperature();
      DisplayTH(humidity,temperature);
  }

  
  if(!wifiClient.connected()){
    reconnect();
  }

  
  
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







void DisplayTH(float t,float h){

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  //clear display
  display.clearDisplay();

  // display temperature
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Temperature: ");
  display.setTextSize(2);
  display.setCursor(0,10);
  display.print(t);
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);
  display.write(248);
  display.setTextSize(2);
  display.print("C");
  
  // display humidity
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print("Humidity: ");
  display.setTextSize(2);
  display.setCursor(0, 45);
  display.print(h);
  display.print(" %"); 
  
  display.display(); 

  
}
