#include <DHT.h>
#include <ESP8266WiFi.h>

// 공유기 또는 무선환경에 따라 환경재설정
const char* ssid = "J-Kyu"; // 사용할 무선 SSID로 지정(예:HGU_IoT_1)
const char* password = "password";//인터넷 연결
IPAddress ip(192,168,137,1); // 고정 아이피 주소
IPAddress gateway(192,168,10,1); // set gateway to match your network
IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your

#define D0 16 // LED(5파이)
#define D1 5 // Relay control signal pin
#define D2 4 // 온습도센서 연결핀
#define LIGHT_PIN A0 // 조도센서 연결핀
#define LED_PIN D0
#define DHT_PIN D2
#define DHTTYPE DHT22
#define RELAY1_PIN D1
#define RELAY_OFF HIGH
#define RELAY_ON LOW
#define LED_ON HIGH
#define LED_OFF LOW


DHT dht(DHT_PIN, DHTTYPE);
int USBLED_state, light_value;
float temperature, humidity;
WiFiServer server(80);

void setup() {
  Serial.begin(9600); //속도-usb로 연결(통신)하겠다
  dht.begin();
  delay(100);
  pinMode(LIGHT_PIN,INPUT); // CDS 조도 센서 입력단자
  pinMode(LED_PIN, OUTPUT); // LED 연결단자
  pinMode(RELAY1_PIN, OUTPUT); // Relay signal 출력단자
  digitalWrite(RELAY1_PIN, RELAY_OFF); // Relay OFF
  USBLED_state = RELAY_OFF;
  
  //Connect to wifi my network;
  Serial.println();
  Serial.println();
  Serial.println("Connecting to ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA); // station mode로 설정
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password); //와이파이에 연결
  //wifi에 접속시도 하는 동안 점을 찍어 진행되고 있음을 표시
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
  
  Serial.println("");
  Serial.println("WiFi Connected");
  
  //Start the server
  server.begin();
  Serial.println("Server started");
  
  //Print the IP address - 웹에서 접속할 IP를 알려 준다.
  Serial.println("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}



void loop() {
// Check if a client has connected
  WiFiClient client = server.available();
  if(!client) {
    delay(1000); return;
  }
  
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  Serial.println("Measuring Temperature and Humidity...");
  
  while((isnan(humidity) || isnan(temperature))){
    delay(1000);
    Serial.print(".");
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();
  }
  
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.print(" Humidity = ");
  Serial.println(humidity);
  
  // light_value = analogRead(LIGHT_PIN);
  // Wait untill the client sends some data
  Serial.println("new client");
  
  while(!client.available()){
    delay(100);
  }



  //Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  
  //Match the request for LED
  if (request.indexOf("/LED/ON") != -1) {
    digitalWrite(LED_PIN, LED_ON);
  }
  if(request.indexOf("/LED/OFF") != -1) {
    digitalWrite(LED_PIN, LED_OFF);
  }
  //Match the request for USBLED
  if (request.indexOf("/USBLED/ON") != -1) {
    digitalWrite(RELAY1_PIN, RELAY_ON);
    USBLED_state = RELAY_ON;
  }
  if(request.indexOf("/USBLED/OFF") != -1) {
    digitalWrite(RELAY1_PIN, RELAY_OFF);
    USBLED_state = RELAY_OFF;
  }



  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<title>NodeMCU Control</title>");
  client.println("<meta name='viewport' content='width=device-width, user-scalable=no'>");
  client.println("</head>");
  client.println("<body>");
  client.println("<div style='width: 300px; margin: auto; text-align: center;'>");
  client.println("<h1>Welcome to Handong Global University</h1>");
  client.println("<h2>NodeMCU Web Server</h2>");
  client.print("<h3>");
  client.print(WiFi.localIP()); //IP주소 출력
  client.println("</h3>");
  client.println("<p>");
  client.println("</p>");
  
  
  
  
  client.println("<a href=\"/LED/ON\"\"><button>LED On </button></a>");
  client.println("<a href=\"/LED/OFF\"\"><button>LED Off </button></a><br/>");
  client.println("<p>");
  client.print("Temperature : "); client.println(temperature);
  client.println("</p>"); client.println("<p>");
  client.print("Humidity : "); client.println(humidity);
  client.println("</p>"); client.println("<p>");
  client.print("USB LED lamp: ");
  
  if(USBLED_state == RELAY_ON) {
    client.println("ON");
  } else {
    client.println("OFF");
  }
  client.println("</p>");
  client.println("Light intensity : "); client.println(light_value);
  client.println("<p>");
  client.println("</div>");
  client.println("</body>");
  client.println("</html>");
  delay(1);
  Serial.println("Client disconnected");
  Serial.print("");
}
