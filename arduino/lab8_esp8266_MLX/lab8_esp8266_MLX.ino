#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MLX90614.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);//Screen

//Global Vairable
bool isDetecting = true;


void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
   //OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed ~!"));
    for(;;);
  }
  
  display.clearDisplay();
  display.setTextColor(WHITE);

  mlx.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  float temp = mlx.readObjectTempC();
  
  if (temp < 30.0f){

    if(isDetecting){
      DisplayTH(0.0f,false);
    }

  }
  else{
    DisplayTH(temp,true);
  }

  

}


void DisplayTH(float t,bool isHuman){

  if (isnan(t)) {
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0,0);
    display.print("Failed to read from MLX sensor!");
    display.display();
    return;
  }

    
  if (!isHuman) {

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0,0);
    display.print("The Temperature is below 30.0.....");
    display.display();
    isDetecting = false;
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

  display.display(); 
  isDetecting = true;
  
  
}
