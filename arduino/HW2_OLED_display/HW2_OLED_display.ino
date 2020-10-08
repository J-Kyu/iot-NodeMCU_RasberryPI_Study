/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHTesp.h>

#define LIGHT_PIN A0

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define RELAY1_PIN 2
#define RELAY_OFF HIGH // HIGH 신호이면 릴레이 동작하지 않음
#define RELAY_ON LOW // LOW 신호이면 릴레이 동작함

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHTPIN 0     // Digital pin connected to the DHT sensor

// Uncomment the type of sensor in use:
#define DHTTYPE DHTesp::DHT22 // case of dht11 module

DHTesp dht;


int preEnvState = 0;
int relayState = RELAY_OFF;

unsigned long relayOnTime = 0;
unsigned long previousHTTime = 0;

void setup() {
  Serial.begin(9600);

  dht.setup(DHTPIN,DHTTYPE);
  pinMode(LIGHT_PIN, INPUT);

  pinMode(RELAY1_PIN, OUTPUT); // 릴레이 signal 단자
  digitalWrite(RELAY1_PIN, RELAY_OFF); // 릴레이 OFF

  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
}

void loop() {
  
  unsigned long currentTime = millis();   
  int light_val = analogRead(LIGHT_PIN);

  
  if(currentTime-previousHTTime >= 1000){
      
      previousHTTime = millis();
      
      float humidity = dht.getHumidity();
      float temperature = dht.getTemperature();
      DisplayTH(temperature,humidity);

      Serial.print("Light Intensity: ");
      Serial.print(light_val);
      Serial.print("\t");
      Serial.print(preEnvState);
      Serial.print("\n");
  }

      

 if(preEnvState == 1 && light_val < 300 && relayState == RELAY_OFF  && currentTime - relayOnTime > 10000){
    //turn on relay
    relayState = RELAY_ON;
    relayOnTime = millis();
    Serial.print("Relay ON \n");
    
  }
  else if(preEnvState == 0 && light_val < 300 && relayState == RELAY_ON  && currentTime - relayOnTime < 10000){
    //constantly on for left 10 sec
        Serial.print("Relay ON...ing \n");
  }
   else if( relayState == RELAY_ON  &&currentTime - relayOnTime > 10000){
    //turn off relay when 10s is done
    relayState = RELAY_OFF;

     Serial.print("Relay Off....10s done \n");
   }
   else if(preEnvState == 1 && light_val < 300 && relayState == RELAY_ON){
    //turn off relay (D-> B b4 10 secs
    relayState = RELAY_OFF;    
    relayOnTime = 0;
    Serial.print("Relay Off....B->D \n");
   }

//   else if(preEnvState == 0 && light_val > 300 && relayState == RELAY_ON  &&currentTime - relayOnTime < 10000){
//    //turn off relay (D-> B b4 10 secs
//    relayState = RELAY_OFF;
//    Serial.print("Relay Off....D->B \n");
//   }



  digitalWrite(RELAY1_PIN, relayState); // 릴레이 상태값 출력하기
  

  if(light_val < 300){
       preEnvState = 0;
  }
  else{
       preEnvState = 1;
  }
  
}


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
