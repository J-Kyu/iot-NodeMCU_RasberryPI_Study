#include "DHTesp.h"
#define D2 4 // GPIO 4
#define DHTPIN D2 //digital pin
#define DHTTYPE DHTesp::DHT22 // case of dht11 module

#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif

DHTesp dht;


void setup()
{
  Serial.begin(115200);
  dht.setup(DHTPIN,DHTTYPE);


  // Autodetect is not working reliable, don't use the following line
  // dht.setup(17);
  // use this instead: 
  //  dht.setup(DHTPIN, DHTesp::DHT22); // Connect DHT sensor to GPIO 17

}

void loop()
{
  delay(2000);

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  if(!isnan(humidity) && !isnan(temperature)){
    Serial.print("Humidity: \t");
    Serial.print(humidity, 1);
    Serial.print("\t\t");
    Serial.print("Temperature: \t");
    Serial.print(temperature, 1);
    Serial.print("\n");
    delay(2000);
  }
  else{
    Serial.println("Failed to read from DHT sensor");
    return;
  }
}
