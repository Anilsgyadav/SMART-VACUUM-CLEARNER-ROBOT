#include <Arduino.h>
#include <Servo.h>
#define trigPin PA4  
#define echoPin PA5  
#define servoPin PA6 
#define motorControlPin PA9 
#define motor1Pin1 PA0 
#define motor1Pin2 PA1 
#define motor2Pin1 PA2 
#define motor2Pin2 PA3 
#define motor1Enable PA7 
#define motor2Enable PA8 
long duration;
int distance;
Servo myServo;
void sweepServo();
void stopMotors();
void moveForward();
void moveBackward();
void turnRight();
void turnLeft();
int readDistance();
void collectObject();
void activateDCMotor(bool state);
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor1Enable, OUTPUT);
  pinMode(motor2Enable, OUTPUT);
  pinMode(motorControlPin, OUTPUT);
  digitalWrite(motorControlPin, LOW); 
  myServo.attach(servoPin);
  Serial.begin(9600);
  digitalWrite(motor1Enable, HIGH);
  digitalWrite(motor2Enable, HIGH); 
}
void loop() {
  int distance = readDistance();
  Serial.print("Distance: ");
  Serial.println(distance);
  if (distance > 0 && distance < 20) {
    stopMotors();
    delay(500); 
    collectObject();
    delay(1000);  
    moveBackward(); 
    delay(1000);  
    turnRight(); 
    delay(500);    
  } else {
    moveForward(); 
  }
  sweepServo();
}
void activateDCMotor(bool state) {
  if (state) {
    digitalWrite(motorControlPin, HIGH);  
    Serial.println("DC Motor ON");
  } else {
    digitalWrite(motorControlPin, LOW); 
    Serial.println("DC Motor OFF");
  }
}
int readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH, 30000); 
  if (duration == 0) {
    Serial.println("No echo detected.");
    return -1;
  }
  int distance = duration * 0.034 / 2; 
  return distance;
}
void sweepServo() {
  for (int pos = 0; pos <= 180; pos += 1) { 
    myServo.write(pos);                 
    delay(15);                            
  }
  for (int pos = 180; pos >= 0; pos -= 1) { 
    myServo.write(pos);                     
    delay(15);                              
  }
}
void moveForward() {
  Serial.println("Moving forward...");
  digitalWrite(motor1Pin1, HIGH);  
  digitalWrite(motor1Pin2, LOW);   
  digitalWrite(motor2Pin1, HIGH);  
  digitalWrite(motor2Pin2, LOW);   
}
void moveBackward() {
  Serial.println("Moving backward...");
  digitalWrite(motor1Pin1, LOW);   
  digitalWrite(motor1Pin2, HIGH); 
  digitalWrite(motor2Pin1, LOW);   
  digitalWrite(motor2Pin2, HIGH); 
}
void turnRight() {
  Serial.println("Turning right...");
  digitalWrite(motor1Pin1, HIGH);  
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW); 
  digitalWrite(motor2Pin2, LOW);
}
void turnLeft() {
  Serial.println("Turning left...");
  digitalWrite(motor1Pin1, LOW);   
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);  
  digitalWrite(motor2Pin2, LOW);
}
void collectObject() {
  Serial.println("Collecting object...");
  activateDCMotor(true);  
  delay(2000); 
  activateDCMotor(false);
}
void stopMotors() {
  Serial.println("Stopping motors...");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}