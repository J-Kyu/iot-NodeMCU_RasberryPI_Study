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

//declare
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);//Screen
DHTesp dht; // 온습도 센서 instance 선언 

//Global Variable
unsigned long previousHTTime = 0;
int preEnvState = 1;
int led_state= 0;
int relayState = 0;
unsigned long relayOnTime = 0;
unsigned long currentTime = 0;
int controlFlag = 0;
int light_val = 0;


// Wifi
const char *wifi_ssid = "J-Kyu"; // 사용하는 공유기 이름
const char *wifi_password = "password"; // 공유기 password 입력



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
          controlFlag = 1;
      }
      else if(msgString == "USBLED/OFF"){
          digitalWrite(RELAY1_PIN, RELAY_OFF);
          controlFlag = 2;
      }
      else if(msgString == "USBLED"){
          digitalWrite(RELAY1_PIN, !relayState);
          controlFlag = relayState == 1 ? 1 : 2;
      }
  
} 


void setup() {
  Serial.begin(9600);

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

   client.loop();

   delay(100);

    
  currentTime = millis(); 
  light_val = analogRead(CDS_PIN); 

  
  if(currentTime-previousHTTime >= 10000){
      
      previousHTTime = millis();
      //display
      float humidity = dht.getHumidity();
      float temperature = dht.getTemperature();
      DisplayTH(temperature,humidity);

      //publishing temperature & Humidiy & Light Intensity
      String payload = String("Light intensity: ") + String(lightValue)+String("\t Temperature: ")+String(temperature)+String("\tHumidity: ")+String(humidity);;
      client.publish("iot/2/message", payload.c_str());
  }

  if( controlFlag == 1 || preEnvState == 1 && light_val < 300 && currentTime - relayOnTime > 10000){
    //turn on
    relayState = RELAY_ON;
    relayOnTime = millis();
    controlFlag = 0;
  }
  else if( controlFlag == 0 && currentTime - relayOnTime < 10000){
    relayState = RELAY_ON;
  }
  else if(controlFlag == 2 || relayState == RELAY_ON && currentTime - relayOnTime > 10000){
    relayState = RELAY_OFF;
    relayOnTime = currentTime - 10001; // always make this valid:  currentTime - relayOnTime > 10000
    controlFlag = 0;
  }

  digitalWrite(RELAY1_PIN, relayState); // 릴레이 상태값 출력하기
  

  

   
  if(light_val < 300){
       preEnvState = 0;
  }
  else{
      preEnvState = 1;
  }
  
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
