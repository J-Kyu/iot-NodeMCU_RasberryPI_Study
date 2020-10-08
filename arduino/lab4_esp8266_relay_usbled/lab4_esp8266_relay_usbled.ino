#define D0 16
#define D1 5
#define LIGHT_PIN A0
#define LED_PIN D0
#define RELAY1_PIN D1
#define RELAY_OFF HIGH // HIGH 신호이면 릴레이 동작하지 않음
#define RELAY_ON LOW // LOW 신호이면 릴레이 동작함
int lightValue;
int relay_state = RELAY_OFF; // 릴레이 OFF
void setup() {
  Serial.begin(9600);
  delay(10);
  pinMode(LED_PIN, OUTPUT); // Initialize the LED pin as an output
  digitalWrite(LED_PIN, LOW); //LED off
  pinMode(LIGHT_PIN, INPUT); // 조도센서 입력단자
  pinMode(RELAY1_PIN, OUTPUT); // 릴레이 signal 단자
  digitalWrite(RELAY1_PIN, RELAY_OFF); // 릴레이 OFF
}


void loop() {
  lightValue = analogRead(LIGHT_PIN); // 조도센서 값 읽어오기
  if( lightValue < 500 ) { // 빛의 밝기가 어두워지면
    relay_state = RELAY_ON; // 릴레이 상태를 LED를 켤수 있는 모드로 변경
  }
  else if ( lightValue > 700 ) {
   relay_state = RELAY_OFF;
  }
  digitalWrite(RELAY1_PIN, relay_state); // 릴레이 상태값 출력하기
  Serial.println(lightValue);
  delay(500);
}
