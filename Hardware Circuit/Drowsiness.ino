#include <Servo.h>

#include <LiquidCrystal.h>

Servo myServo; // Create a servo object
LiquidCrystal lcd(2, 3, 4, 5, 6,7);
const int buzzer_Pin = 8;
const int led_Pin = 9;
char sleep_status = 0;
const int relay = 7;
const int trigPin = 10;  // Connect the Trig pin of the ultrasonic sensor to Arduino digital pin 9
const int echoPin = 11; // Connect the Echo pin of the ultrasonic sensor to Arduino digital pin 10


void setup() {
  Serial.begin(9600);  
  pinMode(buzzer_Pin, OUTPUT);
  pinMode(led_Pin, OUTPUT);
  pinMode(5,OUTPUT);
  lcd.begin(16, 2);
  lcd.print("Driver Sleep ");
  lcd.setCursor(0,2);
  lcd.print("Detection SYSTEM");
  digitalWrite(buzzer_Pin, LOW); 
  digitalWrite(led_Pin, LOW);
  digitalWrite(5,LOW);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relay, OUTPUT);
  myServo.attach(6);
}
void loop() 
{

    while (Serial.available() > 0) 
  {
    sleep_status = Serial.read();
    if(sleep_status == 'a')
    { 
        lcd.clear();
        lcd.print("Please wake up");
        digitalWrite(buzzer_Pin, HIGH); 
        digitalWrite(led_Pin, HIGH);
        delay(2000);
        digitalWrite(buzzer_Pin, LOW); 
        digitalWrite(led_Pin, LOW);
        digitalWrite(relay, 150);   // turn the LED on (HIGH is the voltage level)
        delay(500);
        digitalWrite(relay, LOW);    // turn the LED off by making the voltage LOW
        delay(500);
    }
    else if(sleep_status == 'b')
    {
        lcd.clear(); 
        lcd.print("All Ok");
        lcd.setCursor(0,2);
        lcd.print("Drive Safe");
        digitalWrite(buzzer_Pin, LOW); 
        digitalWrite(led_Pin, LOW);
        delay(2000);
    }
    else
    {
      /* Do Nothing */
    }
  }
   long duration, distance;

  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo pulse
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  distance = duration * 0.034 / 2;



  // Check if an object is within a certain range (adjust as needed)
  if (distance < 20) {
    // Turn on the motor
  for (int angle = 0; angle <= 90; angle++) {
    myServo.write(angle); // Set servo position
    digitalWrite(5,HIGH);
    delay(15); // Wait for the servo to reach the position (adjust delay as needed)
    digitalWrite(5,LOW);
  }
  }
  delay(100);
}
