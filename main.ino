#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32 
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define echoPin 3 
#define trigPin 2 
int red = 4,green=5,val=10;
long duration; 
int distance; 
int pot = A0;
int potVal;
void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(9600); 
  display.clearDisplay();
  startUpDisplay();
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.display();
}
void startUpDisplay(void) {
   display.clearDisplay();
  for(int16_t i=0; i<display.height()/2-2; i+=2) {
    display.fillRoundRect(i, i, display.width()-2*i, display.height()-2*i,
      display.height()/4, INVERSE);
    display.display();
    delay(1);
  }
  delay(150);
  display.clearDisplay();
  for(int16_t i=0; i<display.height()/2-2; i+=2) {
    display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i,
      display.height()/4, WHITE);
    display.display();
    delay(1);
  }
  delay(500);
  display.clearDisplay();
  display.display();
}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; 
  distance = distance/2.54;
  delay(50);
  display.clearDisplay();
  display.setCursor(10,0);
  display.println("Trigger:");
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" in");
  display.setCursor(10,17);
  display.print(val);
  display.print(" in");
  display.display();
  delay(50);
  potVal = analogRead(pot);
  Serial.println(potVal);
  val = map(potVal,0,930,24,4);
  Serial.println(val);
  if (distance > val && distance != 466) {
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
  }
 
  else {
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
  }
  delay(200);
}
