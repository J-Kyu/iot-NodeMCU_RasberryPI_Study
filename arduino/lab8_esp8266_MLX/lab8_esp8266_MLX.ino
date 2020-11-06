#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MLX90614.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, 0);//Screen

//Global Vairable
enum MeasureState {
  Below30,
  Measuring,
  MeasureSucc,
  MeasureFail
};
MeasureState measureState = Below30;

//measuring
const float measuringInterval = 3000.0f;
float measuringCountTime = 0.0f;

//displaying time
const float displayingInterval = 5000.0f;
float displayCountTime = 0.0f;

float initTemp = 0.0f;//previous temperature


void setup() {
  // put your setup code here, to run once:
  
  Wire.setClock(100000L);
  
  dbegin(9600);
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
  float currentTime = millis();
  float temp = mlx.readObjectTempC();

  switch(measureState){
    case Below30:{
      
      if(temp <30.0f){
        measureState = Below30;  
        DisplayOLED("Current Temperature is below 30... > <",-1,-1);
      }
      else{
        initTemp = temp; //set previous temperature before measuring
        measuringCountTime = millis(); //mark count time before measruing
        measureState = Measuring; //change state
      }

      break;
    }
    case Measuring:{

      if(initTemp - temp > 0.3f){
        displayCountTime = millis();
        measureState = MeasureFail;
        measuringCountTime = 0.0f;
        break;
      }
      else if(currentTime-measuringCountTime >= measuringInterval){
        measureState = MeasureSucc;
        measuringCountTime = 0.0f;
        break;
      }
      else{
        displayCountTime = millis();
        DisplayOLED("Measuring...",-1,(currentTime-measuringCountTime)/measuringInterval);
        //display State = loading
      }
      
      break;
    }
    case MeasureSucc:{
      
      if(currentTime - displayCountTime < displayingInterval){
        //display 5 seconds for actual temperature
        //display state = show temp  
        
        DisplayOLED("Current Temperature is",initTemp,(currentTime-displayCountTime)/displayingInterval);        
      }
      else{
        displayCountTime = 0.0f; //reset count time
        measureState = Below30;
      }


      break;
    }
    case MeasureFail:{
        if(currentTime - displayCountTime < displayingInterval){
        //display 5 seconds for failure message
        //display state = failure message  
        DisplayOLED("Measure Fails....",-1,(currentTime-displayCountTime)/displayingInterval);
      }
      else{
        displayCountTime = 0.0f; //reset count time
        measureState = Below30;
      }
      
      break;
    }
    default:{
      break;
    }
  }
  

}


void DisplayOLED(char* text,float temp ,float percent){

 

  //clear display
  display.clearDisplay();


  //text section
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println(text);  

  //temperature section
  if(temp > 0.0f){
    display.setTextSize(2);
    display.setCursor(20,20);
    display.print(temp);  
    display.print(" ");
    display.setTextSize(2);
    display.cp437(true);
    display.write(248);
    display.setTextSize(2);
    display.print("C");
  }

  //loading section
  if( percent > 0.0f){

    drintln(128*percent);
    for( int i = 0; i < int(128*percent); i+= 10){
        display.setTextSize(3);
        display.setCursor(i,40);
        display.print("I");
    }
  }


  


  display.display(); 

  
  
}
