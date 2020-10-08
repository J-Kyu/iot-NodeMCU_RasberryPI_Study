#include <ESP8266WiFi.h>
#include <EspMQTTClient.h>

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


// Wifi
const char *wifi_ssid = "J-Kyu"; // 사용하는 공유기 이름
const char *wifi_password = "password"; // 공유기 password 입력

//Screen
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


//Global Variable
unsigned long previousHTTime = 0;
int preEnvState = 1;
int led_state= 0;
int relayState = 0;
unsigned long relayOnTime = 0;
unsigned long currentTime = 0;
int timeFlag = 0;
int light_val = 0;


// MQTT
#define mqtt_broker "203.252.106.154" //MQTT broker address(자신의 Raspberry Pi3 IP) 노트북을 통한 모바일 핫스팟에 서 IP check
#define mqtt_user "iot"
#define mqtt_pwd "csee1414"
#define TOPIC_GREETINGS "Hello from nodeMCU at 2"
String mqtt_payload;



//MQTT Client

EspMQTTClient client(
  wifi_ssid,
  wifi_password,
  mqtt_broker,  // MQTT Broker server ip
  mqtt_user,   // Can be omitted if not needed
  mqtt_pwd,   // Can be omitted if not needed
  "kit_2"      // Client name that uniquely identify your device
);




//Publish를 위한 Topic
const char *mqtt_nodeName = "nodeMCU.2";
//Subscribe Topic
const char *sub_topic = "iot/2";

DHTesp dht; // 온습도 센서 instance 선언

float temperature, humidity;
int lightValue;
char pub_data[80]; //publishing 할때 사용
void callback(const String& payload);


void callback(const String& payload) {
  
//  client.subscribe("iot/2",[](const String & payload) {
      unsigned int length = payload.length();
      
      char message_buff[100]; //initialise storage buffer
      String msgString;
      int i = 0;
      Serial.println("Message arrived: topic: " + String("iot/2"));
      Serial.println("Length: "+ String(length,DEC));
      
      //create character buffer with ending null terminator (string)
      for(i=0; i<length; i++){
        message_buff[i] = payload[i];
      }
      
      message_buff[i]= '\0';
      msgString = String(message_buff );
      Serial.println("Payload: "+ msgString);
    
    
        //전송된 메시가 "led"이면 LED를 받을 때마다 켜고 끈다.(토글)
      if (msgString == "led") {
        digitalWrite(LED_PIN, !led_state);
        led_state = !led_state;
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
        client.publish("iot/2/dht22", mqtt_payload.c_str());
        Serial.println("Message sent : " + mqtt_payload);
      } 
      else if (msgString == "dht22_t") {
        temperature = dht.getTemperature();
        mqtt_payload = String("Temperature is ") + String(temperature);
        client.publish("iot/2/dht22_t", mqtt_payload.c_str());
        Serial.println("Message sent : " + mqtt_payload);
      } 
      else if (msgString == "dht22_h") {
        humidity = dht.getHumidity();
        mqtt_payload = String("Humidity is ") + String(humidity);
        client.publish("iot/2/dht22_h", mqtt_payload.c_str());
        Serial.println("Message sent : " + mqtt_payload);
      } 
      else if (msgString == "cds") {
        lightValue = analogRead(CDS_PIN);
        String payload = String("Light intensity is ") + String(lightValue);
        client.publish("iot/2/cds", payload.c_str());
        Serial.println("Message sent : " + payload);
      }
      else if(msgString == "USBLED/ON"){
          digitalWrite(RELAY1_PIN, RELAY_ON);
          relayState = RELAY_ON; 
          timeFlag = 0;
      }
      else if(msgString == "USBLED/OFF"){
          digitalWrite(RELAY1_PIN, RELAY_OFF);
          relayState = RELAY_OFF; 
          timeFlag = 0;
      }
      else if(msgString == "USBLED"){
          digitalWrite(RELAY1_PIN, !relayState);
          relayState = !relayState; 
          timeFlag = 0;
      }
     
//    });
  


  
} /* end of callback() for MQTT */


void setup() {
  Serial.begin(9600);

  //MQTT Callback
//  client.setOnConnectionEstablishedCallback(callback);


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


  //OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  display.clearDisplay();
  display.setTextColor(WHITE);

  if( analogRead(CDS_PIN) < 300){
       preEnvState = 0;
  }
  else{
       preEnvState = 1;
  }

  led_state = digitalRead(LED_PIN);
  relayState = digitalRead(RELAY1_PIN);

  

    
}



void loop() {

  currentTime = millis(); 
  light_val = analogRead(CDS_PIN); 
  Serial.print(light_val);
  Serial.print("\n");

  
  if(currentTime-previousHTTime >= 1000){
      
      previousHTTime = millis();
      
      float humidity = dht.getHumidity();
      float temperature = dht.getTemperature();
      DisplayTH(temperature,humidity);
  }

  if(timeFlag == 0 && preEnvState == 1 && light_val < 300 && currentTime - relayOnTime > 10000){
    //turn on
    relayState = RELAY_ON;
    relayOnTime = millis();
    timeFlag = 1;

  }
  else if(timeFlag == 1 && currentTime - relayOnTime < 10000){
    relayState = RELAY_ON;
  }
  else if(timeFlag == 1 && relayState == RELAY_ON && currentTime - relayOnTime > 10000){
    relayState = RELAY_OFF;
    timeFlag = 0;
  }

  digitalWrite(RELAY1_PIN, relayState); // 릴레이 상태값 출력하기
  

  

   
  if(light_val < 300){
       preEnvState = 0;
  }
  else{
      preEnvState = 1;
  }


  client.loop();
  
} /* end of loop() */




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



void onConnectionEstablished() {

  client.subscribe(sub_topic, callback);

  client.publish(sub_topic,"Connection has established with nodeMCU_Kit Number 2");
  Serial.println("Connection has established with nodeMCU_Kit Number 2");
}
